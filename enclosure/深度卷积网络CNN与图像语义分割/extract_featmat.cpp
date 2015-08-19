#include <glog/logging.h>

#include <stdio.h>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc.hpp>

#include "caffe/caffe.hpp"
#include "caffe/blob.hpp"
#include "caffe/common.hpp"
#include "caffe/net.hpp"
#include "caffe/proto/caffe.pb.h"
#include "caffe/util/io.hpp"
#include "caffe/vision_layers.hpp"
#include "caffe/util/math_functions.hpp"

using boost::shared_ptr;
using caffe::Blob;
using caffe::Caffe;
using caffe::Datum;
using caffe::Layer;
using caffe::Net;
using caffe::Timer;
using caffe::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using cv::Mat;

struct InputData {
  string modelName;
  string protoName;
  string imageName;
  vector<string> blobs;
  vector<string> wrPrefix;
  string wrRoot;
  bool gpu_en;
  int  gpu_id;

  // Methods
  void set_default_val(void) {
    modelName = "";
    protoName = "";
    imageName = "";
    wrRoot = "./";
    gpu_en = false;  
    gpu_id = 0;
  }
  void print_help(void) {
    LOG(ERROR)<<
    "This program takes in a trained network and an input image, and then\n"
    " extract features of the input data produced by the net.\n"
    "Usage: extract_featmat [options]\n"
    "  -model     [pretrained_net_param]\n"
    "  -proto     [feature_extraction_proto_file]\n"
    "  -img       [rgb_image_name]\n"
    "  -blobs     [extract_feature_blob_name1[,name2,...]],refrence .prototxt with"
    "             \"blob:\". [all] for all layers. \n"
    "  -wr_prefix [output_feat_prefix1[,prefix2,...]], conrespond to -blobs\n"
    "  -wr_root   [output_feat_dir], optional, default \"./\", make sure it exist\n"
    "  -gpu       [gpu_id],optional,if not specified,default CPU\n";
  }
  // split by comma
  void split(const string& cmdline, vector<string>& strs) {
    strs.clear();
    string _str="";
    for (int k=0; k<cmdline.length(); ++k) {
      if (cmdline[k] != ',') {
        _str += cmdline[k];
      } else {
        strs.push_back(_str);
        _str = "";
      }
    }
    if (!_str.empty()) {
      strs.push_back(_str);
    }
  }
  // 
  InputData(void) {
    set_default_val();
  }
  // Parsing Input
  InputData(int argc, char **argv) {
    set_default_val();
    if (argc < 5*2+1) {
      print_help();
      return;
    }
    for (int i=1; i<argc; ++i) {
      if (::strcmp(argv[i],"-model")==0 && (i+1)!=argc) {
        modelName = argv[++i]; 
      } else if (::strcmp(argv[i],"-proto")==0 && (i+1)!=argc) {
        protoName = argv[++i];
      } else if (::strcmp(argv[i],"-img")==0 && (i+1)!=argc) {
        imageName = argv[++i];
      } else if (::strcmp(argv[i],"-wr_root")==0 && (i+1)!=argc) {
        wrRoot = argv[++i];
        if (wrRoot[wrRoot.length()-1] != '/') {
          wrRoot += '/';
        }
      } else if (::strcmp(argv[i],"-blobs")==0 && (i+1)!=argc) {
        const string blobs_str = argv[++i];
        split(blobs_str, blobs);
      } else if (::strcmp(argv[i],"-wr_prefix")==0 && (i+1)!=argc) {
        const string feat_str = argv[++i];
        split(feat_str, wrPrefix);
      } else if (::strcmp(argv[i],"-gpu")==0 && (i+1)!=argc) {
        gpu_en = true;
        gpu_id = atoi(argv[++i]);
      } else {
        LOG(ERROR) << "Cannot recognize command: " << argv[i];
        return;
      }
    }
  }
};

// pre-process images for caffe net input
int prepare_image(const Mat& img, float *data_ptr, unsigned long dsize) {
  Mat outimg;
  img.copyTo(outimg);
  outimg.convertTo(outimg, CV_32FC3);  // Convert To float(Dtype) first
  if (NULL==data_ptr) {
    cout << "data ptr should not be NULL."<<endl;
    return -1;
  }
  CHECK_EQ(dsize, outimg.total()*outimg.channels())
    << "Input image size dismatch blob size.";

  // OpenCV is already BGR format
  Mat mean(outimg.rows,outimg.cols,CV_32FC3,cv::Scalar(104,117,123));
  outimg -= mean;

  // rerange data
  vector<Mat> mat_vec;
  split(outimg, mat_vec);
  for (int i=0; i<mat_vec.size(); ++i) {
    float *src_ptr = NULL;
    switch (i) {
      case 0:
        src_ptr = reinterpret_cast<float *>(mat_vec[1].data);
        break;
      case 1:
        src_ptr = reinterpret_cast<float *>(mat_vec[0].data);
        break;
      case 2:
        src_ptr = reinterpret_cast<float *>(mat_vec[2].data);
      default:break;
    }
    caffe::caffe_copy(outimg.total(), src_ptr, data_ptr+outimg.total()*i);
  }

  return 0;
}

// Blob: batch_size x channels x height x width
// mat:  vector<height x width>, so the returned mat size=batch_size x channels
int blob2mat(const shared_ptr<Blob<float> >& feature_blob, vector<Mat>& mat_feat) {
  const int batch_size = feature_blob->num();
  const int channels   = feature_blob->channels();
  const int height     = feature_blob->height();
  const int width      = feature_blob->width();
  // CHECK_GT(batch_size,0) << "batch size should > 0";
  // CHECK_EQ(channels,3) << "channels should == 3";

  const float* feature_blob_data = NULL;
  for (int n=0; n<batch_size; ++n) {
    switch (Caffe::mode()) {
    case Caffe::GPU:
      feature_blob_data = feature_blob->gpu_data() + feature_blob->offset(n);
      break;
    case Caffe::CPU:
      feature_blob_data = feature_blob->cpu_data() + feature_blob->offset(n);
      break;
    default:
      LOG(ERROR) << "Unknow caffe mode";
    }
    
    for (int c=0; c<channels; ++c) {
      Mat _feat(height,width,CV_32FC1);
      float* _dst_data = reinterpret_cast<float *>(_feat.data);
      caffe::caffe_copy(height*width, feature_blob_data,_dst_data);
      mat_feat.push_back(_feat);
    }
  }
  return 0;
}


int main(int argc, char **argv) {
  InputData input_params(argc,argv);

  // Init Caffe Net
  LOG(INFO) << "Init caffe...";
  if (input_params.gpu_en) {
    Caffe::set_mode(Caffe::GPU);
    Caffe::SetDevice(input_params.gpu_id);
  } else {
    Caffe::set_mode(Caffe::CPU);
  }
  Caffe::set_phase(Caffe::TEST);
  Net<float> caffe_net(input_params.protoName);
  caffe_net.CopyTrainedLayersFrom(input_params.modelName);

  if (::strcmp(input_params.blobs[0].c_str(),"all")==0) {  // extract all layers
    input_params.blobs = caffe_net.blob_names();
    input_params.wrPrefix = caffe_net.blob_names();
    // '/' cannot appear in path, and we replace it with '_'
    for (int i=0; i<input_params.wrPrefix.size(); ++i) {  
      for (int j=0; j<input_params.wrPrefix[i].length(); ++j) {
        if (input_params.wrPrefix[i][j] == '/') {
          input_params.wrPrefix[i][j] = '_';
        }
      }
    }
  }
  CHECK_EQ(input_params.wrPrefix.size(),input_params.blobs.size())
    << "wr_prefix.size() != blobs.size()";

  // Check feat specified
  const int feat_nums = input_params.blobs.size();
  CHECK_GT(feat_nums,0)
    << "No blob names specified in command line.";
  for (size_t i = 0; i < feat_nums; i++) {
    CHECK(caffe_net.has_blob(input_params.blobs[i]))
      << "Unknown feature blob name " << input_params.blobs[i]
      << " in the network " << input_params.protoName;
  }

  // Preprocess
  LOG(INFO) << "Prepare image data...";
  const vector<Blob<float>* >& input_blobs = caffe_net.input_blobs();
  const int channels = input_blobs[0]->channels(); 
  const int resize_height = input_blobs[0]->height(); 
  const int resize_width  = input_blobs[0]->width(); 
  const int data_count = input_blobs[0]->count();
  Mat img = cv::imread(input_params.imageName.c_str(),1);
  if (!img.data) {
    LOG(ERROR) << "Cannot open image.";
    return -1;
  }
  CHECK_EQ(img.channels(),channels)
    << "Input image channel dismatch the Net.";

  Mat resized_img;
  cv::resize(img,resized_img,cv::Size(resize_height,resize_width));
  float *_data_ptr = new float[data_count];
  if (-1 == prepare_image(resized_img,_data_ptr,data_count) ) {
    return -1;
  }
  const float* const data_ptr = reinterpret_cast<const float* const>(_data_ptr);

  // Filling input and Extract feature
  switch (Caffe::mode()) {
  case Caffe::GPU:
    caffe::caffe_copy(data_count,data_ptr,input_blobs[0]->mutable_gpu_data());
    break;
  case Caffe::CPU:
    caffe::caffe_copy(data_count,data_ptr,input_blobs[0]->mutable_cpu_data());
    break;
  default:
    LOG(ERROR) << "Unknow caffe mode";
  }
  delete[] _data_ptr;

  LOG(INFO) << "Extracting features begin (total layers " << feat_nums << ")"; 
  //const vector<Blob<float>*>& output_blobs = 
  caffe_net.ForwardPrefilled();  // Forward
  for (int i=0; i<feat_nums; ++i) {
    const shared_ptr<Blob<float> > feature_blob = caffe_net.blob_by_name(input_params.blobs[i]);

    LOG(INFO) << "Extracting " << input_params.blobs[i] << " ("
      << feature_blob->channels()*feature_blob->num() << " Mat)";

    vector<Mat> mat_feature;
    blob2mat(feature_blob, mat_feature);
    // Save to disk
    for (int k=0; k<mat_feature.size(); ++k) {
      char sn[128];
      sprintf(sn,"%s%s_%.4d.png",input_params.wrRoot.c_str(),input_params.wrPrefix[i].c_str(),k);
      imwrite(sn,mat_feature[k]);
    }
  }
  LOG(INFO) << "Extracting features end";
}

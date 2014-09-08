// JavaScript Document
function IMGS(id,w,h,da,c){
  this.w=w;
  this.h=h;
  this.da=da;
  this.l=da.length;
  this.html="";
  this.id=id;
  this.child={img:[],div:[]};
  this.cr=0;
  this.xx=0;
  this.m=10;
  this.pr=null;
  this.time=false;
  if(typeof c =="undefined"){
    this.c={bg:"#600",color:"#fff",cbg:"#eee",ccolor:"#600",bc:"#ccc",step:6000}
  }else{
    this.c=c;
  }
  this.step=this.c.step;
  this.init();
}
IMGS.prototype={
  init:function(){
	document.writeln('<div id="'+this.id+'" style="position:relative;width:'+this.w+'px;height:'+this.h+'px;"></div>');
	var Bdiv=document.createElement("div");
	Bdiv.style.cssText="position:absolute;right:10px;bottom:1px;height:25px;z-index:100;";
	this.$(this.id).appendChild(Bdiv);
	var self=this;
    for(var i=this.l-1;i>=0;i--){
	  var img=document.createElement("img");
	  var div=document.createElement("div");
	  img.width=this.w;
	  img.height=this.h;
	  img.border="0";
	  img.src=this.da[i].src;
	  img.alt=this.da[i].name;
	  div.innerHTML=(i+1);
	  div.style.cssText="float:right;width:20px;height:18px;margin-right:5px;border:1px solid "+this.c.bc+";line-height:18px;text-align:center;cursor:default";
	  if(i>0){
	  div.style.cssText+="background:"+this.c.bg+";color:"+this.c.color+";";
	  }else{
	  div.style.cssText+="background:"+this.c.cbg+";color:"+this.c.ccolor+";";
	  }
	  if(typeof this.da[i].link !=""){
	    var a=document.createElement("a");
		a.href=this.da[i].link;
		a.appendChild(img);
		this.child.img[i]=a;
		this.$(this.id).appendChild(a);
	  }else{
	   this.child.img[i]=img;
	   this.$(this.id).appendChild(img);
	  }
	  this.child.img[i].style.cssText+=";position:absolute;left:0px;top:0px;z-index:1;display:none";
	  this.child.div[i]=div;
	  div.onmouseover=function(){
	     self.Cl(parseInt(this.innerHTML)-1);
	  }
	  if(this.l>0)this.pr=this.child.img[0];
	  if(this.l>1)Bdiv.appendChild(div);
	}
	this.Go();
  },
  Go:function(){
	var self=this; 
	for(var i=0;i<this.l;i++){
     this.child.img[i].style.zIndex="1";
	 this.child.div[i].style.background=this.c.bg;
	 this.child.div[i].style.color=this.c.color;
    }
	if(this.pr!=null)this.pr.style.zIndex="10";
	this.pr=this.child.img[this.cr];
	this.m=10;
	with(this.child.img[this.cr].style){filter='alpha(opacity=10)';opacity=0.1;display="";zIndex="20";}
	this.None(self,this.child.img[this.cr]);
	with(this.child.div[this.cr].style){background=this.c.cbg;color=this.c.ccolor;}
	this.cr++;
	if(this.cr==this.l)this.cr=0;
	if(this.l>1)this.time=setTimeout(function(){self.Go()},this.step);
  },
  None:function(self,tt){
	  with(tt.style){filter='alpha(opacity='+self.m+')';opacity=(self.m/100);}
		self.m+=5;
		if(self.m<101)
		self.xx=setTimeout(function(){self.None(self,tt)},10);
		else
		clearInterval(self.xx);
  },
  Cl:function(cr){
	 clearInterval(this.xx);
	 clearTimeout(this.time);
	 this.cr=cr;
	 this.Go();
	 
  },
  $:function(id){return document.getElementById(id);}
}

#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

function md2html()
{
    for name in `ls $1`
    do
    if [ ! -d $name ];then
      if [ "${name##*.}" == "md" ]; then
   
touch temp_head_keywords.html temp_title.html comments.html # 生成临时文件

title=$(sed -n -e "1,4s/<!---title:\(.\+\)-->/\1/p" $name)

sed -n -e "1,4s/<!---title:\(.\+\)-->/<title>\1<\/title>/p" $name > temp_head_keywords.html # 生成<head>中的标题标签
# sed -n -e "s/<!---keywords:\(.\+\)-->/<meta name=\"keywords\" content=\"\1\">/p" $name >> temp_head_keywords.html # 生成<head>中的关键字标签
sed -n -e "1,4s/<!---title:\(.\+\)-->/<h1>\1<\/h1>/p" $name > temp_title.html                 # 生成<body>中的标题标签<h1>
sed -n -e "1,4s/<!---date:\(.\+\)-->/<h4>\1 \/ xiahouzuoxin<\/h4>/p" $name >> temp_title.html # 提取日期
sed -n -e "1,4s/<!---keywords:\(.\+\)-->/<h4>Tags: \1<\/h4>/p" $name >> temp_title.html       # 提取关键词
echo "转载请注明出处: <a href="xiahouzuoxin.github.io">xiahouzuoxin.github.io</a>" >> temp_title.html

# 生成评论框
echo "<div class=\"ds-thread\" data-thread-key=\"$title\" data-title=\"$title\" data-url=\"xiahouzuoxin.github.io/notes/html/$title.html\"></div>" > comments.html

pandoc $name --include-in-header temp_head_keywords.html --include-before-body header.html --include-before-body temp_title.html --toc --include-after-body comments.html --include-after-body footer.html -o ${name%.*}".html" -c ../stylesheets/Github.css
echo "$name"

rm -f temp_head_keywords.html temp_title.html            # 删除临时文件

      fi
    fi
    done
}

if [ -f $DIR ]; then
    md2html
    exit 0;
fi

if [ -d $DIR ]; then        #如果是目录
    cd $DIR                 #打开目录，然后进入目录进行处理调用
    exit 0;
fi

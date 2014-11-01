#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

touch temp_head_keywords.html temp_title.html # 生成临时文件
sed -n -e "s/<!---title:\(.\+\)-->/<title>\1<\/title>/p" $1 > temp_head_keywords.html # 生成<head>中的标题标签
# sed -n -e "s/<!---keywords:\(.\+\)-->/<meta name=\"keywords\" content=\"\1\">/p" $1 >> temp_head_keywords.html # 生成<head>中的关键字标签
sed -n -e "s/<!---title:\(.\+\)-->/<h1>\1<\/h1>/p" $1 > temp_title.html                 # 生成<body>中的标题标签<h1>
sed -n -e "s/<!---date:\(.\+\)-->/<h4>\1 \/ xiahouzuoxin<\/h4>/p" $1 >> temp_title.html # 提取日期
sed -n -e "s/<!---keywords:\(.\+\)-->/<h4>Tags: \1<\/h4>/p" $1 >> temp_title.html             # 提取关键词
echo "转载请注明出处: <a href="xiahouzuoxin.github.io">xiahouzuoxin.github.io</a>" >> temp_title.html

pandoc $1 --include-in-header temp_head_keywords.html --include-before-body header.html --include-before-body temp_title.html --toc --include-after-body footer.html -o ${1%.*}".html" -c ../stylesheets/Github.css
echo "$1"

rm -f temp_head_keywords.html temp_title.html            # 删除临时文件


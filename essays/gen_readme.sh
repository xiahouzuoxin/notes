#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash
function index()
{
    echo "为了编辑方便，自2014年10月23日之后，所有文档格式都改用Pandoc转html，Pandoc的扩展部分Markdown语法Github并不支持，因此为浏览方便，请转向<http://xiahouzuoxin.github.io>！" > ../README.md 

    echo "" >> ../README.md
    for name in `ls *.md`
    do
    if [ ! -d $name ];then
      if [ "${name##*.}" == "md" ]; then
          echo "- [${name%.*}](./essays/$name)" >> ../README.md
      fi
    fi
    done
}

if [ -f $DIR ]; then
    index
    exit 0;
fi

if [ -d $DIR ]; then        #如果是目录
    cd $DIR                 #打开目录，然后进入目录进行处理调用
    exit 0;
fi

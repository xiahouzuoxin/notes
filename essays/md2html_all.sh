#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

if [ -f $DIR ]; then
    for name in `ls *.md`
	do
		if [ "${name##*.}" == "md" ]; then
			./md2html.sh $name
			# echo "$name"
		fi
	done
    exit 0;
fi

if [ -d $DIR ]; then        #如果是目录
    cd $DIR                 #打开目录，然后进入目录进行处理调用
    exit 0;
fi

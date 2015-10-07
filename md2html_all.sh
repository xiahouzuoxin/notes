#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

for name in `ls *.md`
do
# if [ -f $DIR ]; then

if [ "${name##*.}" == "md" ]; then
	./md2html.sh $name
	# echo "$name"
fi
# fi
done


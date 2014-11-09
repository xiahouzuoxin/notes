#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

for name in `ls *.md`
do
if [ -f $DIR ]; then

if [ "${name##*.}" == "md" ]; then

	if [ "$name" == "README.md" ]; then
		touch tmp_readme.md
		sed -e 's/essays/html/g;s/.md/.html/g' README.md > tmp_readme.md
		pandoc tmp_readme.md --include-before-body header.html --include-after-body footer.html -o ${name%.*}".html" -c ./stylesheets/Github.css
		rm tmp_readme.md
	else
		pandoc $name --include-before-body header.html --include-after-body footer.html -o ${name%.*}".html" -c ./stylesheets/Github.css
	fi
	echo "$name"
	
fi
fi
done


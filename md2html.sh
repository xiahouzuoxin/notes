#########################################################################
# FileName : md2html.sh
# Author   : xiahouzuoxin @163.com
# Date     : 2014/10/23 19:51:29
#########################################################################
# 
#!/bin/bash

if [ "$1" == "README.md" ]; then
	touch tmp_readme.md
	sed -e 's/essays/html/g;s/.md/.html/g' README.md > tmp_readme.md
	pandoc tmp_readme.md --include-before-body header.html --include-after-body footer.html -o ${1%.*}".html" -c ./stylesheets/Github.css
	rm tmp_readme.md
elif [ "$1" == "resume.md" ]; then
	pandoc $1 -o resume.html -c ./stylesheets/Clearness.css
elif [ "$1" == "resume_en.md" ]; then
	pandoc $1 -o resume_en.html -c ./stylesheets/Clearness.css	
else
	pandoc $1 --include-before-body header.html --include-after-body footer.html -o ${1%.*}".html" -c ./stylesheets/Github.css
fi
echo "$1"


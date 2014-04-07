# target, subdir, objects in current dir
TARGET	= test
SUBDIRS	= src
OBJECTS	= 


all:subdirs ${OBJECTS}
	${CC} -o ${TARGET} $$(find ./${SUBDIRS} -name '*.o') ${LDFLAGS} ${INCLUDES}


clean:cleansubdirs
	rm -f ${TARGET} ${OBJECTS}


# path of "make global scripts"
# NOTE, use absolute path. export once, use in all subdirs
export PROJECTPATH=${PWD}
export MAKEINCLUDE=${PROJECTPATH}/makeconfig/make.global

# include "make global scripts"
include ${MAKEINCLUDE}

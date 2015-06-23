#graham greving
#ggreving

GCC      = gcc -g -O0 -Wall -Wextra -std=gnu99

CSOURCES = l8stat.c
SOURCES  = ${CSOURCES} Makefile README
EXECBINS = l8stat
SUBMIT   = submit cmps012b-wm.f12 lab8 ${SOURCES}

all : ${EXECBINS}

% : %.c
	- checksource $<
	${GCC} $< -o $@

clean :
	- rm core

spotless : clean
	- rm ${EXECBINS}

git:
	- git commit -a

submit : ${SOURCES}
	${SUBMIT} ${SOURCES}

again : ${SOURCES}
	gmake --no-print-directory spotless ci all lis


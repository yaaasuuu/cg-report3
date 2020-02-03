CC	= gcc
CPP	= g++
LIBDIR	= /usr/X11R6/lib
GLLIBS	= -lglut -lGLU -lGL
XLIBS	= -lXmu -lXi -lXext -lX11
LIBS	= $(GLLIBS) $(XLIBS) -lm

.c	:
	$(CC) -DGL_GLEXT_PROTOTYPES -L$(LIBDIR) $(CFLAGS) $< $(LIBS) -o $@

.cc	:
	$(CPP) -DGL_GLEXT_PROTOTYPES -L$(LIBDIR) $(CFLAGS) $< $(LIBS) -o $@

all	:
	@echo usage: make xxx

clean	:
	rm -f *.o

LDLIBS = -lm   -lglut -lGL -lGLU -lX11 -lXmu -lXi -L/usr/X11R6/lib
all:showBMP showBMP_pg

showBMP_pg: showBMP.o readBMP.o writeBMP.o
	gcc -pg -o showBMP_pg readBMP.o writeBMP.o showBMP.o $(LDLIBS)
	
showBMP: showBMP.o readBMP.o writeBMP.o
	gcc -o showBMP readBMP.o writeBMP.o showBMP.o $(LDLIBS)

readBMP.o: readBMP.c readBMP.h
	gcc -o readBMP.o -c readBMP.c

writeBMP.o: writeBMP.c writeBMP.h readBMP.h
	gcc -o writeBMP.o -c writeBMP.c

showBMP.o: showBMP.c myfunction.c
	gcc -g -o showBMP.o -c showBMP.c




clean:
	rm -f showBMP.o
	rm -f writeBMP.o
	rm -f showBMP
	rm -f showBMP_pg
	rm -f readBMP.o
	rm -f writeBMP.o
	rm -f gmon.out
	


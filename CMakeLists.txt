cmake_minimum_required(VERSION 3.0)
project(EX5_mivne C)

set(CMAKE_C_STANDARD 11)

add_executable(ex5  readBMP.c readBMP.h  writeBMP.c writeBMP.h  showBMP.c myfunction.c)
find_library(-lm   -lglut -lGL -lGLU -lX11 -lXmu -lXi -L/usr/X11R6/lib)
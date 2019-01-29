CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp
PROG = main

OPENCV = `pkg-config opencv --cflags --libs`
LIBS = $(OPENCV)
LIBS += -lrealsense2 

$(PROG):$(SRCS)
	$(CC) -std=c++11 -O2 $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

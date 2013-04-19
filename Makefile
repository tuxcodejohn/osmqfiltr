#------------------------------------------------------------------------------
#
#  Makefile for Osmium testing...

CXX = g++
#CXX = clang++

#CXXFLAGS = -g
CXXFLAGS = -O2 

CXXFLAGS += -march=native

CXXFLAGS += -Wall -Wextra -pedantic -Wctor-dtor-privacy -Wnon-virtual-dtor -Woverloaded-virtual -Wsign-promo -Wno-long-long

CXXFLAGS += -D_LARGEFILE_SOURCE -D_FILE_OFFSET_BITS=64
CXXFLAGS += -I./osmium/include/

# remove this if you do not want debugging to be compiled in
#CXXFLAGS += -DOSMIUM_WITH_DEBUG

LIB_EXPAT  = -lexpat
LIB_PBF    = -lz -lpthread -lprotobuf-lite -losmpbf

LDFLAGS = $(LIB_EXPAT) $(LIB_PBF)

PROGRAMS = osmium_dvb


.PHONY: all clean

all: $(PROGRAMS)

osmium_dvb: osmium_dvb.cpp
	$(CXX) $(CXXFLAGS)  -o $@ $< $(LDFLAGS) 
	strip $@
clean:
	rm -f *.o core $(PROGRAMS)


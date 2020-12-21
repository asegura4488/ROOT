######################
### Edit this part ###
######################

#ROOTSYS       = /cygdrive/c/root5.12/root
#ROOTSYS       = /usr/local/root
CXX           = g++
LD            = g++

#############################
### Do NOT edit this part ###
#############################

#CXXFLAGS      = -O -Wall -qnoro -qnoroconst -qmaxmem=-1 -I$(ROOTSYS)/include
CXXFLAGS      = -O -Wall -std=c++11 -I$(ROOTSYS)/include
LDFLAGS       = -g
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
#ROOTLIBS      = -L$(ROOTSYS)/lib -lRoot -lCint
LIBS          = $(ROOTLIBS) -lm
LIBSALL       = $(ROOTLIBS) -lXm -lXt -lX11 -lm -lPW -lcurses
 

phasespace_gen5.0:  phasespace_gen5.0.o
	$(LD) $(LDFLAGS) phasespace_gen5.0.o $(LIBS) -o phasespace_gen5.0 
 
.C.o:
	$(CXX) $(CXXFLAGS) -c $<

clean:
 
	rm phasespace_gen5.0

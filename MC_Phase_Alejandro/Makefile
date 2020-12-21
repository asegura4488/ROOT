######################
### Edit this part ###
######################

//ROOTSYS     = /cygdrive/c/root5.12/root
ROOTSYS       = /usr/local/root
CXX           = g++
LD            = g++

#############################
### Do NOT edit this part ###
#############################

CXXFLAGS      = -O -Wall -I$(ROOTSYS)/include 
LDFLAGS       = -g
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
#ROOTLIBS      = -L$(ROOTSYS)/lib -lRoot -lCint
LIBS          = $(ROOTLIBS) -lm
LIBSALL       = $(ROOTLIBS) -lXm -lXt -lX11 -lm -lPW -lcurses
 

proceso:  proceso.o
	$(LD) $(LDFLAGS) proceso.o $(LIBS) -o proceso 
 
.C.o:
	
	$(CXX) $(CXXFLAGS) -c $<
clean: 
	rm *.o 
	rm *.dat
	rm *.root
	rm proceso

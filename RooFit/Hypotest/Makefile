CXX = g++

SRCDIR = src
INCDIR = include
OBJDIR = obj
EXE = HypoTest

ROOTCFLAGS = $(shell root-config --cflags) -O2
ROOTLIBS = $(shell root-config --libs) -O2

CXXFLAGS = $(ROOTCFLAGS) -I./$(INCDIR) -std=c++11 -Wall
LDFLAGS = $(ROOTLIBS) 
LDFLAGS += -lRooFit -lRooStats -lMinuit -lMinuit2 -lHistFactory 

SOURCES = $(wildcard $(SRCDIR)/*.cc)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cc=$(OBJDIR)/%.o)



all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ 

$(OBJDIR)/main.o: $(SRCDIR)/main.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cc $(INCDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

%: $(OBJDIR)/%.o
	$(CXX) -o $@ $< 

show:
	@ls $(OBJECTS)

clean: 
	@ls $(OBJDIR)
	@rm -f $(EXE) $(OBJECTS)

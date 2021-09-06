CPP    = g++
RM     = rm -f
OBJS   = mainTeste.o \
         Edge.o \
         Graph.o \
         main.o \
         Node.o

LIBS   =
CFLAGS =

.PHONY: Projeto.exe clean clean-after

all: Projeto.exe

clean:
	$(RM) $(OBJS) Projeto.exe

clean-after:
	$(RM) $(OBJS)

Projeto.exe: $(OBJS)
	$(CPP) -Wall -s -o $@ $(OBJS) $(LIBS)

mainTeste.o: mainTeste.cpp Graph.h Node.h Edge.h Graph.cpp Node.cpp Edge.cpp
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

Edge.o: Edge.cpp Edge.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

Graph.o: Graph.cpp Graph.h Node.h Edge.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

main.o: main.cpp Graph.h Node.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)

Node.o: Node.cpp Node.h Edge.h
	$(CPP) -Wall -s -c $< -o $@ $(CFLAGS)


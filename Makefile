CXX=g++
CXXFLAGS=-Wall -Wextra -Werror -std=c++11
# CXXFLAGS=-Wall -Wextra -Werror -std=c++11 -fsanitize=address -g

# Add the AddressSanitizer runtime library flag
LDFLAGS=-lasan

REP_CARTE=./CARTE
REP_TRESOR=$(REP_CARTE)/TRESOR
REP_VICTOIRE=$(REP_CARTE)/VICTOIRE
REP_ROYAUME=$(REP_CARTE)/ROYAUME

REP_PARTIE=./PARTIE

REP_PHASE=./PHASE

LISTE_REP = -I$(REP_CARTE) -I$(REP_TRESOR) -I$(REP_VICTOIRE) -I$(REP_PHASE) -I$(REP_ROYAUME) -I$(REP_PARTIE)

SOURCES=$(wildcard $(REP_CARTE)/*.cpp) $(wildcard $(REP_PHASE)/*.cpp) $(wildcard $(REP_TRESOR)/*.cpp) $(wildcard $(REP_VICTOIRE)/*.cpp) $(wildcard $(REP_ROYAUME)/*.cpp)  $(wildcard $(REP_PARTIE)/*.cpp)

OBJECTS=$(SOURCES:.cpp=.o)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LISTE_REP) $< -c -o $@

lancement: $(OBJECTS) lancement.o
	$(CXX) $^ -o $@
# $(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

.PHONY: run clean

run: lancement
	./lancement

clean:
	rm -f $(OBJECTS) lancement *~ *.core


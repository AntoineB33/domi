
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: Phase.o PhaseAchat.o PhaseAction.o PhaseAjustement.o test.o
	$(CXX) $^ -o $@


.PHONY: run clean

run: test
	./$<

clean:
	rm -f *.o *~ *.core 



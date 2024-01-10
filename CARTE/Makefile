
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: Carte.o Tresor.o Or.o test.o
	$(CXX) $^ -o $@


.PHONY: run clean

run: test
	./$<

clean:
	rm -f *.o *~ *.core 



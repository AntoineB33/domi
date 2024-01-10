
CXX=g++
CXXFLAGS=-Wall -Wextra -Werror

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -c -o $@

test: A.o C.o test.o
	$(CXX) $^ -o $@


.PHONY: run clean

run: test
	./$<

clean:
	rm -f *.o *~ *.core 



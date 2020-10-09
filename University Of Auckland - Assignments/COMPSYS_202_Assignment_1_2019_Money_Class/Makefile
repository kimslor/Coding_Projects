CXX = g++
CXXFLAGS = -Wall -g

money_test: test.cpp Money.cpp Money.h basics.cpp basics.h
	$(CXX) $(CXXFLAGS) -o money_test $^

all: clean money_test

run: money_test
	./money_test
	
clean:
	rm -f money_test
	
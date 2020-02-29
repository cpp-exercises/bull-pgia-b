#!make -f

all: test
	./$<

test:  OurTest.o DummyChoosers.o DummyGuessers.o play.o calculate.o SmartGuesser.o
	clang++-5.0 -std=c++17 $^ -o test

%.o: %.cpp
	clang++-5.0 -std=c++17 --compile $< -o $@

OurDemo.o: play.hpp calculate.hpp Chooser.hpp DummyChoosers.hpp Guesser.hpp DummyGuessers.hpp 
OurTest.o: play.hpp calculate.hpp Chooser.hpp DummyChoosers.hpp Guesser.hpp DummyGuessers.hpp badkan.hpp
play.o: play.hpp calculate.hpp Chooser.hpp Guesser.hpp
calculate.o: calculate.hpp Chooser.hpp Guesser.hpp 
DummyChoosers.o: Chooser.hpp
DummyGuessers.o: Guesser.hpp calculate.hpp
SmartGuesser.o:  SmartGuesser.hpp Guesser.hpp 

%Test%.o: badkan.hpp

clean:
	rm -f *.o demo our_test your_test

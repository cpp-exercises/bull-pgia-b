/**
 * A demo program for bull-pgia.
 * 
 * @author Erel Segal-Halevi
 * @since  2019-04
 */


#include <iostream>
using namespace std;

#include "play.hpp"
#include "DummyChoosers.hpp"
#include "DummyGuessers.hpp"
#include "SmartGuesser.hpp"
#include "badkan.hpp"
#include "calculate.hpp"

using namespace bullpgia;

int main() {

	badkan::TestCase testcase;
	int grade=0;
	int signal = setjmp(badkan::longjmp_buffer);
	if (signal == 0) {

		// BASIC TESTS
		ConstantChooser c2828{"2828"}, c0{"0"}, c1234{"1234"}, c12345{"12345"}, c9999{"9999"};
		ConstantGuesser g2828{"2828"}, g0{"0"}, g1234{"1234"}, g12345{"12345"}, g9999{"9999"};		

		testcase.setname("Play with dummy choosers and guessers")
		.CHECK_EQUAL(play(c1234, g1234, 4, 100), 1)      // guesser wins in one turn.
		.CHECK_EQUAL(play(c1234, g9999, 4, 100), 101)    // guesser loses by running out of turns 
		.CHECK_EQUAL(play(c1234, g12345, 4, 100), 101)   // guesser loses technically by making an illegal guess (too long).
		.CHECK_EQUAL(play(c12345, g1234, 4, 100), 0)     // chooser loses technically by choosing an illegal number (too long).
		;

		RandomChooser randy;
		SmartGuesser smarty;
		testcase.setname("Smart guesser - length 1");
		for (uint i=0; i<10; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 1, 200)<=100, true);  // smarty should always win in at most 100 turns!
		}
		testcase.setname("Smart guesser - length 2");
		for (uint i=0; i<20; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 2, 200)<=100, true);  // smarty should always win in at most 100 turns!
		}
		testcase.setname("Smart guesser - length 3");
		for (uint i=0; i<30; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 3, 200)<=100, true);  // smarty should always win in at most 100 turns!
		}
		testcase.setname("Smart guesser - length 4");
		for (uint i=0; i<40; ++i) {
			testcase.CHECK_EQUAL(play(randy, smarty, 4, 200)<=100, true);  // smarty should always win in at most 100 turns!
		}


	// Naor Eliav and Michael Garousi
	// https://github.com/naor94/BullPgia/blob/master/Test.cpp
		testcase.setname("Calculate bull and pgia - NM")
		.CHECK_OUTPUT(calculateBullAndPgia("1234","1234"), "4,0")      // 4 bull, 0 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("1234","4321"), "0,4")      // 0 bull, 4 pgia
		.CHECK_OUTPUT(calculateBullAndPgia("0000","9999"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("111","111"), "3,0")
		.CHECK_OUTPUT(calculateBullAndPgia("555","655"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("001","1"), "0,1") 
		.CHECK_OUTPUT(calculateBullAndPgia("010","1"), "0,1")     
		.CHECK_OUTPUT(calculateBullAndPgia("100","1"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("4","1"), "0,0") 
		.CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("01","10"), "0,2")
		.CHECK_OUTPUT(calculateBullAndPgia("10","10"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("9876543210","9876543210"), "10,0")  
		.CHECK_OUTPUT(calculateBullAndPgia("987654321","123456789"), "1,8") 
		.CHECK_OUTPUT(calculateBullAndPgia("4567","7654"), "0,4") 
		;

		// Liad Cohen and Timor Sharabi
		// https://github.com/xposionn/Bull-Pgia/blob/master/Test.cpp
		testcase.setname("100 percent bullseye LT")
		.CHECK_OUTPUT(calculateBullAndPgia("9999","9999"), "4,0")
		.CHECK_OUTPUT(calculateBullAndPgia("8787","8787"), "4,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1","1"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("55","55"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("57","57"), "2,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1234567","1234567"), "7,0")
		.CHECK_OUTPUT(calculateBullAndPgia("852852852","852852852"), "9,0")
		;

		testcase.setname("short and long chooser-guesser combinations LT")
		.CHECK_OUTPUT(calculateBullAndPgia("9","8"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("87","79"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("789654","000124"), "1,0")
		.CHECK_OUTPUT(calculateBullAndPgia("000000","111111"), "0,0")
		.CHECK_OUTPUT(calculateBullAndPgia("8888777999","5700000000"), "0,1")
		.CHECK_OUTPUT(calculateBullAndPgia("987654321","123456789"), "1,8") //only 5 is bull, all others are pgia
		.CHECK_OUTPUT(calculateBullAndPgia("852852851","852852857"), "8,0")
		.CHECK_OUTPUT(calculateBullAndPgia("1573","1875"), "2,1")	   // 2 bull, 1 pgia
		;

		testcase.setname("play function LT")
		.CHECK_EQUAL(play(c1234, g1234, 4, 5), 1) //guesser should win in 1 turn even with max turns of 5 and not 100.
		.CHECK_EQUAL(play(c0, g0, 1, 5), 1) //1 turn winning
		.CHECK_EQUAL(play(c1234, g0, 1, 5), 0) // chooser loses technical
		.CHECK_EQUAL(play(c0, g12345, 1, 100), 101) // guesser loses technical
		;		

		// Moran Oshia and Israel Buskila
		// https://github.com/MoranOshia/Ex4_Cpp/blob/master/Test.cpp

		testcase.setname("all digit are in the guess MI")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "64532"), "0,5")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "23456"), "5,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "32546"), "1,4")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "23452"), "4,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "34561"), "0,4")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "25346"), "2,3")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "23546"), "3,2")				
				;


		testcase.setname("with digits are not in the guess MI")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "17890"), "0,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "78950"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "78269"), "0,2")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "13487"), "2,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "34687"), "0,3")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "23489"), "3,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "82734"), "0,3")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "73456"), "4,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "34567"), "0,4")
				;

		testcase.setname("Repeated digit in the guess MI")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "22222"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "33333"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "44444"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "55555"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "66666"), "1,0")
				;
				
		testcase.setname("Repeated digit not in the guess MI")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "11111"), "0,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "77777"), "0,0")
				.CHECK_OUTPUT(calculateBullAndPgia("23456", "88888"), "0,0")
				
				.CHECK_OUTPUT(calculateBullAndPgia("1113", "1111"), "3,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1113", "3113"), "3,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1113", "3331"), "0,2")
				
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "1111"), "3,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "2222"), "1,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "2111"), "2,2")
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "2112"), "1,2")
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "2221"), "2,0")
				.CHECK_OUTPUT(calculateBullAndPgia("1211", "1112"), "2,2")
				;
	
		testcase.setname("Wikipedia")
		// The example in https://en.wikipedia.org/wiki/Mastermind_(board_game)#Gameplay_and_rules
				.CHECK_OUTPUT(calculateBullAndPgia("2211", "2221"), "3,0")
				;

		testcase.print();
    grade = testcase.grade();
	} else {
		testcase.print_signal(signal);
		grade = 0;
	}
  cout <<  grade << " " << "asdfasdghw54yj344lj6h" << endl;
	return 0;
}


#pragma once
/**
 * Author: Erel Segal-Halevi
 * Since:  2019-04
 */

#include <iostream>
using std::string, std::ostream;

namespace bullpgia {
	struct Reply {
		int bull;
		int pgia;
	};
	Reply calculateBullAndPgia(string choice, string guess);
}


inline ostream& operator<< (ostream& out, const bullpgia::Reply& r) {
	return (out << r.bull << "," << r.pgia);
}

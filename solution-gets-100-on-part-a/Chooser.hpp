#pragma once
#include <string>

namespace bullpgia {
	struct Chooser {
		virtual std::string choose(uint length) = 0;
	};
}

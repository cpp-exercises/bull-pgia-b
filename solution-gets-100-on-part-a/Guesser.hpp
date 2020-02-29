#pragma once
#include <string>
#include "calculate.hpp"

namespace bullpgia {
	class Guesser {
		protected:
			uint length;
		public:
			virtual void startNewGame(uint length) {
				this->length = length;
			}
			virtual std::string guess() = 0;
			virtual void learn(const Reply& reply)  { }
			virtual ~Guesser() {}
	};
}

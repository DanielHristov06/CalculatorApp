#include <iostream>
#include "Token.h"

int main() {
	for (const auto& token : calc::tokenize("12.5 + (2 * 4)")) {
		std::cout << token;
	}

	return 0;
}
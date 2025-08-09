#include <iostream>
#include "Parser.h"

int main() {
	std::string s = "1 + (2 + 3) * 2";
	std::cout << "Result: " << calc::evaluate(s) << "\n";

	return 0;
}
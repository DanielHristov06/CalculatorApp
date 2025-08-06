#include <iostream>
#include <string>
#include <sstream>
#include <vector>

static std::vector<std::string> tokenize(const std::string& str) {
	std::stringstream ss(str);
	std::string buffer;
	std::vector<std::string> tokens;

	while (ss >> buffer) {
		tokens.push_back(buffer);
	}

	return tokens;
}

int main() {
	for (const auto& token : tokenize("Hello world from tokenizer!")) {
		std::cout << token << "\n";
	}

	return 0;
}
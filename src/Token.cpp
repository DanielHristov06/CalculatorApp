#include "Token.h"

std::ostream& calc::operator<<(std::ostream& os, const Token& token) {
	os << token.value;
	return os;
}

std::vector<calc::Token> calc::tokenize(const std::string& input) {
	std::vector<Token> tokens;
	std::string numberBuffer;

	for (size_t i = 0; i < input.length(); ++i) {
		char c = input[i];

		if (isdigit(c) || c == '.') {
			numberBuffer += c;
		}
		else {
			if (!numberBuffer.empty()) {
				tokens.push_back(Token{ TokenType::Number, numberBuffer });
				numberBuffer.clear();
			}

			if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
				tokens.push_back(Token{ TokenType::Operator, std::string(1, c) });
			}
			else if (c == '(') {
				tokens.push_back(Token{ TokenType::LeftParen, "(" });
			}
			else if (c == ')') {
				tokens.push_back(Token{ TokenType::RightParen, ")" });
			}
		}
	}

	if (!numberBuffer.empty()) {
		tokens.push_back(Token{ TokenType::Number, numberBuffer });
	}

	return tokens;
}
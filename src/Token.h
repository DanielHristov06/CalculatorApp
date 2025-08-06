#pragma once

#include <string>
#include <ostream>
#include <vector>

namespace calc {
	enum class TokenType {
		Number,
		Operator,
		LeftParen,
		RightParen
	};

	struct Token {
		TokenType type;
		std::string value;
	};

	std::ostream& operator<<(std::ostream& os, const Token& token);

	std::vector<Token> tokenize(const std::string& input);
}
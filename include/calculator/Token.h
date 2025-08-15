#pragma once

#include <string>
#include <ostream>
#include <vector>

namespace calc {
	enum class TokenType : uint8_t {
		Number,
		Operator,
		LeftParen,
		RightParen
	};

	enum class Op : uint8_t {
		Plus,
		Minus,
		Mul,
		Div,
		Pow
	};

	struct Token {
		TokenType type = TokenType::Number;
		std::string value{}; // original text (useful for debuging/printing)
		double number = 0.0; // valid if kind == Number
		Op op = Op::Plus;	 // valid if kind == Operator
	};

	std::ostream& operator<<(std::ostream& os, const Token& token);

	int precedence(Op op);
	bool leftAssociative(Op op);
	bool charToOp(char c, Op& out);

	std::vector<Token> tokenize(const std::string& input);
}
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

	enum class Op {
		Plus,
		Minus,
		Mul,
		Div,
		Pow
	};

	struct Token {
		TokenType type;
		std::string value; // original text (useful for debuging/printing)
		double number;	   // valid if kind == Number
		Op op;			   // valid if kind == Operator
	};

	std::ostream& operator<<(std::ostream& os, const Token& token);

	int precedence(Op op);
	bool leftAssociative(Op op);
	static bool charToOp(char c, Op& out);

	std::vector<Token> tokenize(const std::string& input);
}
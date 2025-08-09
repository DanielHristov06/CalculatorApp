#include "Token.h"
#include <iostream>

std::ostream& calc::operator<<(std::ostream& os, const Token& token) {
	os << token.value;
	return os;
}

int calc::precedence(Op op) {
	switch (op) {
		case Op::Plus:  return 1;
		case Op::Minus: return 1;
		case Op::Mul:   return 2;
		case Op::Div:   return 2;
		case Op::Pow:   return 3;
	}
	return 0;
}

bool calc::leftAssociative(Op op) {
	return op != Op::Pow; // + - * / are left-associative; ^ is right-associative
}

bool calc::charToOp(char c, Op& out) {
	switch (c) {
		case '+': out = Op::Plus; return true;
		case '-': out = Op::Minus; return true;
		case '*': out = Op::Mul; return true;
		case '/': out = Op::Div; return true;
		case '^': out = Op::Pow; return true;
		default: return false;
	}
}

std::vector<calc::Token> calc::tokenize(const std::string& input) {
	std::vector<Token> tokens;
	std::string numberBuffer;

	auto flushNumber = [&]() {
		if (!numberBuffer.empty()) {
			Token t;
			t.type = TokenType::Number;
			t.value = numberBuffer;
			t.number = std::stod(numberBuffer);
			tokens.push_back(t);
			numberBuffer.clear();
		}
	};

	for (size_t i = 0; i < input.length(); ++i) { 
		char c = input[i];

		if (std::isspace(static_cast<unsigned char>(c))) {
			flushNumber();
			continue;
		}

		if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
			numberBuffer += c;
			continue;
		}

		// anything that's not part of a number ends the current number
		flushNumber();

		if (c == '(') {
			tokens.push_back(Token{ TokenType::LeftParen, "(", 0.0, {} });
		}
		else if (c == ')') {
			tokens.push_back(Token{ TokenType::RightParen, ")", 0.0, {} });
		}
		else {
			Op op;
			if (!charToOp(c, op)) {
				std::cerr << "Unknown character: " << c << "\n";
			}
			Token t;
			t.type = TokenType::Operator;
			t.value = std::string(1, c);
			t.op = op;
			tokens.push_back(t);
		}
	}

	flushNumber();
	return tokens;
}
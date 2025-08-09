#pragma once

#include <vector>
#include "Token.h"

namespace calc {
	// Convert infix to postfix (RPN)
	std::vector<Token> toPostfix(const std::vector<Token>& infix);

	// Evaluate a postfix token stream and return the rsult
	double evalPostfix(const std::vector<Token>& rpn);

	double evaluate(const std::string& expr);
}
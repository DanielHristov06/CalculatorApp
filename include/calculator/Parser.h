#pragma once

#include <vector>
#include <expected>
#include "Token.h"

namespace calc {
	// Convert infix to postfix (RPN)
	std::expected<std::vector<Token>, std::string> toPostfix(const std::vector<Token>& infix);

	// Evaluate a postfix token stream and return the rsult
	std::expected<double, std::string> evalPostfix(const std::vector<Token>& rpn);

	std::expected<double, std::string> evaluate(const std::string& expr);
}
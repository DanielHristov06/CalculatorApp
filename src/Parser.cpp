#include "Parser.h"
#include <stack>
#include <iostream>

std::vector<calc::Token> calc::toPostfix(const std::vector<calc::Token>& infix) {
	std::vector<Token> output;
	output.reserve(infix.size());
	std::stack<Token> opStack;

	for (const Token& t : infix) {
		switch (t.type)
		{
		case TokenType::Number:
			// numbers go straight to the outpit
			output.push_back(t);
			break;
		case TokenType::Operator:
			// while top of stack is an operator with higher precedence
			// OR (equal precedence AND current operator is left-associative)
			// pop stack to output
			while (!opStack.empty() && opStack.top().type == TokenType::Operator) {
				const Token& o2 = opStack.top();
				int p1 = precedence(t.op);
				int p2 = precedence(o2.op);
				if (p2 > p1 || (p2 == p1 && leftAssociative(t.op))) {
					output.push_back(o2);
					opStack.pop();
				}
				else break;
			}
			// push current operator
			opStack.push(t);
			break;
		case TokenType::LeftParen:
			opStack.push(t);
			break;
		case TokenType::RightParen:
			// pop until we find a left paren
			while (!opStack.empty() && opStack.top().type != TokenType::LeftParen) {
				output.push_back(opStack.top());
				opStack.pop();
			}
			if (opStack.empty()) {
				std::cerr << "Mismatched parentheses: missing '('\n";
			}
			// discard the '('
			opStack.pop();
			break;
		}
	}

	// After reading all tokens, pop reaining operators
	while (!opStack.empty()) {
		if (opStack.top().type == TokenType::LeftParen) {
			std::cerr << "Mismatched parentheses: missing ')'\n";
		}
		output.push_back(opStack.top());
		opStack.pop();
	}

	return output;
}

double calc::evalPostfix(const std::vector<calc::Token>& rpn) {
	std::stack<double> st;

	for (const Token& t : rpn) {
		if (t.type == TokenType::Number) {
			st.push(t.number);
			continue;
		}

		if (t.type == TokenType::Operator) {
			if (st.size() < 2) {
				std::cerr << "Malformed expression: operator without two operands\n";
			}

			double right = st.top();
			st.pop();
			double left = st.top();
			st.pop();

			double res = 0.0;
			switch (t.op)
			{
			case Op::Plus: res = left + right; break;
			case Op::Minus: res = left - right; break;
			case Op::Mul: res = left * right; break;
			case Op::Div:
				if (right == 0.0) std::cerr << "Division by zero\n"; break;
				res = left / right;
				break;
			case Op::Pow: res = std::pow(left, right); break;
			}
			st.push(res);
			continue;
		}

		// Parentheses neer appear in RPN: if they do, it's a bug upstream.
		std::cerr << "Unexpected token in RPN\n";
	}
	
	if (st.size() != 1) std::cerr << "Malformed expression: leftover values\n";
	return st.top();
}

double calc::evaluate(const std::string& expr) {
	auto tokens = tokenize(expr);
	auto rpn = toPostfix(tokens);
	return evalPostfix(rpn);
}
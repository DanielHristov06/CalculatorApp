#include "calculator/Parser.h"
#include <stack>

namespace calc {
	std::expected<std::vector<Token>, std::string> toPostfix(const std::vector<Token>& infix) {
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
					return std::unexpected("Mismatched parentheses: missing '('");
				}
				// discard the '('
				opStack.pop();
				break;
			}
		}

		// After reading all tokens, pop reaining operators
		while (!opStack.empty()) {
			if (opStack.top().type == TokenType::LeftParen) {
				return std::unexpected("Mismatched parentheses: missing ')'");
			}
			output.push_back(opStack.top());
			opStack.pop();
		}

		return output;
	}

	std::expected<double, std::string> evalPostfix(const std::vector<Token>& rpn) {
		std::stack<double> st;

		for (const Token& t : rpn) {
			if (t.type == TokenType::Number) {
				st.push(t.number);
				continue;
			}

			if (t.type == TokenType::Operator) {
				if (st.size() < 2) {
					return std::unexpected("Malformed expression: operator without two operands");
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
					if (right == 0.0) return std::unexpected("Cannot divide by zero");
					res = left / right;
					break;
				case Op::Pow: res = std::pow(left, right); break;
				}
				st.push(res);
				continue;
			}

			// Parentheses neer appear in RPN: if they do, it's a bug upstream.
			return std::unexpected("Unexpected token in RPN");
		}

		if (st.size() != 1) return std::unexpected("Malformed expression: leftover values");
		return st.top();

	}

	std::expected<double, std::string> evaluate(const std::string& expr) {
		auto tokens = tokenize(expr);
		if (!tokens) return std::unexpected(tokens.error());
		auto rpn = toPostfix(*tokens);
		if (!rpn) return std::unexpected(rpn.error());
		auto answer = evalPostfix(*rpn);
		if (!answer) return std::unexpected(answer.error());
		return answer;
	}
}
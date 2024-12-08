#include "interpreter.hpp"

#include <algorithm>
#include <iostream>
#include <string>

double Interpreter::evalute(const ASTNode* node) {
  if (node->type == "NUMBER") {
    return std::stod(node->value);
  }

  if (node->type == "OPERATION") {
    double left = evalute(node->left.get());
    double right = evalute(node->right.get());

    if (node->value == "+") return left + right;
    if (node->value == "-") return left - right;
    if (node->value == "*") return left * right;
    if (node->value == "/") {
      if (right == 0) throw std::runtime_error("Division by zero");
      return left / right;
    }
  }

  throw std::runtime_error("Unknown node type");
}

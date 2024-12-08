#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.hpp"

class Interpreter {
 public:
  double evalute(const ASTNode* node);
};

#endif
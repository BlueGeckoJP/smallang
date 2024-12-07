#include "parser.hpp"

#include <iostream>
#include <string>

ASTNode::ASTNode(const std::string& n_type, const std::string& n_value,
                 ASTNode* n_left, ASTNode* n_right)
    : type(n_type), value(n_value), left(n_left), right(n_right) {};

ASTNode Parser::parse() { return this->expression(); };

ASTNode Parser::expression() {
  ASTNode left = this->term();

  while (this->current_token_type() == "PLUS" ||
         this->current_token_type() == "MINUS") {
    Token current_op = this->current_token();
    this->consume_token();

    ASTNode right = this->term();
    left = ASTNode("OPERATION", current_op.value, &left, &right);
  }

  return left;
};

ASTNode Parser::term() {
  ASTNode left = this->factor();
  while (this->current_token_type() == "MULTIPLY" ||
         this->current_token_type() == "DIVIDE") {
    Token current_op = this->current_token();
    this->consume_token();

    ASTNode right = this->factor();
    left = ASTNode("OPERATION", current_op.value, &left, &right);
  }

  return left;
};

ASTNode Parser::factor() {
  Token current_token = this->current_token();
  if (current_token.type == "NUMBER") {
    ASTNode node = ASTNode("NUMBER", current_token.value);
    this->consume_token();
    return node;
  } else if (current_token.type == "LEFT_PAREN") {
    this->consume_token();
    ASTNode node = this->expression();

    if (this->current_token_type() != "RIGHT_PAREN") {
      throw std::runtime_error("Expected closing parenthesis");
    }

    this->consume_token();
    return node;
  }
  throw std::runtime_error("UNKNOWN token type");
}

Token Parser::current_token() {
  if (this->current_token_index < static_cast<int>(this->tokens.size())) {
    return this->tokens[this->current_token_index];
  }
  throw std::runtime_error("Unexpected end of input");
}

std::string Parser::current_token_type() { return this->current_token().type; }

void Parser::consume_token() { this->current_token_index++; }

void Parser::print_ast(ASTNode node, int level) {
  std::vector<char> indent_c = {};
  for (int i = 0; level != i; ++i) {
    indent_c.push_back(' ');
  }
  std::string indent(indent_c.begin(), indent_c.end());

  std::cout << indent << node.type << ": " << node.value << std::endl;

  if (node.left) {
    std::cout << indent << "Left: \n";
    this->print_ast(*node.left, level + 1);
  } else if (node.right) {
    std::cout << indent << "Right: \n";
    this->print_ast(*node.right, level + 1);
  }
}
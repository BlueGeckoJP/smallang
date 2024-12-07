#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

#include "token.hpp"

class ASTNode {
 public:
  std::string type = "";
  std::string value = "";
  ASTNode* left = nullptr;
  ASTNode* right = nullptr;

  explicit ASTNode(const std::string& n_type, const std::string& n_value = "",
                   ASTNode* n_left = nullptr, ASTNode* n_right = nullptr);
};

class Parser {
 public:
  int current_token_index = 0;
  std::vector<Token> tokens = {};

  explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {};

  ASTNode parse();

  ASTNode expression();

  ASTNode term();

  ASTNode factor();

  Token current_token();

  std::string current_token_type();

  void consume_token();

  void print_ast(ASTNode node, int level = 0);
};

#endif

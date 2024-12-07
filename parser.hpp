#ifndef PARSER_HPP
#define PARSER_HPP

#include <memory>
#include <string>
#include <vector>

#include "token.hpp"

class ASTNode {
 public:
  std::string type = "";
  std::string value = "";
  std::unique_ptr<ASTNode> left;
  std::unique_ptr<ASTNode> right;

  explicit ASTNode(const std::string& type, const std::string& value = "",
                   std::unique_ptr<ASTNode> left = nullptr,
                   std::unique_ptr<ASTNode> right = nullptr)
      : type(type),
        value(value),
        left(std::move(left)),
        right(std::move(right)) {};
};

class Parser {
 public:
  int current_token_index = 0;
  std::vector<Token> tokens = {};

  explicit Parser(const std::vector<Token>& tokens) : tokens(tokens) {};

  std::unique_ptr<ASTNode> parse();

  std::unique_ptr<ASTNode> expression();

  std::unique_ptr<ASTNode> term();

  std::unique_ptr<ASTNode> factor();

  Token current_token();

  std::string current_token_type();

  void consume_token();

  void print_ast(const ASTNode* node, int level = 0);
};

#endif

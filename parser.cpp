#include "parser.hpp"

#include <iostream>
#include <memory>
#include <string>

std::unique_ptr<ASTNode> Parser::parse() {
  auto result = expression();
  if (current_token_index < static_cast<int>(tokens.size())) {
    throw std::runtime_error("Unexpected tokens at end of expression");
  }
  return result;
};

// FIXME: The order of the calculations is wrong, please correct me
std::unique_ptr<ASTNode> Parser::expression() {
  if (current_token_type() == "NONE") {
    throw std::runtime_error("Unexpected end of input");
  }

  std::unique_ptr<ASTNode> left = term();

  while (current_token_type() == "MULTIPLY" ||
         current_token_type() == "DIVIDE") {
    Token current_op = current_token();
    consume_token();

    std::unique_ptr<ASTNode> right = term();
    left = std::unique_ptr<ASTNode>(new ASTNode(
        "OPERATION", current_op.value, std::move(left), std::move(right)));
  }

  return left;
};

std::unique_ptr<ASTNode> Parser::term() {
  if (current_token_type() == "NONE") {
    throw std::runtime_error("Unexpected end of input");
  }

  std::unique_ptr<ASTNode> left = factor();

  while (current_token_type() == "PLUS" || current_token_type() == "MINUS") {
    Token current_op = current_token();
    consume_token();

    std::unique_ptr<ASTNode> right = factor();
    left = std::unique_ptr<ASTNode>(new ASTNode(
        "OPERATION", current_op.value, std::move(left), std::move(right)));
  }

  return left;
};

std::unique_ptr<ASTNode> Parser::factor() {
  Token c_token = current_token();

  if (c_token.type == "NONE") {
    throw std::runtime_error("Unexpected end of input");
  }

  if (c_token.type == "NUMBER") {
    consume_token();
    return std::unique_ptr<ASTNode>(new ASTNode("NUMBER", c_token.value));
  } else if (c_token.type == "LEFT_PAREN") {
    consume_token();
    std::unique_ptr<ASTNode> node = expression();

    if (current_token_type() != "RIGHT_PAREN") {
      throw std::runtime_error("Expected closing parenthesis");
    }

    consume_token();
    return node;
  }
  throw std::runtime_error("UNKNOWN token type");
}

Token Parser::current_token() {
  if (current_token_index < static_cast<int>(tokens.size())) {
    return tokens[current_token_index];
  }
  return Token("NONE", "");
}

std::string Parser::current_token_type() { return current_token().type; }

void Parser::consume_token() { current_token_index += 1; }

void Parser::print_ast(const ASTNode* node, int level) {
  if (!node) return;

  std::string indent(level * 2, ' ');

  std::cout << indent << node->type << ": " << node->value << std::endl;

  if (node->left) {
    std::cout << indent << "Left: \n";
    print_ast(node->left.get(), level + 1);
  }
  if (node->right) {
    std::cout << indent << "Right: \n";
    print_ast(node->right.get(), level + 1);
  }
}
#include "lexer.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "token.hpp"

Lexer::Lexer(const std::string& text) { input_text = text; }

void Lexer::tokenize() {
  while (this->position < static_cast<int>(this->input_text.size())) {
    char current_char = this->input_text[this->position];

    switch (this->current_state) {
      case State::INITIAL:
        this->handle_initial_state(current_char);
        break;
      case State::NUMBER:
        this->handle_number_state(current_char);
        break;
      case State::IDENTIFIER:
        this->handle_identifier_state(current_char);
        break;
      case State::PLUS:
      case State::MINUS:
      case State::MULTIPLY:
      case State::DIVIDE:
      case State::LEFT_PAREN:
      case State::RIGHT_PAREN:
        this->handle_operator_state();
        break;
    };

    this->position++;
  }

  this->finalize_current_token();
}

void Lexer::handle_initial_state(char c) {
  const char operators[] = {'+', '-', '*', '/', '(', ')'};

  if (isdigit(c)) {
    this->current_state = State::NUMBER;
    this->current_token_value = c;
  } else if (isalpha(c)) {
    this->current_state = State::IDENTIFIER;
    this->current_token_value = c;
  } else if (std::find(std::begin(operators), std::end(operators), c) !=
             std::end(operators)) {
    switch (c) {
      case '+':
        this->current_state = State::PLUS;
        break;
      case '-':
        this->current_state = State::MINUS;
        break;
      case '*':
        this->current_state = State::MULTIPLY;
        break;
      case '/':
        this->current_state = State::DIVIDE;
        break;
      case '(':
        this->current_state = State::LEFT_PAREN;
        break;
      case ')':
        this->current_state = State::RIGHT_PAREN;
        break;
    }
    this->current_token_value = c;
  } else if (!isspace(c)) {
    throw std::runtime_error("unexpected character");
  }
}

void Lexer::handle_number_state(char c) {
  if (isdigit(c)) {
    this->current_token_value += c;
  } else {
    this->finalize_current_token();
    this->current_state = State::INITIAL;
    this->position--;
  }
}

void Lexer::handle_identifier_state(char c) {
  if (isalnum(c)) {
    this->current_token_value += c;
  } else {
    this->finalize_current_token();
    this->current_state = State::INITIAL;
    this->position--;
  }
}

void Lexer::handle_operator_state() {
  this->finalize_current_token();
  this->current_state = State::INITIAL;
  this->position--;
}

void Lexer::finalize_current_token() {
  std::string token_type = this->determine_token_type();
  this->tokens.push_back(Token(token_type, this->current_token_value));
  this->current_token_value = "";
}

std::string Lexer::determine_token_type() {
  switch (this->current_state) {
    case State::NUMBER:
      return "NUMBER";
      break;
    case State::IDENTIFIER:
      return "IDENTIFIER";
      break;
    case State::PLUS:
      return "PLUS";
      break;
    case State::MINUS:
      return "MINUS";
      break;
    case State::MULTIPLY:
      return "MULTIPLY";
      break;
    case State::DIVIDE:
      return "DIVIDE";
      break;
    case State::LEFT_PAREN:
      return "LEFT_PAREN";
      break;
    case State::RIGHT_PAREN:
      return "RIGHT_PAREN";
      break;
    default:
      return "UNKNOWN";
  }
}

void Lexer::debug_print_tokens() {
  for (auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
    std::cout << "Type: " << it->type << ", Value:" << it->value << "\n";
  }
};

#ifndef LEXER_HPP
#define LEXER_HPP

#include <iostream>
#include <vector>

enum class State { INITIAL, NUMBER, IDENTIFIER, OPERATOR };

class Token {
 public:
  std::string type = "";
  std::string value = "";

  Token(const std::string& t_type, const std::string& t_value);
};

class Lexer {
 public:
  std::string input_text = "";
  int position = 0;
  State current_state = State::INITIAL;
  std::vector<Token> tokens = {};
  std::string current_token_value = "";

  explicit Lexer(const std::string& text);

  void tokenize();

  void handle_initial_state(char c);

  void handle_number_state(char c);

  void handle_identifier_state(char c);

  void handle_operator_state();

  void finalize_current_token();

  std::string determine_token_type();

  void debug_print_tokens();
};

#endif
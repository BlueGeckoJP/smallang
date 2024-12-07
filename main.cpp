#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

enum class State { INITIAL, NUMBER, IDENTIFIER, OPERATOR };

class Token {
 public:
  std::string type;
  std::string value;

  Token(const std::string& type, const std::string& value) {
    this->type = type;
    this->value = value;
  }
};

class Lexer {
 public:
  std::string input_text = "";
  int position = 0;
  State current_state = State::INITIAL;
  std::vector<Token> tokens = {};
  std::string current_token_value = "";

  explicit Lexer(const std::string& input_text) {
    this->input_text = input_text;
  }

  void tokenize() {
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
        case State::OPERATOR:
          this->handle_operator_state();
          break;
      };

      this->position++;
    }

    this->finalize_current_token();
  }

  void handle_initial_state(char c) {
    const char operators[] = {'+', '-', '*', '/'};

    if (isdigit(c)) {
      this->current_state = State::NUMBER;
      this->current_token_value = c;
    } else if (isalpha(c)) {
      this->current_state = State::IDENTIFIER;
      this->current_token_value = c;
    } else if (std::find(std::begin(operators), std::end(operators), c) !=
               std::end(operators)) {
      this->current_state = State::OPERATOR;
      this->current_token_value = c;
    } else if (!isspace(c)) {
      throw std::runtime_error("unexpected character");
    }
  }

  void handle_number_state(char c) {
    if (isdigit(c)) {
      this->current_token_value += c;
    } else {
      this->finalize_current_token();
      this->current_state = State::INITIAL;
      this->position--;
    }
  }

  void handle_identifier_state(char c) {
    if (isalnum(c)) {
      this->current_token_value += c;
    } else {
      this->finalize_current_token();
      this->current_state = State::INITIAL;
      this->position--;
    }
  }

  void handle_operator_state() {
    this->finalize_current_token();
    this->current_state = State::INITIAL;
    this->position--;
  }

  void finalize_current_token() {
    std::string token_type = this->determine_token_type();
    this->tokens.push_back(Token(token_type, this->current_token_value));
    this->current_token_value = "";
  }

  std::string determine_token_type() {
    switch (this->current_state) {
      case State::NUMBER:
        return "NUMBER";
      case State::IDENTIFIER:
        return "IDENTIFIER";
      case State::OPERATOR:
        return "OPERATOR";
      default:
        return "UNKNOWN";
    }
  }

  void debug_print_tokens() {
    for (auto it = this->tokens.begin(); it != this->tokens.end(); ++it) {
      std::cout << "Type: " << it->type << ", Value:" << it->value << "\n";
    }
  }
};

int main(int, char**) {
  std::string input_text = "add 123 + 456";
  Lexer lexer = Lexer(input_text);
  lexer.tokenize();
  lexer.debug_print_tokens();
}

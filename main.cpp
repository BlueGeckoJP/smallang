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

      // TODO: Implement this
      switch (this->current_state) {
        case State::INITIAL:
        case State::NUMBER:
        case State::IDENTIFIER:
        case State::OPERATOR:
          break;
      };

      this->position++;
    }
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
      // TODO: Implement finalize current token
    }
  }
};

int main(int, char**) { std::cout << "Hello, from smallang!\n"; }

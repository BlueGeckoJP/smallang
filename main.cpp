#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "lexer.hpp"

int main(int, char**) {
  std::string input_text = "add 123 + 456";
  Lexer lexer = Lexer(input_text);
  lexer.tokenize();
  lexer.debug_print_tokens();
}

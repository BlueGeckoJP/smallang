#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "lexer.hpp"
#include "parser.hpp"

int main(int, char**) {
  std::string input_text = "8*2+(1+3)/6";
  Lexer lexer = Lexer(input_text);
  lexer.tokenize();
  lexer.debug_print_tokens();
  Parser parser = Parser(lexer.tokens);

  auto ast = parser.parse();
  parser.print_ast(ast.get());
}

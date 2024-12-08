#include <algorithm>
#include <cctype>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "interpreter.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int main(int, char**) {
  std::string input_text = "8*2";
  Lexer lexer = Lexer(input_text);
  lexer.tokenize();
  lexer.debug_print_tokens();
  Parser parser = Parser(lexer.tokens);

  auto ast = parser.parse();
  parser.print_ast(ast.get());

  Interpreter interpreter;
  double result = interpreter.evalute(ast.get());

  std::cout << "Result: " << result << std::endl;
}

#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
 public:
  std::string type = "";
  std::string value = "";

  Token(const std::string& t_type, const std::string& t_value);
};

#endif
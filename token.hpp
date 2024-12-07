#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token {
 public:
  std::string type = "";
  std::string value = "";

  Token(const std::string& type, const std::string& value)
      : type(type), value(value) {};
};

#endif
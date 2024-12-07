#include "token.hpp"

#include <string>

Token::Token(const std::string& t_type, const std::string& t_value)
    : type(t_type), value(t_value) {};

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

class ASTNode {
  ASTNode(std::string type, std::string value, std::string left,
          std::string right);
};

#endif
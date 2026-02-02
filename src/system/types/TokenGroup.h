#pragma once
#include "Token.h"
#include <vector>

struct TokenGroup{
  std::vector<Token> command;
  std::vector<Token> option;
  std::vector<Token> separation;
  std::vector<Token> positional;
};


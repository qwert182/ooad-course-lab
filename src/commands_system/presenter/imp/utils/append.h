#pragma once

#include <vector>
#include <string>

void append(std::vector<char> &, const std::vector<char> &);
void append(std::vector<char> &, const char *);
void append(std::vector<char> &, const std::string &);
void appendCRLF(std::vector<char> &);


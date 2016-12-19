#pragma once

#include <unordered_map>
#include <string>

std::unordered_map<std::string, std::string> parse_post(const std::string &);
bool isFlagSet(const std::unordered_map<std::string, std::string> &map, const std::string &flag);

const std::string & getValueByKey(const std::unordered_map<std::string, std::string> &map, const std::string &key);


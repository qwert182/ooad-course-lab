#pragma once

#include <winsock.h>
#include <vector>
#include <string>

void recvToVector(SOCKET a, std::vector<char> &data);
std::string recvToVector_MoveNewToString(SOCKET a, std::vector<char> &data);


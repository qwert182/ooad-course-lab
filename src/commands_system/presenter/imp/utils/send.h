#pragma once

#include <vector>
#include <winsock.h>

void send_status(SOCKET, int code);
void send_data(SOCKET a, const std::vector<char> &data);


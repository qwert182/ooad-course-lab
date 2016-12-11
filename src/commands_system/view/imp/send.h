#pragma once

#include <string>
#include <winsock.h>

void send_file(SOCKET a, const std::string &filename);
void send_response(SOCKET a, int code);


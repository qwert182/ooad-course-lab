#pragma once

#include <vector>
#include "../Session.h"

std::vector<char> file_response_must_be_authorized(const char *filename, Session *session);
void must_be_authorized(Session *session);


#pragma once

#include <vector>
#include "../Session.h"

std::vector<char> file_response_must_be_authorized(const char *filename, Session *session);
std::vector<char> file_response_must_be_authorized_with_header(const char *filename, Session *session, const char *header);
void must_be_authorized(Session *session);


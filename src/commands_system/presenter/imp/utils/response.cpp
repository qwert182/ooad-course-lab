#include "response.h"

#include "../ForbiddenException.h"

#include "status.h"
#include "append.h"
#include "read_file.h"

using std::vector;

vector<char> file_response_must_be_authorized(const char *filename, Session *session) {
	if (session == nullptr) {
	  vector<char> result = getStatusBy(302);
		append(result, "Location: /login\r\n");
		appendCRLF(result);
		return result;
	}


  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	append(result, read_file(filename));
	return result;
}

void must_be_authorized(Session *session) {
	if (session == nullptr)
		throw ForbiddenException("must_be_authorized");
}


#include "StaticHeaderResource.h"

#include "utils/status.h"
#include "utils/append.h"

using std::vector;
using std::string;


StaticHeaderResource::StaticHeaderResource(int status, const char *header) {
	this->header = header;
	this->status = status;
}

vector<char> StaticHeaderResource::get(Session *) const {
  vector<char> result = getStatusBy(status);
	append(result, header);
	appendCRLF(result);
	return result;
}



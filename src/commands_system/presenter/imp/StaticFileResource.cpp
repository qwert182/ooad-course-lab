#include "StaticFileResource.h"


#include "utils/status.h"
#include "utils/read_file.h"
#include "utils/append.h"


using std::vector;
using std::string;


StaticFileResource::StaticFileResource(const char *path_to_file) {
	this->path_to_file = path_to_file;
}

vector<char> StaticFileResource::get(Session *) const {
  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	append(result, read_file(this->path_to_file));
	return result;
}


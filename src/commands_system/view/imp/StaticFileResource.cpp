#include "StaticFileResource.h"

#include "send.h"


StaticFileResource::StaticFileResource(const char *path_to_file) {
	this->path_to_file = path_to_file;
}

void StaticFileResource::get(SOCKET a) const {
	send_response(a, 200);
	send_file(a, this->path_to_file);
}


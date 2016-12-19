#include "MainPageResource.h"


#include "utils/response.h"

using std::vector;


MainPageResource::MainPageResource() {
}


vector<char> MainPageResource::get(Session *session) const {
	return file_response_must_be_authorized("html/home.htm", session);
}


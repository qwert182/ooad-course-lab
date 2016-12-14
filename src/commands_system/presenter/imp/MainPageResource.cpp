#include "MainPageResource.h"


#include "utils/status.h"
#include "utils/append.h"

using std::vector;


MainPageResource::MainPageResource() {
}

vector<char> MainPageResource::get() const {
  vector<char> result = getStatusBy(302);
	append(result, "Location: /login\r\n");
	appendCRLF(result);
	return result;
}


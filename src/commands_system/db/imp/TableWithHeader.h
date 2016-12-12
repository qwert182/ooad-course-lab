#pragma once

#include <vector>
#include <string>
#include "../Element.h"

struct TableWithHeader {
	std::vector<std::vector<Element>> content;
	std::vector<std::string>
		types,
		hat,
		links;
};


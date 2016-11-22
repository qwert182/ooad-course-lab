#include <string>
#include <vector>
#include <fstream>
#include "../Element.h"
#include "../../utils/Exception.h"

struct TableWithHeader {
	std::vector<std::vector<Element>> content;
	std::vector<std::string> hat;
};

TableWithHeader parse(std::istream &file);



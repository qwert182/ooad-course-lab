#include "append.h"


using std::vector;
using std::string;


void append(vector<char> &data, const vector<char> &appendix) {
	data.insert(data.end(), appendix.begin(), appendix.end());
}

void append(vector<char> &data, const char *str) {
	data.insert(data.end(), str, &str[strlen(str)]);
}

void append(vector<char> &data, const string &str) {
	data.insert(data.end(), str.begin(), str.end());
}


void appendCRLF(vector<char> &data) {
  static const char crlf[2] = {'\r', '\n'};
	data.insert(data.end(), crlf, &crlf[2]);
}


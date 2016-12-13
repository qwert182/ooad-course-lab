#include "request.h"

#include <sstream>

#include "../BadRequestException.h"
#include "../NotImplementedException.h"
#include "../../../utils/trim.h"
#include "recv.h"


using std::string;
using std::vector;
using std::istringstream;


void Request::set_headers(const string &all) {
  size_t end_pos = all.find("\r\n\r\n");
	if (end_pos == all.npos) return;

  size_t cur_pos;
  size_t next_pos = all.find("\r\n");

	while (next_pos != end_pos) {
		cur_pos = next_pos + 2;
		next_pos = all.find("\r\n", cur_pos);
		if (all[next_pos + 2] == ' ')
			throw BadRequestException("LWS is not supported yet");

	  string field_line = all.substr(cur_pos, next_pos - cur_pos);
	  size_t col_pos = field_line.find(':');

		if (col_pos == string::npos)
			throw BadRequestException("message header must contain \":\"");

	  string field_name = field_line.substr(0, col_pos);
		trim(field_name);

	  string field_value = field_line.substr(col_pos + 1);
		trim(field_value);

		headers.insert(make_pair(field_name, field_value));
	}
}

void Request::correct_path() {
  size_t ss;
	if (path.length() == 0)
		throw BadRequestException("HTTP request must contain Request-URI");
	if ((ss = path.find("://")) != path.npos) {
		size_t s;
		if ((s = path.find('/', ss + 3)) != path.npos) {
			path.erase(0, s);
		} else {
			path = '/';
		}
	}
}

void Request::set_09(const string &line, size_t sp) {
	version = "HTTP/0.9";
	path = line.substr(sp + 1);
	correct_path();
}

void Request::set_10(const string &all, size_t sp_first, size_t sp_last) {
	version = all.substr(sp_last + 1, all.find('\r') - sp_last - 1);
	path = all.substr(sp_first + 1, sp_last - sp_first - 1);
	correct_path();
	set_headers(all);
}

// HTTP 0.9
Request::Request(const string &line, int version, int sp_first, int sp_last) {
	type = line.substr(0, sp_first);

	if (version == 9  &&  type != "GET")
		throw BadRequestException("HTTP/0.9 request must be GET");

	if (version == 10  &&  type != "GET"  &&  type != "POST")
		throw NotImplementedException("supported only GET and POST");

	if (version == 9) set_09(line, sp_first);
	else if (version == 10) set_10(line, sp_first, sp_last);
	this->all = line;

	if (path.find('/') != 0)
		throw BadRequestException("HTTP request must contain absolute path");
}


















Request Request::receive(SOCKET a) {
  string all;
  size_t sp_first, sp_last;
  vector<char> data;

	for (;;) {
		all += recvToVector_MoveNewToString(a, data);

	  size_t r = all.find("\r\n");
		if (r != string::npos) {
		  string line = all.substr(0, r);
			sp_first = line.find_first_of(' ') ;
			sp_last = line.find_last_of(' ');
			if (sp_first == line.npos)
				throw BadRequestException("first line of HTTP request must contain space");
			if (sp_first == sp_last) { // HTTP 0.9
				return Request(line, 9, sp_first, sp_last);
			} else { // HTTP 1.0+
				break;
			}
		}
	}

  size_t end;
	while ((end = all.find("\r\n\r\n")) == all.npos) {
		all += recvToVector_MoveNewToString(a, data);
	}

  Request request = Request(all, 10, sp_first, sp_last);

	if (request.type == "GET") {
		if (end != all.length() - 4)
			throw BadRequestException("receiveHTTPRequest");
	} else if (request.type == "POST") {
	  auto _content_length = request.headers.find("Content-Length");
		if (_content_length == request.headers.end()) throw BadRequestException("Content-Length not found");
	  istringstream convert(_content_length->second);
	  size_t content_length;
		convert >> content_length;
		if (convert.bad() || !convert.eof()) throw BadRequestException("bad Content-Length");


	  vector<char> content(data.begin() + end + strlen("\r\n\r\n"), data.end());
		while (content.size() < content_length) {
			recvToVector(a, content);
		}
		if (content.size() != content_length)
			throw BadRequestException("actual content length != Content-Length");

		request.content = content;
	} else {
		throw NotImplementedException(request.type.c_str());
	}

	return request;
}



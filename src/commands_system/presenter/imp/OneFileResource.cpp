#include "OneFileResource.h"

#include "../../model/INote.h"
#include "../../model/imp/Attachment.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"

#include "BadRequestException.h"

#include <fstream>

using namespace std;

OneFileResource::OneFileResource(const string & file_name) : file_name(file_name){

}

static const char header[] =
	"Content-Type: application/octet-stream" "\r\n"
	"Content-Disposition: attachment" "\r\n";

vector<char> OneFileResource::get(Session *s) const {
	return file_response_must_be_authorized_with_header(file_name.c_str(), s, header);
}


extern INote *last_note;
extern string *last_filename;
INote *last_note;
string *last_filename;


vector<char> OneFileResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

	if (last_note == nullptr)
		throw BadRequestException("last_note == nullptr");

	ofstream f("attachments/" + *last_filename, ios::binary);
	if (content.size())
		f.write(&content[0], content.size());
	f.close();

  unique_ptr<IUser> user(  last_note->getWriter()  );
  unique_ptr<IAttachment> att(  new Attachment(*last_filename, "no description", *user)  );
	last_note->add(*att);
	delete last_note;
	last_note = nullptr;

  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	return result;
}


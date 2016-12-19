#include "MessagesResource.h"

#include "../../model/IMail.h"
#include "../../model/IMessage.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"

#include "BadRequestException.h"


using std::vector;
using std::string;


MessagesResource::MessagesResource() {
}


vector<char> MessagesResource::get(Session *session) const {
	return file_response_must_be_authorized("html/messages.htm", session);
}


vector<char> MessagesResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);


  string active(content.begin(), content.end());
	if (active != "active") {
		throw BadRequestException("non active /projects");
	}

  vector<char> result = getStatusBy(200);
	appendCRLF(result);

  IUser *user = session->getUser();
  IMail *mail = user->getMail();
  vector<IMessage *> inbox = mail->getInBox();
  size_t i, count = inbox.size();

	if (count == 0) {
		append(result, "no letters");
	}

	for (i = 0; i < count; ++i) {
	  IMessage *msg = inbox[i];
		append(result, "<li>");
		append(result, "Subject: ");
		append(result, msg->getSubject());
		append(result, ". Text: ");
		append(result, msg->getText());
		append(result, "</li>");
		delete msg;
	}

	delete mail;

	return result;
}


#include "SendResource.h"

#include "../../model/IMail.h"
#include "../../model/IAllUsers.h"
#include "allUsersInstance.h"
#include "../../model/imp/Message.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/parse_post.h"

#include "BadRequestException.h"


using std::vector;
using std::string;
using std::unordered_map;


SendResource::SendResource() {
}



vector<char> SendResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> message_content = parse_post(string(content.begin(), content.end()));
  const string
	  &subject = getValueByKey(message_content, "subject"),
	  &text = getValueByKey(message_content, "text"),
	  &receiver_login = getValueByKey(message_content, "receiver");

  	if (!isFlagSet(message_content, "active")) {
	  vector<char> result = getStatusBy(400);
		appendCRLF(result);
		append(result, "only active send supported (please enable javascript)");
		return result;
	}

  IUser *sender = session->getUser();
  IMail *mail = sender->getMail();
  IUser *receiver = allUsers->getUserByLogin(receiver_login);

  IMessage *message = new Message(sender, receiver, subject, text);
	mail->send(*message);

	delete message;
	delete mail;
	delete receiver;

  vector<char> result = getStatusBy(200);
	appendCRLF(result);
	return result;
}


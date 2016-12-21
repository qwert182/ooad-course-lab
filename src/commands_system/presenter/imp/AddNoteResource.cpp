#include "AddNoteResource.h"

#include "../../model/imp/Note.h"
#include "../../model/IAllProjects.h"
#include "../../model/IProject.h"
#include "../../model/ITask.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/parse_post.h"

#include "BadRequestException.h"


using std::vector;
using std::string;
using std::unordered_map;
using std::unique_ptr;


AddNoteResource::AddNoteResource() {
}


extern INote *last_note;
extern string *last_filename;

vector<char> AddNoteResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> what_content = parse_post(string(content.begin(), content.end()));

  const string
	  &project_name = getValueByKey(what_content, "project"),
	  &task_name = getValueByKey(what_content, "task"),
	  &text = getValueByKey(what_content, "text");
	*last_filename = getValueByKey(what_content, "file");

  vector<char> result = getStatusBy(200);
	appendCRLF(result);

  IUser *user = session->getUser();
  unique_ptr<const IAllProjects> projects(  user->getProjects()  );
  unique_ptr<const IProject> project(  projects->getProjectByName(project_name)  );
  unique_ptr<ITask> task(  project->getTaskByName(task_name)  );

	if (last_note != nullptr) delete last_note;
	last_note =  new Note(*user, text);
	task->add( *last_note );

  /*IMail *mail = user->getMail();
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

	delete mail;*/

	return result;
}


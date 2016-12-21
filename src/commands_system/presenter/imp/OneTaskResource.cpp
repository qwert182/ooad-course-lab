#include "OneTaskResource.h"

#include "../../model/IAllProjects.h"
#include "../../model/IProject.h"
#include "../../model/ITask.h"
#include "../../model/INote.h"
#include "../../model/IAttachment.h"

#include "utils/response.h"
#include "utils/status.h"
#include "utils/append.h"
#include "utils/parse_post.h"

#include "BadRequestException.h"

#include <memory>

using std::vector;
using std::string;
using std::unordered_map;
using std::unique_ptr;


OneTaskResource::OneTaskResource() {
}




vector<char> OneTaskResource::get(Session *session) const {
	return file_response_must_be_authorized("html/task.htm", session);
}



vector<char> OneTaskResource::post(const vector<char> &content, Session *session) const {
	must_be_authorized(session);

  unordered_map<string, string> what_content = parse_post(string(content.begin(), content.end()));

  const string
	  &project_name = getValueByKey(what_content, "project"),
	  &task_name = getValueByKey(what_content, "task"),
	  &what = getValueByKey(what_content, "content");

  vector<char> result = getStatusBy(200);
	append(result, "Content-Type: text/html;charset=windows-1251\r\n");
	appendCRLF(result);

  const IUser *user = session->getUser();
  unique_ptr<const IAllProjects> projects(  user->getProjects()  );
  unique_ptr<const IProject> project(  projects->getProjectByName(project_name)  );
  unique_ptr<const ITask> task(  project->getTaskByName(task_name)  );

	if (what == "task_description") {
		append(result, task->getDescription());
	} else if (what == "task_theme") {
		append(result, task->getTheme());
	} else if (what == "task_notes") {
	  vector<INote *> notes = task->getNotes();
		for (size_t i = 0; i < notes.size(); ++i) {
		  INote *note = notes[i];
		  IUser *user = note->getWriter();
			append(result, "<li>");
			append(result, "от: ");
			append(result, user->getName());
			append(result, " \"");
			append(result, note->getText());
			append(result, "\"");
			append(result, "</li>");
			delete user;
			delete note;
		}
	} else if (what == "task_attachments") {
	  vector<IAttachment *> attachments = task->getAttachments();
		for (size_t i = 0; i < attachments.size(); ++i) {
		  IAttachment *attachment = attachments[i];
			append(result, "<li>");
			append(result, "<a href=\"");
			append(result, "/files/" + attachment->getFileName());
			append(result, "\">");
			append(result, attachment->getFileName());
			append(result, "</a>");
			append(result, " описание: " + attachment->getDescription());
			append(result, "</li>");
			delete attachment;
		}
	} else {
		throw BadRequestException("non active /projects");
	}


	return result;
}


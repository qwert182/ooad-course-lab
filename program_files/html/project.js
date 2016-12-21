"use strict";











var logIn_submit_button;

var project_name;







function logIn_response() {
	if (this.readyState == 4) {
		logIn_submit_button.disabled = false;
		if (this.status == 200) {
			getProjects(response_workersList, "workers_list");
			getProjects(response_taskList, "task_list");
		} else {
			abort("error");
		}
	}
}


function logIn() {
  var s = new XMLHttpRequest();
  var inputs = this.getElementsByTagName("input");
  var selects = this.getElementsByTagName("select");
  var content = "active\r\n" + "project=" + project_name + "\r\n";

	for (var i = 0; i < inputs.length; ++i) {
	  var input = inputs[i];
		if (input.type == "password" || input.type == "text") {
			content += input.name + "=" + input.value + "\r\n";
		} else if (input.type == "submit") {
			logIn_submit_button = input;
		}
	}

	for (i = 0; i < selects.length; ++i) {
	  var select = selects[i];
		content += select.name + "=" + select.value + "\r\n";
	}

	logIn_submit_button.disabled = true;

	s.onreadystatechange = logIn_response;
	s.open(this.method, this.action, true);
	s.send(content);

	return false; // prevent submiting by browser
}


function main2() {
  var forms = document.getElementsByTagName("form");
	for (var i = 0; i < forms.length; ++i) {
		forms[i].onsubmit = logIn;
	}
}









var select_users;
function setUsers(text) {
	select_users.innerHTML = text;
}
function responseUsers() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			setUsers(this.responseText);
		} else {
			alert("error");
		}
	}
}

function getUsers() {
  var s = new XMLHttpRequest();
	s.onreadystatechange = responseUsers;
	s.open("POST", "/users", true);
	s.send("active");
}







var projectDescription;
var taskList;
var workersList;

function response_projectDescription() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			projectDescription.innerHTML = this.responseText;
		} else {
			alert("error");
		}
	}
}

function response_taskList() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			taskList.innerHTML = this.responseText;
		} else {
			alert("error");
		}
	}
}

function response_workersList() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			workersList.innerHTML = this.responseText;
		} else {
			alert("error");
		}
	}
}

function getProjects(response, what) {
  var s = new XMLHttpRequest();
	s.onreadystatechange = response;
	s.open("POST", document.URL, true);
	s.send(what);
}

function main() {
  var projectName = document.getElementById("project_name");
  var arr = document.URL.split("/");
	projectName.innerHTML = "\"" + arr[arr.length - 1] + "\"";
	project_name = arr[arr.length - 1];

	projectDescription = document.getElementById("project_description");
	taskList = document.getElementById("task_list");
	workersList = document.getElementById("workers_list");

	getProjects(response_projectDescription, "project_description");
	getProjects(response_taskList, "task_list");
	getProjects(response_workersList, "workers_list");

  var selects = document.getElementsByTagName("select");
	if (selects.length != 1) {throw "selects (tag \"select\") count must be 1";}
	select_users = selects[0];
	getUsers();

	main2();
}


window.onload = main;


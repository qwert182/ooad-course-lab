"use strict";

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

	projectDescription = document.getElementById("project_description");
	taskList = document.getElementById("task_list");
	workersList = document.getElementById("workers_list");

	getProjects(response_projectDescription, "project_description");
	getProjects(response_taskList, "task_list");
	getProjects(response_workersList, "workers_list");
}


window.onload = main;


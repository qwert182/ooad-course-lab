"use strict";

var list;

function setProjects(text) {
	list.innerHTML = text;
}

function response() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			setProjects(this.responseText);
		} else {
			alert("error");
		}
	}
}

function getProjects() {
  var s = new XMLHttpRequest();
	s.onreadystatechange = response;
	s.open("POST", "/projects", true);
	s.send("active");
}

function main() {
  var lists = document.getElementsByTagName("ol");
	if (lists.length != 1) {
		throw "lists (tag \"ol\") count must be 1";
	}
	list = lists[0];
	getProjects();
}


window.onload = main;


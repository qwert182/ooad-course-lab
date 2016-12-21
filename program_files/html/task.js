"use strict";


function getFromServer(what) {
  var ELEMENT = document.getElementById(what);
  var s = new XMLHttpRequest();


	s.onreadystatechange = function() {
		if (this.readyState == 4) {
			if (this.status == 200) {
				ELEMENT.innerHTML = this.responseText;
			} else {
				alert("error");
			}
		}
	};


	s.open("POST", document.URL, true);
	s.send(what);
}




function send_data(content, to) {
  var s = new XMLHttpRequest();
	s.onreadystatechange = function() {
		if (this.readyState == 4) {
			if (this.status != 200) {
				alert("send_data error");
			} else {
				update();
			}
		}
	};
	s.open("POST", to, true);
	s.send(content);
}

function send_file(file) {
  var f = new FileReader();
	f.onloadend = function() {
		if (this.readyState == 2) {
			send_data(this.result, "/files/" + file.name);
		} else {
			alert("send_file error");
		}
	};
	f.readAsArrayBuffer(file);
}


function update() {
	getFromServer("task_theme");
	getFromServer("task_description");
	getFromServer("task_notes");
	getFromServer("task_attachments");
}

var content_BEGIN;

function lastSlash(str) {
  var arr;
	arr = str.split("/");
	str = arr[arr.length - 1];
	arr = str.split("\\");
	return arr[arr.length - 1];
}

function addNote() {
  var s = new XMLHttpRequest();
  var inputs = this.getElementsByTagName("input");
  var content = "active\r\n" + content_BEGIN;
  var i;
  var submitButton;
  var file = null;

	for (i = 0; i < inputs.length; ++i) {
	  var input = inputs[i];
		if (input.type == "text") {
			content += input.name + "=" + input.value + "\r\n";
		} else if (input.type == "file") {
			content += input.name + "=" + lastSlash(input.value) + "\r\n";
			if (input.files.length != 0) {
				file = input.files[0];
			}
		} else if (input.type == "submit") {
			submitButton = input;
		}
	}

	submitButton.disabled = true;

	s.onreadystatechange = function() {
		if (this.readyState == 4) {
			if (this.status != 200) {
				alert("error");
			} else {
				if (file != null) {
					send_file(file);
				} else {
					update();
				}
			}
			submitButton.disabled = false;
		}
	};
	s.open(this.method, this.action, true);
	s.send(content);

	return false; // prevent submiting by browser
}




function main() {
  var arr = document.URL.split("/");
	document.getElementById("task_name").innerHTML = "\"" + arr[arr.length - 1] + "\"";
	content_BEGIN = "project=" + arr[arr.length - 2] + "\r\n";
	content_BEGIN += "task=" + arr[arr.length - 1] + "\r\n";


	update();

  var forms = document.getElementsByTagName("form");
	if (forms.length != 1) {
		throw "forms count must be 1";
	}
  var form = forms[0];
	form.onsubmit = addNote;
}


window.onload = main;


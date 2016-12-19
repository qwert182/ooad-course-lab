"use strict";

var list_inbox;

function setMessages(text) {
	list_inbox.innerHTML = text;
}

function response() {
	if (this.readyState == 4) {
		if (this.status == 200) {
			setMessages(this.responseText);
		} else {
			alert("error");
		}
	}
}

function getMessages() {
  var s = new XMLHttpRequest();
	s.onreadystatechange = response;
	s.open("POST", "/messages", true);
	s.send("active");
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







var sendMessage_submit_button;

function sendMessage_response() {
	if (this.readyState == 4) {
		if (this.status != 200) {
			alert("error");
		}
		sendMessage_submit_button.disabled = false;
	}
}

function sendMessage() {
  var s = new XMLHttpRequest();
  var inputs = this.getElementsByTagName("input");
  var selects = this.getElementsByTagName("select");
  var content = "active\r\n";
  var i;

	for (i = 0; i < inputs.length; ++i) {
	  var input = inputs[i];
		if (input.type == "password" || input.type == "text") {
			content += input.name + "=" + input.value + "\r\n";
		} else if (input.type == "submit") {
			sendMessage_submit_button = input;
		}
	}

	for (i = 0; i < selects.length; ++i) {
	  var select = selects[i];
		content += select.name + "=" + select.value + "\r\n";
	}

	sendMessage_submit_button.disabled = true;

	s.onreadystatechange = sendMessage_response;
	s.open(this.method, this.action, true);
	s.send(content);

	return false; // prevent submiting by browser
}






function main() {
  var lists = document.getElementsByTagName("ol");
	if (lists.length != 1) {
		throw "lists (tag \"ol\") count must be 1";
	}
	list_inbox = lists[0];
	getMessages();



  var selects = document.getElementsByTagName("select");
	if (selects.length != 1) {
		throw "selects (tag \"select\") count must be 1";
	}
	select_users = selects[0];
	getUsers();




  var forms = document.getElementsByTagName("form");
	if (forms.length != 1) {
		throw "forms count must be 1";
	}

  var form = forms[0];
	form.onsubmit = sendMessage;
}


window.onload = main;


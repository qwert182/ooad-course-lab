"use strict";

var logIn_submit_button;
var logIn_errmsg_div;


function logIn_hideErrorMessage() {
	logIn_errmsg_div.className = "hidden_errmsg";
}

function logIn_showServerErrorMessage() {
	document.getElementById("errmsg_server").className = "sub_errmsg";
	document.getElementById("errmsg_loginpassword").className = "hidden_sub_errmsg";
	logIn_errmsg_div.className = "errmsg";
}

function logIn_showLoginPasswordErrorMessage() {
	document.getElementById("errmsg_loginpassword").className = "sub_errmsg";
	document.getElementById("errmsg_server").className = "hidden_sub_errmsg";
	logIn_errmsg_div.className = "errmsg";
}



function logIn_successfully(response) {
  var arr = response.split("\r\n");
	if (arr.length == 2  ||  arr.length == 3 && arr[2] === "") {
	  var sid = arr[0];
	  var location = arr[1];
		document.cookie = "sid=" + sid;
		window.location.replace(location);
	} else {
		logIn_showServerErrorMessage();
	}
}



function logIn_response() {
	if (this.readyState == 4) {
		logIn_submit_button.disabled = false;
		if (this.status == 200) {
			logIn_successfully(this.responseText);
		} else if (this.status == 403) {
			logIn_showLoginPasswordErrorMessage();
		} else {
			logIn_showServerErrorMessage();
		}
	}
}


function logIn() {
  var s = new XMLHttpRequest();
  var inputs = this.getElementsByTagName("input");
  var content = "active\r\n";

	for (var i = 0; i < inputs.length; ++i) {
	  var input = inputs[i];
		if (input.type == "password" || input.type == "text") {
			content += input.name + "=" + input.value + "\r\n";
		} else if (input.type == "submit") {
			logIn_submit_button = input;
		}
	}

	logIn_hideErrorMessage();
	logIn_submit_button.disabled = true;

	s.onreadystatechange = logIn_response;
	s.open(this.method, this.action, true);
	s.send(content);

	return false; // prevent submiting by browser
}


function main() {
  var forms = document.getElementsByTagName("form");
	if (forms.length != 1) {
		throw "forms count must be 1";
	}

  var form = forms[0];
	form.onsubmit = logIn;

	logIn_errmsg_div = document.getElementById("errmsg");
}


window.onload = main;


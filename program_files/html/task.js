"use strict";

//var task_name;
//var task_theme;
//var task_description;




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

function main() {
  var arr = document.URL.split("/");
	document.getElementById("task_name").innerHTML = "\"" + arr[arr.length - 1] + "\"";


	getFromServer("task_theme");
	getFromServer("task_description");
	getFromServer("task_notes");
}


window.onload = main;


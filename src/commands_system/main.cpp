#define _CRTDBG_MAP_ALLOC 1
#include <stdlib.h>
#include <crtdbg.h>
#include <windows.h>
#include <type_traits>

#include <iostream>

#include "utils/Test.h"
#include "utils/formatTypeidName.h"
#include "utils/Exception.h"

#include "presenter/imp/HTTPServer.h"
#include "presenter/imp/allUsersInstance.h"

#include "db/imp/DataBase.h"
#include "db/instance.h"


using std::cout;
using std::endl;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportFile(_CRT_WARN, GetStdHandle(STD_ERROR_HANDLE)); // for use in Test.cpp when _CRTDBG_MODE_FILE
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_WNDW);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_WNDW);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_WNDW);

	#if COMPILE_WITH_TESTS
	Test::All();
	#endif



	DataBase::CreateInstance();
	dataBase->open();

	allUsers_Create();


	cout << "ctrl+c to stop" << endl;
	{
	  IPresenter* presenter = nullptr;
		try {
			presenter = new HTTPServer();
			presenter->present();
		} catch (const Exception &e) {
			cout << "Exception: " << formatTypeidName(typeid(e).name()) << '\n';
			cout << '\t' << e.what() << '\n';
		}
		delete presenter;
	}
	cout << "stopped" << endl;


	delete allUsers;
	delete dataBase;



	return 0;
}


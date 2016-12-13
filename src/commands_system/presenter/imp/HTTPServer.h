#pragma once

#include "../IPresenter.h"
#include <winsock.h>


class HTTPServer : public IPresenter {
private:
	SOCKET s;

	// disable
	HTTPServer(const HTTPServer &);
	HTTPServer & operator =(const HTTPServer &);
	void server();

public:
	HTTPServer();
	virtual void present();
	virtual ~HTTPServer();
};


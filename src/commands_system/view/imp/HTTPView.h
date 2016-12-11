#pragma once

#include "../IView.h"
#include <winsock.h>


class HTTPView : public IView {
private:
	SOCKET s;

	// disable
	HTTPView(const HTTPView &);
	HTTPView & operator =(const HTTPView &);


public:
	HTTPView();
	void server();
	virtual ~HTTPView();
};


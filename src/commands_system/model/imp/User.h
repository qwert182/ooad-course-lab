#pragma once

#include "../IUser.h"
#include <vector>

class User : public IUser {
private:
	int id;
	class IMail *mail;
};




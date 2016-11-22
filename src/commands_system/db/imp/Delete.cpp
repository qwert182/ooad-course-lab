#include "../Delete.h"
#include "../ITable.h"

using namespace std;

  ITable & Delete::perform(DataBase &db) const {
	  return *(ITable*)0;
  };

  bool Delete::filled() const {
	  return  filled_from && filled_where;
  }

Delete::Delete() {
}

Delete & Delete::from(const string &table) {
	this->table = table;
	filled_from =true;
	return *this;
}

	Delete & Delete::where(const string &column, const Element &equal) {
		this->whereEqual = make_pair(column, equal);
		filled_where = true;
		return *this;
	}
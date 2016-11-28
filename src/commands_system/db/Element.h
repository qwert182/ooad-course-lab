#pragma once

#include <string>


//Ќазначение:
//	»спользуетс€ дл€ получени€/задани€ значений в таблицах базы данных.
//»спользование:
//	ћожет €вл€тьс€ строкой либо целым числом.
//	ѕри выполнении операций в случае несоответстви€ типов бросает WrongTypeException.
class Element {
protected:
	// virtual function table
	const struct _Element_vft *__vft;

	union {
		int integer;
		char *str;
	} data;


public:
	Element();
	Element(int integer);
	Element(const char *string);
	Element(const std::string &string);

//virtual:
	Element(const Element &);
	Element(Element &&);

	operator int() const;
	operator std::string() const;
	~Element();

	Element & operator =(const Element &);
	Element & operator =(Element &&);

	bool equals(const Element &) const;

private:
	// не используютс€:
	void operator +=(const Element &);
	void operator -=(const Element &);
	void operator *=(const Element &);
	void operator /=(const Element &);
	void operator %=(const Element &);
	void operator &=(const Element &);
	void operator |=(const Element &);
	void operator ^=(const Element &);
	void operator <<=(int);
	void operator >>=(int);
};


//¬ случае несовпадени€ типов бросает WrongTypeException
bool operator ==(const Element &, const Element &);



// не используютс€:
void operator !=(const Element &, const Element &);
void operator >=(const Element &, const Element &);
void operator >(const Element &, const Element &);
void operator <=(const Element &, const Element &);
void operator <(const Element &, const Element &);

void operator +(const Element &);
void operator -(const Element &);
void operator +(const Element &, const Element &);
void operator -(const Element &, const Element &);

void operator *(const Element &, const Element &);
void operator /(const Element &, const Element &);
void operator %(const Element &, const Element &);

void operator ~(const Element &);
void operator ^(const Element &, const Element &);
void operator &(const Element &, const Element &);
void operator |(const Element &, const Element &);
void operator <<(const Element &, int);
void operator >>(const Element &, int);

void operator !(const Element &);
void operator &&(const Element &, const Element &);
void operator ||(const Element &, const Element &);

void operator ++(const Element &);
void operator --(const Element &);
void operator ++(const Element &, int);
void operator --(const Element &, int);


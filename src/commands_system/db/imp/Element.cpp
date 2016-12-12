#include "../Element.h"
#include "../WrongTypeException.h"

#include "../../utils/strnew.h"
#include <malloc.h>

using std::string;





class ElementInt : public Element {
public: // virtual:
	operator int() const {
		return data.integer;
	}

	operator string() const {
		throw WrongTypeException("Element doesn't contain <string>");
	}

	void destroy() {
	}

	void copy_from(const Element &other) {
		data.integer = static_cast<const ElementInt &>(other).data.integer;
	}

	void move_from(Element &&other) {
	  ElementInt &other_int = static_cast<ElementInt &>(other);
		data.integer = other_int.data.integer;
		other_int.__vft = nullptr; // make other empty
	}

	bool equals(const Element &other) const {
		return data.integer == (int) other;
	}
};



class ElementString : public Element {
public: // virtual:
	operator int() const {
		throw WrongTypeException("Element doesn't contain <int>");
	}

	operator string() const {
		return data.str;
	}

	void destroy() {
		free(data.str);
	}

	void copy_from(const Element &other) {
		data.str = strnew(static_cast<const ElementString &>(other).data.str);
	}

	void move_from(Element &&other) {
	  ElementString &other_str = static_cast<ElementString &>(other);
		data.str = other_str.data.str;
		other_str.data.str = nullptr;
		other_str.__vft = nullptr; // make other empty
	}

	bool equals(const Element &other) const {
		return data.str == (string) other;
	}
};




// virtual function table declaration
struct _Element_vft {
	int (Element::* operator_int)(void) const;
	string (Element::* operator_string)(void) const;
	void (Element::* destroy)(void);
	void (Element::* copy_from)(const Element &);
	void (Element::* move_from)(Element &&);
	bool (Element::* equals)(const Element &other) const;
};



// virtual function table definition for ElementInt
static _Element_vft int_vft = {
	static_cast<    int (Element::*)(void) const             >      (&ElementInt::operator int),
	static_cast< string (Element::*)(void) const             >      (&ElementInt::operator string),
	static_cast<   void (Element::*)(void)                   >      (&ElementInt::destroy),
	static_cast<   void (Element::*)(const Element &)        >      (&ElementInt::copy_from),
	static_cast<   void (Element::*)(Element &&)             >      (&ElementInt::move_from),
	static_cast<   bool (Element::*)(const Element &) const  >      (&ElementInt::equals)
};

// virtual function table definition for ElementString
static _Element_vft string_vft = {
	static_cast<    int (Element::*)(void) const             >      (&ElementString::operator int),
	static_cast< string (Element::*)(void) const             >      (&ElementString::operator string),
	static_cast<   void (Element::*)(void)                   >      (&ElementString::destroy),
	static_cast<   void (Element::*)(const Element &)        >      (&ElementString::copy_from),
	static_cast<   void (Element::*)(Element &&)             >      (&ElementString::move_from),
	static_cast<   bool (Element::*)(const Element &) const  >      (&ElementString::equals)
};









Element::Element() {
	__vft = nullptr;
}

Element::Element(const Element &el) {
	if ((__vft = el.__vft) == nullptr)
		return;
	(this->*__vft->copy_from)(el);
}
Element::Element(Element &&el) {
	if ((__vft = el.__vft) == nullptr)
		return;
	(this->*__vft->move_from)(std::move(el));
}
Element & Element::operator =(const Element & other) {
	this->Element::~Element();
	this->Element::Element(other);
	return *this;
}
Element & Element::operator =(Element && other) {
	this->Element::~Element();
	this->Element::Element(std::move(other));
	return *this;
}



Element::Element(int integer) {
	__vft = &int_vft;
	data.integer = integer;
}

Element::Element(const char *str) {
	__vft = &string_vft;
	data.str = strnew(str);
}

Element::Element(const std::string &string) {
	__vft = &string_vft;
	data.str = strnew(string.c_str());
}



Element::~Element() {
	if (__vft != nullptr)
		(this->*__vft->destroy)();
}








Element::operator int() const {
	if (__vft == nullptr)
		throw WrongTypeException("Element hasn't been initialized");

	return (this->*__vft->operator_int)();
}

Element::operator std::string() const {
	if (__vft == nullptr)
		throw WrongTypeException("Element hasn't been initialized");

	return (this->*__vft->operator_string)();
}

bool Element::equals(const Element &other) const {
	if (__vft == nullptr)
		throw WrongTypeException("can't compare empty Element");

	return (this->*__vft->equals)(other);
}





bool operator ==(const Element &a, const Element &b) {
	return a.equals(b);
}


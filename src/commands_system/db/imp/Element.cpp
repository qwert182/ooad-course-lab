#include "../Element.h"

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
		copy_from(other);
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
	  const ElementString &other_str = static_cast<const ElementString &>(other);
		data.str = strnew(other_str.data.str);
	}

	void move_from(Element &&other) {
	  ElementString &other_str = static_cast<ElementString &>(other);
		data.str = other_str.data.str;
		other_str.data.str = nullptr;
	}
};




// virtual function table declaration
struct _Element_vft {
	int (Element::* operator_int)(void) const;
	string (Element::* operator_string)(void) const;
	void (Element::* destroy)(void);
	void (Element::* copy_from)(const Element &);
	void (Element::* move_from)(Element &&);
};



// virtual function table definition for ElementInt
static _Element_vft int_vft = {
	static_cast<    int (Element::*)(void) const             >      (&ElementInt::operator int),
	static_cast< string (Element::*)(void) const             >      (&ElementInt::operator string),
	static_cast<   void (Element::*)(void)                   >      (&ElementInt::destroy),
	static_cast<   void (Element::*)(const Element &)        >      (&ElementInt::copy_from),
	static_cast<   void (Element::*)(Element &&)             >      (&ElementInt::move_from)
};

// virtual function table definition for ElementString
static _Element_vft string_vft = {
	static_cast<    int (Element::*)(void) const             >      (&ElementString::operator int),
	static_cast< string (Element::*)(void) const             >      (&ElementString::operator string),
	static_cast<   void (Element::*)(void)                   >      (&ElementString::destroy),
	static_cast<   void (Element::*)(const Element &)        >      (&ElementString::copy_from),
	static_cast<   void (Element::*)(Element &&)             >      (&ElementString::move_from)
};






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





Element::Element(const Element &el) {
	__vft = el.__vft;
	(this->*__vft->copy_from)(el);
}

Element::Element(Element &&el) {
	__vft = el.__vft;
	(this->*__vft->move_from)(std::move(el));
}





Element::operator int() const {
	return (this->*__vft->operator_int)();
}

Element::operator std::string() const {
	return (this->*__vft->operator_string)();
}


Element::~Element() {
	(this->*__vft->destroy)();
}




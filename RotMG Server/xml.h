#ifndef XML_H_
#define XML_H_

#include "pugixml.hpp"
#include <iostream>

class XML {
public:
	XML(const char* fileName);
	~XML() { }
	bool success;
	const char* loadMessage;
	pugi::xml_document doc;
private:
	
};

class XMLOptionedTag {
public:
	XMLOptionedTag();
	~XMLOptionedTag();
	const char* name;
private:

};

class XMLOptionsMap {
public:
	XMLOptionsMap();
	~XMLOptionsMap();

private:

};

#endif // !XML_H_

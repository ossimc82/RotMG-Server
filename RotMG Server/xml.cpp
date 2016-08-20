#include "xml.h"

XML::XML(const char * fileName) {
	pugi::xml_parse_result result = doc.load_file(fileName);
	success = result.status == pugi::xml_parse_status::status_ok;
	loadMessage = result.description();
}

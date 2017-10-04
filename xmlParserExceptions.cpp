#include "xmlParser.h"

xmlParse::xmlException::xmlException(string msg) :
	message("XML exception: " + msg)
{}

xmlParse::xmlException::~xmlException()
{}

const string & xmlParse::xmlException::getMessage() const
{
	return message;
}

xmlParse::xmlIncorrectContent::xmlIncorrectContent() :
	xmlException("incorrect content for parse.")
{}

xmlParse::xmlEmpty::xmlEmpty() :
	xmlException("attempt to parse the empty file.")
{}
#pragma once
#include <string>
#include <list>
using namespace std;

class xmlParse
{
public:
	xmlParse(const string&);
	
	string getString() const;
	void setString(string&);

	string find(const string&, unsigned int = 0) const;
	list<string> findAll(const string&) const;

	class xmlException;
	class xmlIncorrectContent;
	class xmlEmpty;
private:
	int searchPosition(const string&, unsigned int = 0) const;
	void eraseWhitespaces();
	string content;
};

//Exceptions class
//       |
//       |
//      \ /
//       v

class xmlParse::xmlException
{
public:
	xmlException(string);
	virtual ~xmlException() = 0;
	const string& getMessage() const;
private:
	string message;
};

class xmlParse::xmlIncorrectContent : public xmlException
{
public:
	xmlIncorrectContent();
};

class xmlParse::xmlEmpty : public xmlException
{
public:
	xmlEmpty();
};
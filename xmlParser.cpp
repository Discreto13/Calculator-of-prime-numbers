#include "xmlParser.h"

xmlParse::xmlParse(const string & str) :
	content(str)
{
	eraseWhitespaces();
}

string xmlParse::getString() const
{
	return string(content);
}

void xmlParse::setString(string & str)
{
	content = str;
	eraseWhitespaces();
}

//Returns a substring between first <findTeg> and </findTag>,
//beginPosition - from where will be performed search
string xmlParse::find(const string& findTag, unsigned int beginPosition) const
{
	if (content.length() == 0)
		throw xmlEmpty();

	string tagBegin = '<' + findTag + '>';
	string tagEnd = "</" + findTag + '>';
	int begin = beginPosition, end = 0;

	begin = searchPosition(tagBegin, beginPosition);
	if (begin == -1)
		return "";
	begin += tagBegin.length();
	
	end = searchPosition(tagEnd, begin);
	if (end == -1)
		throw xmlIncorrectContent();

	return string(content, begin, end - begin);
}

//Returns list of results find(..).
list<string> xmlParse::findAll(const string & findTag) const
{
	if (content.length() == 0)
		throw xmlEmpty();

	string tagEnd = "</" + findTag + '>';
	list<string> l;
	int position = 0;
	string iterationResult;
	for (;;)
	{
		iterationResult = find(findTag, position);
		if (iterationResult == "")
			break;
		l.push_back(iterationResult);
		position = searchPosition(tagEnd, position + tagEnd.length());
		iterationResult = "";
	}
	return list<string>(l);
}

//Returns position of first symbol of find tag ('<'),
//starting from the beginPosition.
int xmlParse::searchPosition(const string & tag, unsigned int beginPosition) const
{
	bool successful = false;
	for (unsigned int i = beginPosition; i < content.length(); i++)
	{
		if (content[i] == tag[0])
		{
			successful = true;
			for (unsigned int j = 1; j < tag.length(); j++)
			{
				if (content[i + j] != tag[j])
				{
					successful = false;
					break;
				}
			}
			if (successful)
				return i;
		}
	}
	return -1;
}

//Erase all whitespaces from 'content'-string.
inline void xmlParse::eraseWhitespaces()
{
	if (content.length() == 0)
		throw xmlEmpty();

	for (unsigned int i = 0; i < content.length(); i++)
	{
		if (content[i] == ' ' || content[i] == '\n' || content[i] == '\t' || content[i] == '\r')
			content.erase(i, 1);
	}
}
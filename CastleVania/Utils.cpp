#include "Utils.h"

Utils* Utils::_instance = nullptr;

void eraseAllSubStr(std::string & mainStr, const std::string & toErase)
{
	size_t pos = std::string::npos;
	while ((pos = mainStr.find(toErase)) != std::string::npos)
	{
		mainStr.erase(pos, toErase.length());
	}
}

void findAndReplaceAll(std::string & data, std::string toSearch, std::string replaceStr)
{
	size_t pos = data.find(toSearch);
	while (pos != std::string::npos)
	{
		data.replace(pos, toSearch.size(), replaceStr);
		pos = data.find(toSearch, pos + replaceStr.size());
	}
}

Utils::Utils()
{
}

Utils * Utils::getInstance()
{
	if (_instance == nullptr)
		_instance = new Utils();
	return _instance;
}

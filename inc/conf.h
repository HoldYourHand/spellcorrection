#ifndef _CONF_H
#define _CONF_H

#include <string>
#include <fstream>
#include <sstream>
#include <map>

class MyConf
{
public:
	MyConf(std::string &);

	bool init();

	std::map<std::string, std::string> &get_map()
	{
		return map_;
	}

	void show();
private:
	std::ifstream in_;
	std::map<std::string, std::string> map_;
};

#endif

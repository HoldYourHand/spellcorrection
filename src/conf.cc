#include "conf.h"
#include <iostream>
#include <utility>

MyConf::MyConf(std::string &path) 
	: in_(path.c_str())
{}

bool MyConf::init()
{
	if(!in_)
	{
		std::cout << "file read error" << std::endl;
		return false;
	}
	std::string line;
	while(getline(in_, line))
	{
		std::istringstream iss(line);
		std::string key, value;
		iss >> key >> value;
		map_.insert(make_pair(key, value));
	}
	in_.close();
	return true;
}

void MyConf::show()
{
	std::map<std::string, std::string>::const_iterator mit = map_.begin();
	for(; mit != map_.end(); ++mit)
	{
		std::cout << mit->first << " --> " << mit->second << std::endl;
	}
}

#ifndef _MYDICT_H
#define _MYDICT_H

#include <string>
#include <vector>
#include <set>
#include <utility>
#include <map>

class MyDict
{
public:
	static MyDict* createInstance(const char *dictpath, const char * dictpath2);

	std::vector<std::pair<std::string, int> > &get_dict();
	std::map<std::string, std::set<int> > &get_index_table();

	void show_dict();
	void show_index_table();

private:
	MyDict(const char * dictpath, const char * dictpath2);
	void read_from(const char * dictpath);
	void record_to_index(int idx);

private:
	static MyDict *pInstance;
	std::vector<std::pair<std::string, int> > dict_;
	std::map<std::string, std::set<int> > index_table_;
};

#endif//end _MYDICT_H


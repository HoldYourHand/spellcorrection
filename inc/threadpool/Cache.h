#ifndef __CACHE_H
#define __CACHE_H

#include "MutexLock.h"
#include <ext/hash_map>
#include <string>

struct MyHashFn
{
	std::size_t operator()(const std::string &str) const
	{
		return __gnu_cxx::__stl_hash_string(str.c_str());
	}
};

class Cache
{
public:
	typedef __gnu_cxx::hash_map<std::string, std::string, MyHashFn> HashMap;
	typedef __gnu_cxx::hash_map<std::string, std::string, MyHashFn>::iterator HashMap_it;
	typedef __gnu_cxx::hash_map<std::string, std::string, MyHashFn>::const_iterator HashMap_cit;

	Cache(const int num = 100);
	Cache(const Cache &cache);

	void map_to_cache(std::string &key, std::string &value);

	//HashMap_it is_mapped(const std::string &word);

	std::string query_cache(const std::string &word);

	void write_to_file(std::ofstream &fout);

	void read_from_file(const std::string &filename);

	void add_elements(const Cache &cache);
private:
	HashMap hashmap_;
	MutexLock mutex_;
};

#endif

#pragma once
#include <map>
#include <string>

class base_page
{
public: 
	virtual ~base_page() = default; 

	virtual std::map<std::string, std::string> get_data() = 0;
};


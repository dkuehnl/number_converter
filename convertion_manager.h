#pragma once
#include <string>
#include <functional>
#include <map>

class convertion_manager
{
public:

	using data_callback = std::function<std::map<std::string, std::string>()>;

	convertion_manager() = default;
	void print_test();
	void register_page(data_callback callback);
	void test_information_transfer(std::string values);

private: 
	data_callback page;
	std::string test = "Test"; 
};


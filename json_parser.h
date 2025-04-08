#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class json_parser
{
public: 
	json_parser(std::string const& filename);
	const std::unordered_map<std::string, std::vector<std::string>>& get_smops_filter() const;
	const std::vector<std::string>& get_eosight_filter() const;
	const std::vector<std::string>& get_eolive_filter() const;
	const unsigned int& get_preview_lines() const; 
	void add_eolive_filter(std::string new_value);
	void add_eosight_filter(std::string new_value);
	void add_smops_filter(const std::string& key, std::string new_value);
	void update_preview_lines(unsigned int new_value); 
	void save(); 

private:
	std::string m_loaded_filename; 
	std::unordered_map<std::string, std::vector<std::string>> m_parsed_smops;
	std::vector<std::string> m_parsed_eosight;
	std::vector<std::string> m_parsed_eolive;
	unsigned int m_preview_lines = 0; 
};


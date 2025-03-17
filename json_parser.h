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

private:
	std::unordered_map<std::string, std::vector<std::string>> m_parsed_smops;
	std::vector<std::string> m_parsed_eosight;
	std::vector<std::string> m_parsed_eolive;
};


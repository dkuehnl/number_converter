#pragma once
#include <string>
#include <vector>
#include <unordered_map>

/// @brief Loads and saves the app's per-target-system filter configuration as JSON.
///
/// @note Class name doesn't follow the project's PascalCase convention used
/// elsewhere (e.g. CSVParser, ConvertionManager) -- kept as-is here to avoid
/// an unrelated rename during restructuring.
class json_parser
{
public: 
	/// @brief Loads filter configuration from @p filename, if it exists and parses successfully.
	/// @param filename Path to the JSON config file.
	json_parser(std::string const& filename); 

	/// @return Saved SMOPS filter values, grouped by key.
	const std::unordered_map<std::string, std::vector<std::string>>& get_smops_filter() const;

	/// @return Saved eoSight filter values.
	const std::vector<std::string>& get_eosight_filter() const;

	/// @return Saved eoLive filter values.
	const std::vector<std::string>& get_eolive_filter() const;

	/// @return The configured number of preview lines.
	const unsigned int& get_preview_lines() const; 

	/// @brief Adds a value to the eoLive filter list.
	void add_eolive_filter(std::string new_value);

	/// @brief Adds a value to the eoSight filter list.
	void add_eosight_filter(std::string new_value);

	/// @brief Adds a value under @p key in the SMOPS filter map.
	void add_smops_filter(const std::string& key, std::string new_value);

	/// @brief Updates the configured number of preview lines.
	void update_preview_lines(unsigned int new_value); 

	/// @brief Writes the current filter configuration back to the loaded file.
	void save(); 

private:
	std::string m_loaded_filename; 
	std::unordered_map<std::string, std::vector<std::string>> m_parsed_smops;
	std::vector<std::string> m_parsed_eosight;
	std::vector<std::string> m_parsed_eolive;
	unsigned int m_preview_lines = 0; 
};

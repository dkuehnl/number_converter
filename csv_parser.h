#pragma once

#include <string>
#include <vector>
#include <winrt/Windows.Storage.h>

class CSVparser {
private: 
	std::vector<std::string> m_lines; 
	std::vector<std::string> Split(const std::string& line, char delimiter) const; 

public:
	CSVparser() = default; 
	void load_file(winrt::Windows::Storage::StorageFile const& file); 
	std::vector<std::string> get_headers() const; 
	std::vector<std::vector<std::string>> get_rows() const; 
	std::vector<std::string> get_specific_values(const std::string& colum_name) const; 

};
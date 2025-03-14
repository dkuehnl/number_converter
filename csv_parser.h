#pragma once

#include <string>
#include <vector>
#include <winrt/Windows.Storage.h>

class CSVparser {
private: 
	std::vector<std::string> m_lines; 
	std::vector<std::string> Split(const std::string& line, char delimiter) const; 
	std::string Trim(const std::string& str) const;

public:
	CSVparser() = default; 
	winrt::Windows::Foundation::IAsyncAction load_file(winrt::Windows::Storage::StorageFile const& file);
	std::vector<std::string> get_headers(const char delim) const;
	std::string test_get_firstline(int i) const;
	std::vector<std::vector<std::string>> get_rows(const char delim) const;
	/*std::vector<std::string> get_specific_values(const std::string& colum_name) const; */

};
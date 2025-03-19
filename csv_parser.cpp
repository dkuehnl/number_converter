#include "pch.h"
#include "csv_parser.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <winrt/base.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt; 
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation; 

winrt::Windows::Foundation::IAsyncAction CSVparser::load_file(StorageFile const& file) {
	hstring file_text = co_await FileIO::ReadTextAsync(file); 
	std::string file_content = to_string(file_text); 

	std::istringstream iss(file_content); 
	std::string line; 
	m_lines.clear(); 
	while (std::getline(iss, line)) {
		if (!line.empty()) {
			m_lines.push_back(line);
		}
	}
}

std::string CSVparser::test_get_firstline(int i) const {
	if (!m_lines.empty()) {
		return m_lines[i]; 
	}
	return "empty lines";
}

std::vector<std::string> CSVparser::get_headers(const char delim) const {
	if (m_lines.empty()) {
		return {};
	}
	return Split(m_lines.front(), delim);
}

std::vector<std::vector<std::string>> CSVparser::get_rows(const char delim) const {
	std::vector<std::vector<std::string>> rows; 
	if (m_lines.size() < 2) {
		return rows; 
	}

	for (size_t i = 1; i < m_lines.size(); i++) {
		rows.push_back(Split(m_lines[i], delim));
	}
	return rows;
}

std::vector<std::string> CSVparser::get_specific_values(
	const std::vector<std::vector<std::string>>& rows, const std::vector<std::string>& headers, const std::string& searched_column) const {
	std::vector<std::string> searched_values; 
	auto index = CSVparser::get_index(headers, searched_column);
	if (index < 0) {
		return {};
	}

	for (size_t i = 0; i < rows.size(); i++) {
		searched_values.push_back(rows[i][index]);
	}
	return searched_values;
}

std::vector<std::string> CSVparser::Split(const std::string& line, char delimiter) const {
	std::vector<std::string> tokens; 
	std::string token; 
	std::istringstream token_stream(line); 
	while (std::getline(token_stream, token, delimiter)) {
		token = Trim(token); 
		if (!token.empty()) {
			tokens.push_back(token);
		}
	}

	return tokens;
}

std::string CSVparser::Trim(const std::string& str) const {
	size_t first = str.find_first_not_of(" \n\r\t");
	if (first == std::string::npos) return ""; 
	size_t last = str.find_last_not_of(" \n\r\t");
	return str.substr(first, (last - first + 1));
}

int CSVparser::get_index(const std::vector<std::string>& headers, const std::string& searched_column) const {
	auto counter = std::find(headers.begin(), headers.end(), searched_column);
	if (counter != headers.end()) {
		auto index = std::distance(headers.begin(), counter); 
		return index; 
	}
	else {
		return -1; 
	}
}

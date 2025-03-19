#include "csv_parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>



void CSVParser::load_file(std::string const& file_name) {
    // std::cout << file_name << "\n"; 
    std::ifstream file(file_name); 

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_name << "\n"; 
        return;
    }

    std::ostringstream oss; 
    oss << file.rdbuf(); 
    std::string file_content = oss.str();  
    std::string line; 
    std::istringstream iss(file_content);
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            // std::cout << line << std::endl;
            m_lines.push_back(line); 
        }
    }
}

std::vector<std::string> CSVParser::get_headers(const char delim) const {
    if (m_lines.empty()) {
        return {};
    }
    return Split(m_lines.front(), delim);
}

std::vector<std::vector<std::string>> CSVParser::get_rows(const char delim) const {
    std::vector<std::vector<std::string>> rows; 
    if (m_lines.size() < 2) {
        return rows; 
    }

    for (size_t i = 1; i < m_lines.size(); i++) {
        rows.push_back(Split(m_lines[i], delim));
    }
    return rows;
}

std::vector<std::string> CSVParser::get_specific_values(const std::vector<std::vector<std::string>>& values, const std::string& colum_name) const {
    std::vector<std::string> searched_values; 
    std::vector<std::string> temp_header = get_headers(',');
    auto index = get_index(temp_header, colum_name);
    if (index < 0 ) {
        return {};
    }

    for (size_t i = 0; i < values.size(); i++) {
        searched_values.push_back(values[i][index]);
    }
    return searched_values;
}

std::vector<std::string> CSVParser::Split(const std::string& line, char delimiter) const {
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

std::string CSVParser::Trim(const std::string& str) const {
    size_t first = str.find_first_not_of(" \n\r\t");
    if (first == std::string::npos) return ""; 
    size_t last = str.find_last_not_of(" \n\r\t");
    return str.substr(first, (last - first + 1));
}

int CSVParser::get_index(const std::vector<std::string>& headers, const std::string& searched_header) const {
    auto counter = std::find(headers.begin(), headers.end(), searched_header); 
    if (counter != headers.end()) {
        auto index = std::distance(headers.begin(), counter); 
        return index; 
    } else {
        return -1;
    }
}

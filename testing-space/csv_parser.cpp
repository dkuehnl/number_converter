#include "csv_parser.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

CSVParser::CSVParser(const std::string& file, const char& delim) : m_file(file), m_delim(delim) {
    try {
        this->parse_file(); 
        this->extract_headers();
        this->extract_rows();
    } catch (const std::exception& e) {
        m_error_msg = "Error while reading file: " + std::string(e.what()); 
        m_error = true; 
    }
}

void CSVParser::parse_file() { 
    std::ifstream file(m_file); 
    file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        std::ostringstream oss; 
        oss << file.rdbuf(); 
        std::string file_content = oss.str();  
        std::string line; 
        std::istringstream iss(file_content);
        while (std::getline(iss, line)) {
            if (!line.empty()) {
                m_lines.push_back(line); 
                m_parsed_lines++; 
            } else {
                m_empty_lines++; 
            }
        }
    } catch (const std::ifstream::failure& e) {
        throw std::runtime_error("Error reading file: " + m_file + " (" + e.what() + ")");
    }

}

void CSVParser::extract_headers() {
    if (m_lines.empty()) {
        m_headers = {};
        return;
    }
    m_headers = Split(m_lines.front());
}

void CSVParser::extract_rows() {
    if (m_lines.size() < 2) {
        m_rows = {}; 
        return;
    }

    for (size_t i = 1; i < m_lines.size(); i++) {
        m_rows.push_back(Split(m_lines[i]));
    }
}

std::vector<std::string> CSVParser::Split(const std::string& line) {
    std::vector<std::string> tokens; 
    std::string token; 
    std::istringstream token_stream(line); 
    while (std::getline(token_stream, token, m_delim)) {
        token = Trim(token); 
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::string CSVParser::Trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \n\r\t");
    if (first == std::string::npos) return ""; 
    size_t last = str.find_last_not_of(" \n\r\t");
    return str.substr(first, (last - first + 1));
}

int CSVParser::get_index(const std::vector<std::string>& headers, const std::string& searched_column) const {
    auto counter = std::find(headers.begin(), headers.end(), searched_column); 
    if (counter != headers.end()) {
        auto index = std::distance(headers.begin(), counter); 
        return index; 
    } else {
        return -1;
    }
}

const std::vector<std::vector<std::string>>& CSVParser::get_rows() const {
    return m_rows;
}

const std::vector<std::string>& CSVParser::get_headers() const {
    return m_headers;
}

void CSVParser::remove_duplicates(std::vector<std::string>& vector) {
    unsigned int values_before = vector.size(); 
    std::sort(vector.begin(), vector.end());
    vector.erase(std::unique(vector.begin(), vector.end()), vector.end()); 
    m_duplicates = values_before - vector.size(); 
}

std::vector<std::string> CSVParser::get_specific_values(const std::string& searched_column) {
    std::vector<std::string> searched_values; 
    auto index = get_index(m_headers, searched_column);
    if (index < 0 ) {
        return {};
    }

    for (size_t i = 0; i < m_rows.size(); i++) {
        searched_values.push_back(m_rows[i][index]);
    }
    remove_duplicates(searched_values);

    return searched_values;
}

const bool& CSVParser::is_valid() const {
    return m_error;
}

const std::string& CSVParser::get_error() const {
    return m_error_msg;
}

std::map<std::string, unsigned int> CSVParser::get_statistic() {
    return {
        {"parsed", m_parsed_lines}, 
        {"empty", m_empty_lines}, 
        {"duplicates", m_duplicates},
        {"total", m_empty_lines + m_parsed_lines}
    };
}
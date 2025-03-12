#include "csv_parser.h"
#include <sstream>
#include <iostream>
#include <fstream>


void CSVParser::load_file(std::string const& file_name) {
    std::cout << file_name << "\n"; 
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
            std::cout << line << std::endl;
            m_lines.push_back(line); 
        }
    }
}
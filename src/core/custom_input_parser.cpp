#include "pch.h"
#include "custom_input_parser.h"

#include <sstream>
#include <fstream>

namespace CustomInputParser {
	std::vector<std::string> parse_custom_input(winrt::hstring input) {
		std::vector<std::string> parse_lines; 

		std::string content = winrt::to_string(input); 
		std::istringstream iss(content); 
		std::string line; 

		while (std::getline(iss, line)) {
			if (!line.empty()) {
				parse_lines.push_back(line); 
			}
		}
		return parse_lines; 
	}

}
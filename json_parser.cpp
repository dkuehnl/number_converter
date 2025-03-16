#include "pch.h"
#include "json_parser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

 json_parser::json_parser(std::string const& filename) {
	 std::ifstream file(filename); 
	 if (!file) {
		 OutputDebugString(L"File couldn't be opened.\n");
		 return;
	 }
	 json json_file = json::parse(file); 

	 for (auto& [key, value] : json_file.items()) {
		 if (key == "smops") {
			 for (const auto& [inner_key, inner_value] : json_file[key].items()) {
				 if (inner_value.is_array()) {
					 for (const auto& element : inner_value) {
						 m_parsed_smops[inner_key].push_back(element.get<std::string>());
					 }
				 }
			 }
		 }
		 else if (key == "eolive") {
		 
		 }
		 else if (key == "eosight") {

		 }
	 }
}

std::unordered_map<std::string, std::vector<std::string>> json_parser::get_smops_filter() {

}

std::vector<std::string> json_parser::get_eosight_filter() {

}

std::vector<std::string> json_parser::get_eolive_filter() {

}
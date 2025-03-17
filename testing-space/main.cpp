#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "./json.hpp"
using json = nlohmann::json;

int main() {
    std::unordered_map<std::string, std::vector<std::string>> smops; 
    std::vector<std::string> eolive; 
    std::vector<std::string> eosight; 

    std::string filename = "./smops_values.json"; 
    std::ifstream file(filename); 
    json data = json::parse(file);

    for (auto& [key, value] : data.items()) {
        std::cout << "Program: " << key << std::endl; 
        if (key == "smops") {
            for (const auto& [inner_key, inner_value] : data[key].items()) {
                std::cout << "\t" << inner_key << std::endl;
                for (const auto& element : inner_value) {
                    smops[inner_key].push_back(element.get<std::string>());
                }
            }
        } else if (key == "eolive") {
            for (const auto& element : value) {
                eolive.push_back(element.get<std::string>());
            }
        } else if (key == "eosight") {
            for (const auto& element : value) {
                eosight.push_back(element.get<std::string>());
            }
        }

    }

    for (const auto& [key, value] : smops) {
        std::cout << key << std::endl; 
    }
    return 0; 
}


// CSVParser parser; 
// std::string filepath = "./test.csv";
// parser.load_file(filepath);

// for (const auto& element : value) {
//     std::cout << "\t" << element.get<std::string>() << std::endl;
// }
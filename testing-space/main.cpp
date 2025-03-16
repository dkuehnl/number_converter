#include <iostream>
#include <fstream>
#include <string>
#include "./json.hpp"
using json = nlohmann::json;

int main() {
    std::string filename = "./smops_values.json"; 
    std::ifstream file(filename); 
    json data = json::parse(file);

    for (auto& [key, value] : data.items()) {
        std::cout << "Program: " << key << std::endl; 
        if (key == "smops") {
            for (const auto& [inner_key, inner_value] : data[key].items()) {
                std::cout << "\t" << inner_key << std::endl;
                for (const auto& element : inner_value) {
                    std::cout << "\t\t" << element.get<std::string>() << std::endl;
                }
            }
        }

    }
    return 0; 
}


// CSVParser parser; 
// std::string filepath = "./test.csv";
// parser.load_file(filepath);

// for (const auto& element : value) {
//     std::cout << "\t" << element.get<std::string>() << std::endl;
// }
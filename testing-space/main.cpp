#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
#include "./json.hpp"
#include "./csv_parser.h"
#include "./convertion_manager.h"
using json = nlohmann::json;

int main() {

    CSVParser parser("./test.csv", ',');
    ConvertionManager convert; 
    convert.register_page("smops");
    
    std::vector<std::string> header = parser.get_headers(); 
    convert.set_external_file(true); 
    convert.set_filter_type("is one of"); 
    convert.set_filter_value("reg_user_agent"); 

    std::vector<std::string> searched_values = parser.get_specific_values(header[0]);
    for (const auto& element : searched_values) { 
        std::cout << element << std::endl; 
    }

    convert.convert(searched_values); 
    std::map<std::string, unsigned int> statistic = parser.get_statistic(); 
    // for (const auto& [key, value] : statistic) {
    //     std::cout << key << ": " << value << std::endl; 
    // }

    return 0; 
}




// for (const auto& element : value) {
//     std::cout << "\t" << element.get<std::string>() << std::endl;
// }


// std::unordered_map<std::string, std::vector<std::string>> smops; 
// std::vector<std::string> eolive; 
// std::vector<std::string> eosight; 

// std::string filename = "./smops_values.json"; 
// std::ifstream file(filename); 
// json data = json::parse(file);

// for (auto& [key, value] : data.items()) {
//     std::cout << "Program: " << key << std::endl; 
//     if (key == "smops") {
//         for (const auto& [inner_key, inner_value] : data[key].items()) {
//             std::cout << "\t" << inner_key << std::endl;
//             for (const auto& element : inner_value) {
//                 smops[inner_key].push_back(element.get<std::string>());
//             }
//         }
//     } else if (key == "eolive") {
//         for (const auto& element : value) {
//             eolive.push_back(element.get<std::string>());
//         }
//     } else if (key == "eosight") {
//         for (const auto& element : value) {
//             eosight.push_back(element.get<std::string>());
//         }
//     }

// }

// for (const auto& [key, value] : smops) {
//     std::cout << key << std::endl; 
// }

    // auto counter = std::find(header_test.begin(), header_test.end(), searched_header);
    // if (counter != header_test.end()) {
    //     auto index = std::distance(header_test.begin(), counter);
    //     std::cout << "Gefunden: " << index << std::endl; 
    //     for (int i = 0; i < values.size(); i++){
    //         std::cout << values[i][index] << std::endl; 
    //     }
    // } 
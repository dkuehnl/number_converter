#include <iostream>
#include "csv_parser.h"

int main() {
    CSVParser parser; 
    std::string filepath = "./test.csv";
    parser.load_file(filepath);

    return 0; 
}
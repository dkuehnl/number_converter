#pragma once
#include <string>
#include <functional>
#include <vector>

class ConvertionManager
{
public:
    ConvertionManager() = default;
    int register_page(std::string registered_page);
    //int convert(std::vector<std::string> values);
    int convert(); 
    int set_filter_type(std::string filter_type);
    int set_filter_value(std::string filter_value);
    int set_external_file(bool external);

private: 
    int check_input_valid();
    void convert_to_smops(std::vector<std::string> values);
    void convert_to_eolive(std::vector<std::string> values);
    void convert_to_eosight(std::vector<std::string> values);
    std::string m_registered_page;
    std::string m_filter_type;
    std::string m_filter_value;
    bool m_external_file = true;

    std::string m_error_msg;
};


#pragma once
#include <string>
#include <functional>
#include <vector>
#include <winrt/base.h>

class ConvertionManager
{
public:
    ConvertionManager() = default;
    int register_page(std::string registered_page);
    winrt::Windows::Foundation::IAsyncOperation<int> convert(winrt::hstring source_file, std::vector<std::string> values);
    //int convert(); 
    int set_filter_type(std::string filter_type);
    int set_filter_value(std::string filter_value);
    int set_external_file(bool external);

private: 
    int check_input_valid();
    winrt::Windows::Foundation::IAsyncAction convert_to_smops(winrt::hstring source_file, std::vector<std::string> values);
    winrt::Windows::Foundation::IAsyncAction convert_to_eolive(winrt::hstring source_file, std::vector<std::string> values);
    winrt::Windows::Foundation::IAsyncAction convert_to_eosight(winrt::hstring source_file, std::vector<std::string> values);
    std::string m_registered_page;
    std::string m_filter_type;
    std::string m_filter_value;
    bool m_external_file = true;

    std::string m_error_msg;
};


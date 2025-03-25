#include "pch.h"
#include "convertion_manager.h"
#include "file_handling.h"
#include <string>
#include <sstream>
#include <windows.h>


int ConvertionManager::register_page(std::string registered_page) {
	if (registered_page == "smops") {
		m_registered_page = registered_page;
		return 0;
	}
	else {
		m_error_msg = "Unknown Page-Type, no Convertion-Routine available";
		return -1;
	}
}

int ConvertionManager::convert(winrt::hstring source_file, std::vector<std::string> values) {
//int ConvertionManager::convert() {
    OutputDebugStringA(m_filter_value.c_str());
    OutputDebugString(L"\n"); 
    OutputDebugStringA(m_filter_type.c_str()); 
    OutputDebugString(L"\n"); 

    if (values.size() == 0) {
        return 1;
    }
    if (check_input_valid() == 1) {
        return 1;
    }
    if (m_registered_page == "smops") {
        convert_to_smops(source_file, values);
    }
    else if (m_registered_page == "eolive") {
        convert_to_eolive(values);
    }
    else if (m_registered_page == "eosight") {
        convert_to_eosight(values);
    }

    return 0;
}

int ConvertionManager::set_filter_type(std::string filter_type) {
    m_filter_type = filter_type;
    return 0;
}

int ConvertionManager::set_filter_value(std::string filter_value) {
    m_filter_value = filter_value;
    return 0;
}

int ConvertionManager::set_external_file(bool external) {
    m_external_file = external;
    return 0;
}

int ConvertionManager::check_input_valid() {
    if (m_filter_type.empty() || m_filter_value.empty()) {
        return 1;
    }
    return 0;
}

void ConvertionManager::convert_to_smops(winrt::hstring source_file, std::vector<std::string> values) {
    std::wstringstream wss;
    if (m_filter_type == "is one of") {
        wss << "{\n"
            << "\"query\": {\n"
            << "\"bool\": {\n"
            << "\"should\": [\n";
    }
    else if (m_filter_type == "is not one of") {
        wss << "{\n"
            << "\"query\": {\n"
            << "\"bool\": {\n"
            << "\"must_not\": [\n";
    }
    else {
        m_error_msg = "Unknown filter-type";
        return;
    }

    for (std::size_t i = 0; i < values.size() - 1; i++) {
        std::wstring w_value(values[i].begin(), values[i].end()); 
        std::wstring w_filter(m_filter_value.begin(), m_filter_value.end()); 
        wss << "{\n"
            << "\"match_phrase\": {\n"
            << "\""
            << w_filter
            << "\": \""
            << w_value
            << "\"\n"
                << "}\n"
                << "},\n";
    }

    std::wstring w_last_value(values.back().begin(), values.back().end()); 
    std::wstring w_filter(m_filter_value.begin(), m_filter_value.end()); 
    wss << "{\n"
        << "\"match_phrase\": {\n"
        << "\""
        << w_filter
        << "\": \""
        << w_last_value
        << "\"\n"
        << "}\n"
        << "}\n";

    wss << "],\n"
        << "\"minimum_should_match\": 1\n"
        << "}\n"
        << "}\n"
        << "}";

    std::wstring content = wss.str(); 
    auto async_write = FileHandler::write_file(source_file, content)

}

void ConvertionManager::convert_to_eolive(std::vector<std::string> values) {

}

void ConvertionManager::convert_to_eosight(std::vector<std::string> values) {

}

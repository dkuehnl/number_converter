#include "pch.h"
#include "convertion_manager.h"
#include <string>
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

//int ConvertionManager::convert(std::vector<std::string> values) {
int ConvertionManager::convert() {
    OutputDebugStringA(m_filter_value.c_str());
    OutputDebugString(L"\n"); 
    OutputDebugStringA(m_filter_type.c_str()); 
    OutputDebugString(L"\n"); 

    //if (values.size() == 0) {
    //    return 1;
    //}
    //if (check_input_valid() == 1) {
    //    return 1;
    //}
    //if (m_registered_page == "smops") {
    //    convert_to_smops(values);
    //}
    //else if (m_registered_page == "eolive") {
    //    convert_to_eolive(values);
    //}
    //else if (m_registered_page == "eosight") {
    //    convert_to_eosight(values);
    //}

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

void ConvertionManager::convert_to_smops(std::vector<std::string> values) {
    /*std::ofstream outfile("./test_output.txt");
    if (m_filter_type == "is one of") {
        outfile << "{\n"
            << "\"query\": {\n"
            << "\"bool\": {\n"
            << "\"should\": [\n";
    }
    else if (m_filter_type == "is not one of") {
        outfile << "{\n"
            << "\"query\": {\n"
            << "\"bool\": {\n"
            << "\"must_not\": [\n";
    }
    else {
        m_error_msg = "Unknown filter-type";
        return;
    }

    for (std::size_t i = 0; i < values.size() - 1; i++) {
        outfile << "{\n"
            << "\"match_phrase\": {\n"
            << "\""
            << m_filter_value
            << "\": \""
            << values[i]
            << "\"\n"
                << "}\n"
                << "},\n";
    }
    outfile << "{\n"
        << "\"match_phrase\": {\n"
        << "\""
        << m_filter_value
        << "\": \""
        << values.back()
        << "\"\n"
        << "}\n"
        << "}\n";

    outfile << "],\n"
        << "\"minimum_should_match\": 1\n"
        << "}\n"
        << "}\n"
        << "}";

    outfile.close();*/
}

void ConvertionManager::convert_to_eolive(std::vector<std::string> values) {

}

void ConvertionManager::convert_to_eosight(std::vector<std::string> values) {

}

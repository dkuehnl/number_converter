#include "pch.h"
#include "convertion_manager.h"
#include "file_handling.h"
#include <string>
#include <sstream>
#include <windows.h>


int ConvertionManager::register_page(std::string registered_page) {
	if (registered_page == "SMOPS") {
		m_registered_page = registered_page;
		return 0;
	}
	else {
		m_error_msg = "Unknown Page-Type, no Convertion-Routine available";
		return -1;
	}
}

winrt::Windows::Foundation::IAsyncOperation<int> ConvertionManager::convert(winrt::hstring source_file, std::vector<std::string> values) {
    if (values.size() == 0) {
        m_error_msg = "No valid values found to convert";
        co_return 1;
    }
    if (check_input_valid() == 1) {
        m_error_msg = "No valid filter-value available"; 
        co_return 1;
    }

    try {
        if (m_registered_page == "SMOPS") {
            co_await convert_to_smops(source_file, values);
        }
        else if (m_registered_page == "eoLive") {
            co_await convert_to_eolive(source_file, values);
        }
        else if (m_registered_page == "eoSight") {
            co_await convert_to_eosight(source_file, values);
        }
        else {
            m_error_msg = "registered Page not found";
            co_return 1;
        }
    }
    catch (const winrt::hresult_error& e) {
        m_error_msg = winrt::to_string(e.message()); 
        co_return 1; 
    }
    

    co_return 0;
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

winrt::Windows::Foundation::IAsyncAction ConvertionManager::convert_to_smops(winrt::hstring source_file, std::vector<std::string> values) {
    try {
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
            co_return;
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
        co_await FileHandler::write_file(source_file, std::wstring(m_registered_page.begin(), m_registered_page.end()), content);
    }
    catch (const winrt::hresult_error& e) {
        m_error_msg = winrt::to_string(e.message());
    }
    co_return;
}

winrt::Windows::Foundation::IAsyncAction ConvertionManager::convert_to_eolive(winrt::hstring source_file, std::vector<std::string> values) {
    std::wstringstream wss; 
    std::wstring w_filter(m_filter_value.begin(), m_filter_value.end());
    if (m_filter_type == "begins") {
        wss << "["
            << w_filter
            << "] begins (";
    }

    for (std::size_t i = 0; i < values.size() - 1; i++) {
        std::wstring w_value(values[i].begin(), values[i].end());
        wss << "\""
            << w_value
            << "\", ";
    }
    std::wstring w_last_value(values.back().begin(), values.back().end());
    wss << "\""
        << w_last_value
        << "\")";

    std::wstring content = wss.str();
    co_await FileHandler::write_file(source_file, std::wstring(m_registered_page.begin(), m_registered_page.end()), content);
    co_return;
}

winrt::Windows::Foundation::IAsyncAction ConvertionManager::convert_to_eosight(winrt::hstring source_file, std::vector<std::string> values) {
    std::wstringstream wss; 
    std::wstring w_filter(m_filter_value.begin(), m_filter_value.end());
    if (m_filter_type == "contains") {
        for (std::size_t i = 0; i < values.size() - 1; i++) {
            std::wstring w_value(values[i].begin(), values[i].end());
            wss << "CONTAINS(["
                << w_filter
                << "], \""
                << w_value
                << "\") or ";
        }
        std::wstring w_last_value(values.back().begin(), values.back().end());
        wss << "CONTAINS(["
            << w_filter
            << "], \""
            << w_last_value
            << "\")";

    }
    else if (m_filter_type == "equal") {
        for (std::size_t i = 0; i < values.size() - 1; i++) {
            std::wstring w_value(values[i].begin(), values[i].end()); 
            wss << "["
                << w_filter
                << "] = \""
                << w_value
                << "\" or ";
        }
        std::wstring w_last_value(values.back().begin(), values.back().end());
        wss << "["
            << w_filter
            << "] = \""
            << w_last_value
            << "\"";
    }
    else {
        co_return; 
    }

    std::wstring content = wss.str();
    co_await FileHandler::write_file(source_file, std::wstring(m_registered_page.begin(), m_registered_page.end()), content);
    co_return;
}

std::string ConvertionManager::get_error_msg() {
    return m_error_msg;
}
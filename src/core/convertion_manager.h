#pragma once
#include <string>
#include <functional>
#include <vector>
#include <winrt/base.h>

/// @brief Builds a target-system query/filter expression from a list of values and writes it to file.
///
/// Usage: register_page() picks the output format (currently only "SMOPS"
/// is accepted, even though convert() also handles "eoLive"/"eoSight"),
/// set_filter_type()/set_filter_value() configure the filter clause, then
/// convert() builds the expression and writes it next to the source file
/// via FileHandler::write_file().
class ConvertionManager
{
public:
    ConvertionManager() = default;

    /// @brief Selects the output format to convert to.
    /// @param registered_page Target system name; only `"SMOPS"` is currently accepted.
    /// @return 0 on success, -1 if @p registered_page is unknown (see get_error_msg()).
    int register_page(std::string registered_page);

    /// @brief Builds the filter expression for the registered page and writes it to a new file next to @p source_file.
    /// @param source_file Path of the file the converted output is derived from/written next to.
    /// @param values The values to filter on.
    /// @return 0 on success, 1 on failure (see get_error_msg()).
    winrt::Windows::Foundation::IAsyncOperation<int> convert(winrt::hstring source_file, std::vector<std::string> values);

    /// @return The last error message, if any.
    std::string get_error_msg(); 

    /// @brief Sets the filter operator (e.g. "is one of", "contains", "begins" -- meaning depends on the registered page).
    int set_filter_type(std::string filter_type);

    /// @brief Sets the column/field name the filter applies to.
    int set_filter_value(std::string filter_value);

    /// @brief Marks whether the source file is external (currently unused by check_input_valid()).
    int set_external_file(bool external);

private: 
    /// @return 1 if m_filter_type or m_filter_value is unset, 0 otherwise.
    int check_input_valid();

    /// @brief Builds an Elasticsearch-style bool query and writes it via FileHandler::write_file().
    winrt::Windows::Foundation::IAsyncAction convert_to_smops(winrt::hstring source_file, std::vector<std::string> values);

    /// @brief Builds an eoLive "begins (...)" filter expression and writes it via FileHandler::write_file().
    winrt::Windows::Foundation::IAsyncAction convert_to_eolive(winrt::hstring source_file, std::vector<std::string> values);

    /// @brief Builds an eoSight CONTAINS()/equality filter expression and writes it via FileHandler::write_file().
    winrt::Windows::Foundation::IAsyncAction convert_to_eosight(winrt::hstring source_file, std::vector<std::string> values);

    std::string m_registered_page;
    std::string m_filter_type;
    std::string m_filter_value;
    bool m_external_file = true;

    std::string m_error_msg;
};

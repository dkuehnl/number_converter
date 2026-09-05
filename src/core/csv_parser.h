#pragma once

#include <string>
#include <vector>
#include <winrt/Windows.Storage.h>

/// @brief Parses a delimited (e.g. CSV) StorageFile into headers/rows.
///
/// Construction only stores the file/delimiter; call initialize() to
/// actually read and parse it (reading a StorageFile is async, so this
/// can't happen in the constructor).
class CSVParser {
private: 
    //File-related variables
    winrt::Windows::Storage::StorageFile m_file;
    char m_delim;
    std::vector<std::string> m_lines;
    std::vector<std::string> m_headers;
    std::vector<std::vector<std::string>> m_rows;

    //Error-related variables
    std::string m_error_msg;
    bool m_error = false;

    //Statistic variables
    unsigned int m_parsed_lines = 0;
    unsigned int m_empty_lines = 0;
    unsigned int m_duplicates = 0;

    /// @brief Reads m_file and splits it into m_lines, tracking parsed/empty-line counts.
    winrt::Windows::Foundation::IAsyncAction parse_file();

    /// @brief Splits the first line of m_lines into m_headers.
    void extract_headers();

    /// @brief Splits every line but the first into m_rows.
    void extract_rows();

    /// @brief Removes duplicate entries from @p vector (sorts it as a side effect) and records the count in m_duplicates.
    void remove_duplicates(std::vector<std::string>& vector);

    /// @brief Removes empty entries from @p vector.
    void drop_empty_cells(std::vector<std::string>& vector);

    /// @brief Splits @p line on m_delim, trimming each field.
    std::vector<std::string> Split(const std::string& line);

    /// @brief Trims leading/trailing whitespace from @p str.
    std::string Trim(const std::string& str);

    /// @brief Index of @p searched_header within @p headers, or -1 if not found.
    int get_index(const std::vector<std::string>& headers, const std::string& searched_header) const;
	
public:
    /// @brief Stores the file to parse and the field delimiter to use.
    /// @param file StorageFile to read (not yet read at this point).
    /// @param delim Field delimiter (e.g. `,` or `;`).
    CSVParser(winrt::Windows::Storage::StorageFile const& file, const char& delim); 

    /// @brief Reads m_file and populates headers/rows. Sets is_valid()/get_error() on failure.
    winrt::Windows::Foundation::IAsyncAction initialize(); 
	//winrt::Windows::Foundation::IAsyncAction load_file(winrt::Windows::Storage::StorageFile const& file);

    /// @return The parsed header row.
    const std::vector<std::string>& get_headers() const;

    /// @return The parsed data rows (header row excluded).
    const std::vector<std::vector<std::string>>& get_rows() const;

    /// @brief Collects every (deduplicated, non-empty) value seen in @p searched_column.
    /// @param searched_column Header name to look up.
    /// @return The distinct, non-empty values in that column, or empty if the column isn't found.
    std::vector<std::string> get_specific_values(const std::string& searched_column);

    /// @return The last parse error message, if any.
    const std::string& get_error() const;

    /// @return Whether parsing failed. @note Despite the name, this returns m_error (true means invalid).
    const bool& is_valid() const;

    /// @return Parsed/empty/duplicate/total line counts from the last parse.
    std::map<std::string, unsigned int> get_statistic();
};

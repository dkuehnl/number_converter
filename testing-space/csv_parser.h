#include <string>
#include <vector>

class CSVParser {
    private:
        std::vector<std::string> m_lines; 
        std::vector<std::string> Split(const std::string& line, char delimiter) const; 
        std::string Trim(const std::string& str) const;
        int get_index(const std::vector<std::string>& headers, const std::string& searched_header) const;

    public: 
        CSVParser() = default; 
        void load_file(std::string const& filepath); 
        std::vector<std::string> get_headers(const char delim) const;
        std::string test_get_firstline(int i) const;
        std::vector<std::vector<std::string>> get_rows(const char delim) const;
        std::vector<std::string> get_specific_values(const std::vector<std::vector<std::string>>& values, const std::string& colum_name) const;

};
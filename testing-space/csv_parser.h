#include <string>
#include <vector>
#include <map>


class CSVParser {
    private:
        //File-related variables
        std::string m_file; 
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

        void parse_file(); 
        void extract_headers();
        void extract_rows(); 
        void remove_duplicates(std::vector<std::string>& vector); 

        std::vector<std::string> Split(const std::string& line); 
        std::string Trim(const std::string& str);
        int get_index(const std::vector<std::string>& headers, const std::string& searched_header) const;

    public: 
        CSVParser(const std::string& file, const char& delim); 
        const std::vector<std::string>& get_headers() const;
        const std::vector<std::vector<std::string>>& get_rows() const;
        std::vector<std::string> get_specific_values(const std::string& searched_column);
        const std::string& get_error() const; 
        const bool& is_valid() const; 
        std::map<std::string, unsigned int> get_statistic();
};
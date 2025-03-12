#include <string>
#include <vector>

class CSVParser {
    private:
        std::vector<std::string> m_lines; 

    public: 
        CSVParser() = default; 
        void load_file(std::string const& filepath); 

};
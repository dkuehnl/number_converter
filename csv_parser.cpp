#include "csv_parser.h"
#include <sstream>
#include <winrt/base.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt; 
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Foundation; 

void CSVparser::load_file(StorageFile const& file) {
	hstring file_text = FileIO::ReadTextAsync(file).get(); 
	std::string file_content = to_string(file_text); 

	std::istringstream iss(file_content); 
	std::string line; 
	m_lines.clear(); 
	while (std::getline(iss, line)) {
		if (!line.empty()) {
			m_lines.push_back(line);
		}
	}
}
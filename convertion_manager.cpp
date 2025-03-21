#include "pch.h"
#include "convertion_manager.h"
#include <string>
#include <windows.h>


//void convertion_manager::register_page(data_callback callback) {
//	page = callback;
//}
void convertion_manager::register_page(std::string page) {
	m_registered_page = page; 
	std::wstring wmsg(m_registered_page.begin(), m_registered_page.end()); 
	OutputDebugString(wmsg.c_str()); 
}

void convertion_manager::test_information_transfer(std::vector<std::string> values) {
	//OutputDebugString(L"\n");
	//for (const auto& element : values) {
	//	std::wstring wmsg(element.begin(), element.end()); 
	//	OutputDebugString(wmsg.c_str()); 
	//	OutputDebugString(L"\n");
	//}
	//if (page) {
	//	auto data = page(); 
	//	for (const auto& [key, value] : data) {
	//		std::wstring wmsg_key(key.begin(), key.end());
	//		std::wstring wmsg_value(value.begin(), value.end()); 
	//		OutputDebugString(wmsg_key.c_str());
	//		OutputDebugString(L"\n"); 
	//		OutputDebugString(wmsg_value.c_str()); 
	//		OutputDebugString(L"\n");
	//	}
	//}
}

void convertion_manager::print_test() {
	OutputDebugString(L"Message from convertion_manager\n\n");
}

#include "pch.h"
#include "convertion_manager.h"
#include "smops.xaml.h"
#include <windows.h>
#include <string>


convertion_manager::convertion_manager(std::string test_var) {
	std::wstring wmsg(test_var.begin(), test_var.end()); 
	OutputDebugString(wmsg.c_str()); 
}


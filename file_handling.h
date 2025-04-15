#pragma once
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <ShObjIdl.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/base.h>


namespace FileHandler {
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> pick_file(HWND hWnd); 
	winrt::Windows::Foundation::IAsyncAction write_file(const winrt::hstring& source_file, const std::wstring& destination_system, const std::wstring& conten);
	winrt::hstring build_new_filename(const winrt::hstring& source_file, const std::wstring& destination_system);
	winrt::hstring get_folder_path(const winrt::hstring& source_file);
	winrt::hstring get_downloads_path();
}
#pragma once
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <ShObjIdl.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/base.h>


namespace FileHandler {
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> pick_file(HWND hWnd); 
	winrt::Windows::Foundation::IAsyncAction write_file(const winrt::hstring& source_file, const std::wstring& content);
}
#pragma once
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <ShObjIdl.h>
#include <winrt/Microsoft.UI.Xaml.h>


namespace FileHandler {
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> pick_file(HWND hWnd); 
}
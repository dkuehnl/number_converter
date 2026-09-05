#include "pch.h"
#include "file_handling.h"
#pragma comment(lib, "Shell32.lib")

#include <filesystem>
#include <cstdlib>

#include <winrt/base.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Foundation.h>
#include <windows.h>
#include <ShlObj.h>
#include <KnownFolders.h>

namespace FileHandler {
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> pick_file(HWND hWnd) {

        winrt::Windows::Storage::Pickers::FileOpenPicker open_picker;

        auto picker_interop = open_picker.as<::IInitializeWithWindow>();
        winrt::check_hresult(picker_interop->Initialize(hWnd));

        open_picker.ViewMode(winrt::Windows::Storage::Pickers::PickerViewMode::Thumbnail);
        open_picker.SuggestedStartLocation(winrt::Windows::Storage::Pickers::PickerLocationId::DocumentsLibrary);
        open_picker.FileTypeFilter().ReplaceAll({ L".csv", L".xls", L".xlsx" });
        
        co_return co_await open_picker.PickSingleFileAsync();
  
    }

    winrt::Windows::Foundation::IAsyncAction write_file(const winrt::hstring& source_file, const std::wstring& destination_system, const std::wstring& content) {
        winrt::hstring new_filename = build_new_filename(source_file, destination_system); 
        winrt::hstring folder_path = get_folder_path(source_file); 

        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(folder_path);
        auto new_file = co_await folder.CreateFileAsync(new_filename + L".txt", winrt::Windows::Storage::CreationCollisionOption::GenerateUniqueName);
        co_await winrt::Windows::Storage::FileIO::WriteTextAsync(new_file, content);
        co_return;
    }

    winrt::hstring build_new_filename(const winrt::hstring& source_file, const std::wstring& destination_system) {
        std::filesystem::path pathObj(source_file.c_str());
        std::wstring w_old_filename = pathObj.stem().wstring();

        std::wstring w_new_filename = w_old_filename + L"_" + destination_system + L"_converted";
        winrt::hstring new_filename(w_new_filename.c_str());
        return new_filename;
    }

    winrt::hstring get_folder_path(const winrt::hstring& source_file) {
        std::wstring wmsg(source_file.begin(), source_file.end());
        std::filesystem::path fs_path(wmsg);

        std::wstring w_folder_path = fs_path.parent_path().wstring();        
        winrt::hstring folder_path(w_folder_path.c_str());
        return folder_path;
    }

    winrt::hstring get_downloads_path() {
        PWSTR path = nullptr; 
        std::wstring download_path; 
        if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, nullptr, &path))) {
            download_path = path; 
            CoTaskMemFree(path); 
        }

        return winrt::to_hstring(download_path.c_str());
    }

}

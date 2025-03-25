#include "pch.h"
#include "file_handling.h"

#include <filesystem>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Foundation.h>

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

    winrt::Windows::Foundation::IAsyncAction write_file(const winrt::hstring& source_file, const std::wstring& content) {
        std::wstring wmsg(source_file.begin(), source_file.end());
        std::filesystem::path fs_path(wmsg);

        std::wstring folder_path = fs_path.parent_path().wstring();
        auto folder = co_await winrt::Windows::Storage::StorageFolder::GetFolderFromPathAsync(winrt::hstring(folder_path));
        auto new_file = co_await folder.CreateFileAsync(L"test_file.txt", winrt::Windows::Storage::CreationCollisionOption::GenerateUniqueName);
        co_await winrt::Windows::Storage::FileIO::WriteTextAsync(new_file, content);
        co_return;
    }

}

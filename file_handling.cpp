#include "pch.h"
#include "file_handling.h"

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>

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
}

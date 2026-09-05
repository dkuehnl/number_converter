#pragma once
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <ShObjIdl.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/base.h>

/// @brief File-picking and file-writing helpers used to load a source file and save conversion output next to it.
namespace FileHandler {
	/// @brief Shows a file-open picker filtered to `.csv`/`.xls`/`.xlsx`.
	/// @param hWnd Owning window handle (required by the WinRT file picker on desktop apps).
	/// @return The picked file, or null if the user cancelled.
	winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> pick_file(HWND hWnd); 

	/// @brief Writes @p content to a new, uniquely-named `.txt` file in the same folder as @p source_file.
	/// @param source_file Path of the original source file; determines the destination folder and base filename.
	/// @param destination_system Target-system name, used to build the output filename (see build_new_filename()).
	/// @param conten Text content to write.
	winrt::Windows::Foundation::IAsyncAction write_file(const winrt::hstring& source_file, const std::wstring& destination_system, const std::wstring& conten);

	/// @brief Builds the output filename (without extension) as `<source stem>_<destination_system>_converted`.
	winrt::hstring build_new_filename(const winrt::hstring& source_file, const std::wstring& destination_system);

	/// @brief Returns the folder containing @p source_file.
	winrt::hstring get_folder_path(const winrt::hstring& source_file);

	/// @brief Returns the current user's Downloads folder path.
	winrt::hstring get_downloads_path();
}

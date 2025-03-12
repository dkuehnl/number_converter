#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "smops.xaml.h"
#include "eolive.xaml.h"
#include "eosight.xaml.h"

#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <microsoft.ui.xaml.window.h>
#include <Shobjidl.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Windowing;
using namespace Microsoft::UI; 
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    MainWindow::MainWindow() {
        this->InitializeComponent(); 
        _appWindow = this->AppWindow(); 
        _appWindow.Title(L"First Try for C++-Windows application");
        if (AppWindowTitleBar::IsCustomizationSupported()) {
            _titleBar = _appWindow.TitleBar(); 
            
            _titleBar.BackgroundColor(Microsoft::UI::Colors::Black());
            _titleBar.InactiveBackgroundColor(Microsoft::UI::Colors::Black()); 
            _titleBar.ButtonBackgroundColor(Microsoft::UI::Colors::Black());
            _titleBar.ButtonHoverBackgroundColor(winrt::Windows::UI::ColorHelper::FromArgb(255, 60, 64, 67));
            _titleBar.ButtonInactiveBackgroundColor(Microsoft::UI::Colors::Black()); 

            _titleBar.IconShowOptions(IconShowOptions::HideIconAndSystemMenu);
        }
        ContentFrame().Navigate(xaml_typename<App1::smops>());
    }

    void MainWindow::navView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args) {
        auto selectedItem = args.SelectedItem().try_as<Microsoft::UI::Xaml::Controls::NavigationViewItem>(); 
        if (selectedItem) {
            hstring tag = unbox_value<hstring>(selectedItem.Tag()); 
            if (tag == L"smops") {
                ContentFrame().Navigate(xaml_typename<App1::smops>()); 
            }
            else if (tag == L"eolive") {
                ContentFrame().Navigate(xaml_typename<App1::eolive>());
            }
            else if (tag == L"eosight") {
                ContentFrame().Navigate(xaml_typename<App1::eosight>()); 
            }
        }
    }
    
    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    winrt::fire_and_forget MainWindow::click_file_picker(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        auto lifetime = get_strong(); 

        file_picker().IsEnabled(false); 

        Windows::Storage::Pickers::FileOpenPicker open_picker; 
        auto window_native{ this->m_inner.as<::IWindowNative>() };
        HWND hWnd{ 0 };
        window_native->get_WindowHandle(&hWnd); 

        auto picker_interop = open_picker.as<::IInitializeWithWindow>();
        winrt::check_hresult(picker_interop->Initialize(hWnd));

        open_picker.ViewMode(PickerViewMode::Thumbnail); 
        open_picker.SuggestedStartLocation(PickerLocationId::DocumentsLibrary);
        open_picker.FileTypeFilter().ReplaceAll({ L".csv", L".xls", L".xlsx" });
        StorageFile file = co_await open_picker.PickSingleFileAsync(); 
        if (file != nullptr) {
            file_picker_output().Text(file.Name()); 
            file_picker().IsEnabled(true); 
        }
        else {
            file_picker_output().Text(L"No File selected"); 
            file_picker().IsEnabled(true); 
        }
    }

}

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "smops.xaml.h"
#include "eolive.xaml.h"
#include "eosight.xaml.h"

#include <iostream>
#include <algorithm>

#include <winrt/Microsoft.UI.Windowing.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Xaml.Documents.h>
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

#define MAX_PREVIEW_VALUE 10

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
            m_selected_file = file;
        }
        else {
            file_picker_output().Text(L"No File selected"); 
            file_picker().IsEnabled(true); 
        }
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::btn_convert_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        if (m_selected_file != nullptr) {
            if (m_selected_file.FileType() == L".csv") {
                co_await m_csv_parser.load_file(m_selected_file);

                char delim = winrt::to_string(m_selected_delim)[0];
                data_output().Inlines().Clear(); 
                m_headers = m_csv_parser.get_headers(delim);
                
                m_header_collection.Clear(); 
                for (const std::string& headers : m_headers) {
                    m_header_collection.Append(winrt::to_hstring(headers)); 
                    auto header_text = winrt::Microsoft::UI::Xaml::Documents::Run(); 
                    auto bold = winrt::Microsoft::UI::Xaml::Documents::Bold(); 
                    header_text.Text(winrt::to_hstring(headers) + L"\t");
                    bold.Inlines().Append(header_text);
                    data_output().Inlines().Append(bold); 
                }
                cb_header().ItemsSource(m_header_collection); 
                cb_header().SelectedIndex(0);
                

                m_values = m_csv_parser.get_rows(delim);
                for (int i = 0; i < std::min(MAX_PREVIEW_VALUE, m_values.size()); i++) {
                    auto outer_text = winrt::Microsoft::UI::Xaml::Documents::Run(); 
                    outer_text.Text(L"\n");
                    data_output().Inlines().Append(outer_text);
                    for (const auto& values : m_values[i]) {
                        auto inner_text = winrt::Microsoft::UI::Xaml::Documents::Run();
                        inner_text.Text(winrt::to_hstring(values) + L"\t");
                        data_output().Inlines().Append(inner_text); 
                    }
                }
            } 
        }
        else {
            data_output().Text(L"No File selected"); 
        }
        
    }

    void MainWindow::delim_menu_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        auto menu_item = sender.as<winrt::Microsoft::UI::Xaml::Controls::MenuFlyoutItem>(); 
        if (menu_item) {
            hstring selected_value = menu_item.Text(); 
            btn_delim().Content(box_value(selected_value));

            m_selected_delim = selected_value;
        }
    }

}

#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include "smops.xaml.h"
#include "eolive.xaml.h"
#include "eosight.xaml.h"
#include "convertion_manager.h"
#include "file_handling.h"
#include "App.xaml.h" 

#include <iostream>
#include <algorithm>
#include <filesystem>

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

constexpr auto MAX_PREVIEW_VALUE = 10;

namespace winrt::App1::implementation
{
    MainWindow::MainWindow() : m_convert(App::GetConvertionManager()) {
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

        auto window_native{ this->m_inner.as<::IWindowNative >() };
        HWND hWnd{ 0 };
        window_native->get_WindowHandle(&hWnd);

        winrt::Windows::Storage::StorageFile file = co_await FileHandler::pick_file(hWnd); 
        if (file != nullptr) {
            file_picker_output().Text(file.Name());
            m_selected_file = file;
            co_await display_file();
        }
        else {
            file_picker_output().Text(L"No File selected");
        }
        file_picker().IsEnabled(true);
    }

    winrt::Windows::Foundation::IAsyncAction MainWindow::display_file() {
        if (m_selected_file != nullptr) {
            if (m_selected_file.FileType() == L".csv") {
                char delim = winrt::to_string(m_selected_delim)[0];
                data_output().Inlines().Clear(); 

                m_parser = std::make_unique<CSVParser>(m_selected_file, delim); 
                co_await m_parser->initialize(); 
                
                m_header_collection.Clear(); 
                std::vector<std::string> headers = m_parser->get_headers(); 
                for (const std::string& headers : headers) {
                    m_header_collection.Append(winrt::to_hstring(headers)); 
                    auto header_text = winrt::Microsoft::UI::Xaml::Documents::Run(); 
                    auto bold = winrt::Microsoft::UI::Xaml::Documents::Bold(); 
                    header_text.Text(winrt::to_hstring(headers) + L"\t");
                    bold.Inlines().Append(header_text);
                    data_output().Inlines().Append(bold); 
                }
                cb_header().ItemsSource(m_header_collection); 
                cb_header().SelectedIndex(0);
                
                std::vector<std::vector<std::string>> values = m_parser->get_rows();
                for (int i = 0; i < min(MAX_PREVIEW_VALUE, values.size()); i++) {
                    auto outer_text = winrt::Microsoft::UI::Xaml::Documents::Run(); 
                    outer_text.Text(L"\n");
                    data_output().Inlines().Append(outer_text);
                    for (const auto& value : values[i]) {
                        auto inner_text = winrt::Microsoft::UI::Xaml::Documents::Run();
                        inner_text.Text(winrt::to_hstring(value) + L"\t");
                        data_output().Inlines().Append(inner_text); 
                    }
                }
            }
            else if (m_selected_file.FileType() == L".xls") {
                MainWindow::handle_infobar("Info", L"The file-type .xls is not implemented yet.", "info");
            }
        }
        else {
            data_output().Text(L"No File selected"); 
        }
    }

    void MainWindow::cb_delim_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
        if (auto com_box = sender.try_as<ComboBox>()) {
            if (auto selected_item = com_box.SelectedItem().try_as<ComboBoxItem>()) {
                m_selected_delim = selected_item.Content().as<hstring>(); 
            }
            else {
                MainWindow::handle_infobar("Error", L"combox couldn't be assigned, using standard-value", "error");
                m_selected_delim = L",";
            }
        }
        else {
            MainWindow::handle_infobar("Error", L"combox couldn't be assigned, using standard-value", "error");
            m_selected_delim = L",";
        }
    }

    void MainWindow::cb_header_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
        if (auto com_box = sender.try_as<ComboBox>()) {
            if (com_box.SelectedItem() != nullptr) {
                m_selected_header = winrt::unbox_value<hstring>(com_box.SelectedItem());
                hstring message = L"Selected header: " + m_selected_header;
                MainWindow::handle_infobar("Info", message, "info");
            }
            else {
                MainWindow::handle_infobar("Error", L"Combox empty, could not assign any value for further proceeding", "error"); 
                m_selected_header = L" ";
            }
        }
        else {
            MainWindow::handle_infobar("Error", L"Something went wrong with the combox-object", "error");
            m_selected_header = L" ";
        }
    }

    void MainWindow::handle_infobar(const std::string& title, const hstring& message, const std::string& severity) {
        message_window().Title(winrt::to_hstring(title) + L": ");
        message_window().Message(message); 

        if (severity == "info") {
            message_window().Severity(InfoBarSeverity::Informational); 
        }
        else if (severity == "warning") {
            message_window().Severity(InfoBarSeverity::Warning); 
        }
        else if (severity == "error") {
            message_window().Severity(InfoBarSeverity::Error);
        }
        else if (severity == "success") {
            message_window().Severity(InfoBarSeverity::Success);
        }
        else {
            message_window().Severity(InfoBarSeverity::Informational);
        }

        message_window().IsOpen(true); 
    }

    winrt::fire_and_forget MainWindow::btn_convert_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args) {
        std::vector<std::string> searched_values = m_parser->get_specific_values(winrt::to_string(m_selected_header));
        if (co_await m_convert.convert(m_selected_file.Path(), searched_values) != 0) {
            MainWindow::handle_infobar("Error", winrt::to_hstring(m_convert.get_error_msg()), "error"); 
        }
        else {
            MainWindow::handle_infobar("Info", L"Konvertierung erfolgreich", "success"); 
        }

    }

}

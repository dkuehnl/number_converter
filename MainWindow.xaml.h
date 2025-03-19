#pragma once

#include "MainWindow.g.h"
#include "csv_parser.h"
#include "json_parser.h"
#include "convertion_manager.h"
#include <winrt/Windows.Foundation.h>
#include "base_page.h"

namespace winrt::App1::implementation
{
    struct MainWindow : MainWindowT<MainWindow>, base_page
    {
        MainWindow();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        void navView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
        fire_and_forget click_file_picker(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void cb_delim_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void cb_header_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void handle_infobar(const std::string& title, const hstring& message, const std::string& severity); 
        void btn_convert_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args); 

        std::map<std::string, std::string> get_data() override;

    private:
        convertion_manager& m_convert;
        winrt::Microsoft::UI::Windowing::AppWindow _appWindow{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar _titleBar{ nullptr };
        winrt::Windows::Storage::StorageFile m_selected_file{ nullptr };
        CSVparser m_csv_parser; 
        hstring m_selected_delim = L",";
        std::vector<std::string> m_headers;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> m_header_collection{winrt::single_threaded_observable_vector<winrt::hstring>()};
        std::vector<std::vector<std::string>> m_values;
        winrt::Windows::Foundation::IAsyncAction display_file();
        hstring m_selected_header = L" ";
    };
}

namespace winrt::App1::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}

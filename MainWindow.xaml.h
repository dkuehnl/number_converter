#pragma once

#include <memory>
#include "MainWindow.g.h"
#include "csv_parser.h"
#include "json_parser.h"
#include "convertion_manager.h"
#include <winrt/Windows.Foundation.h>


namespace winrt::App1::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        void navView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);
        fire_and_forget click_file_picker(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void cb_delim_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void cb_header_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        void handle_infobar(const std::string& title, const hstring& message, const std::string& severity); 
        winrt::fire_and_forget btn_convert_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        ConvertionManager& m_convert;
        winrt::Microsoft::UI::Windowing::AppWindow _appWindow{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar _titleBar{ nullptr };
        winrt::Windows::Storage::StorageFile m_selected_file{ nullptr };
        std::unique_ptr<CSVParser> m_parser; 
        hstring m_selected_delim = L",";
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> m_header_collection{winrt::single_threaded_observable_vector<winrt::hstring>()};
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

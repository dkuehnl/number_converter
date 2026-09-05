#pragma once

#include <memory>
#include "MainWindow.g.h"
#include "csv_parser.h"
#include "json_parser.h"
#include "convertion_manager.h"
#include <winrt/Windows.Foundation.h>


/// @brief Main window: pick a source file, preview its parsed content, and navigate to the per-target-system conversion pages.
namespace winrt::App1::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        /// @brief Handles NavigationView selection changes (switches the displayed page).
        void navView_SelectionChanged(Microsoft::UI::Xaml::Controls::NavigationView const& sender, Microsoft::UI::Xaml::Controls::NavigationViewSelectionChangedEventArgs const& args);

        /// @brief Opens the file picker and, on selection, parses and previews the chosen file.
        fire_and_forget click_file_picker(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

        /// @brief Updates the CSV delimiter used for parsing.
        void cb_delim_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

        /// @brief Updates the header column used to derive filter values.
        void cb_header_chg(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

        /// @brief Shows a titled message in the window's info bar.
        void handle_infobar(const std::string& title, const hstring& message, const std::string& severity); 

        /// @brief Runs ConvertionManager::convert() for the selected header column's values and reports the result.
        winrt::fire_and_forget btn_convert_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args);

        /// @brief Handles edits to the manual/custom-input text box.
        void alt_custom_txt_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private:
        ConvertionManager& m_convert;
        winrt::Microsoft::UI::Windowing::AppWindow _appWindow{ nullptr };
        winrt::Microsoft::UI::Windowing::AppWindowTitleBar _titleBar{ nullptr };
        winrt::Windows::Storage::StorageFile m_selected_file{ nullptr };
        std::unique_ptr<CSVParser> m_parser; 
        hstring m_selected_delim = L",";
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> m_header_collection{winrt::single_threaded_observable_vector<winrt::hstring>()};

        /// @brief Parses m_selected_file (currently .csv only -- see the TODO in the .cpp) and renders a preview.
        winrt::Windows::Foundation::IAsyncAction display_file();
        hstring m_selected_header = L" ";
        hstring m_custom_input = L" ";
    };
}

namespace winrt::App1::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}

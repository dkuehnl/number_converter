#pragma once

#include "SettingsPage.g.h"
#include <json_parser.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <string>

/// @brief Settings page: view/edit the saved per-target-system filter configuration (json_parser).
namespace winrt::App1::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage();

        int32_t MyProperty();
        void MyProperty(int32_t value);

        /// @brief Switches which target system's filters are being edited.
        void ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);

        /// @brief Persists the current filter configuration via json_parser::save().
        void btn_save_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

    private: 
        json_parser& m_parser;
        std::string m_selected_filter;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::hstring> m_header_collection{ winrt::single_threaded_observable_vector<winrt::hstring>() };

        /// @brief Populates the page once its controls are available.
        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::App1::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}

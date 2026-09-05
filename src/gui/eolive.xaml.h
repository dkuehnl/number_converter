#pragma once

#include "eolive.g.h"
#include <json_parser.h>
#include <winrt/Windows.Foundation.h>
#include "convertion_manager.h"

/// @brief eoLive conversion page: search/select values from the parsed source file and build an eoLive "begins" filter.
namespace winrt::App1::implementation
{
    struct eolive : eoliveT<eolive>
    {
        eolive();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        /// @brief Filters the displayed value list as the search text changes.
        void search_field_on_change(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& args);

        /// @brief Toggles between the parsed-file search field and the manual/custom-input field.
        void ts_alt_search_field(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Updates the selected filter type (e.g. "begins").
        void rb_filter_checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Handles selection changes in the value list view.
        void lv_element_selection_SChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
        //void ts_alt_filepath(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        //const hstring& set_direct_output() const;
    private:
        ConvertionManager& m_convert;
        hstring m_search_filter = L" ";
        hstring m_filter_type = L"error";
        bool m_alt_search_field_active = false;


        /// @brief Populates the page's filter presets once its controls are available.
        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Rebuilds the value list view from @p value_vector.
        void build_listview(std::vector<std::string> value_vector);
    };
}

namespace winrt::App1::factory_implementation
{
    struct eolive : eoliveT<eolive, implementation::eolive>
    {
    };
}

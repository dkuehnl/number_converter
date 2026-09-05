#pragma once

#include "smops.g.h"
#include <json_parser.h>
#include <winrt/Windows.Foundation.h>
#include "convertion_manager.h"

/// @brief SMOPS conversion page: search/select values from the parsed source file and build a SMOPS bool-query filter.
namespace winrt::App1::implementation
{
    struct smops : smopsT<smops>
    {
        smops();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        /// @brief Filters the displayed value tree as the search text changes.
        void search_field_on_change(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& args);

        /// @brief Toggles between the parsed-file search field and the manual/custom-input field.
        void ts_alt_search_field(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Updates the selected filter type (e.g. "is one of"/"is not one of").
        void rb_one_of_checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Handles selection changes in the value tree view.
        void tv_element_selection_SChanged(winrt::Microsoft::UI::Xaml::Controls::TreeView const& sender, winrt::Microsoft::UI::Xaml::Controls::TreeViewSelectionChangedEventArgs const& args);
        //void ts_alt_filepath(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        //const hstring& set_direct_output() const;
    private:
        ConvertionManager& m_convert;
        hstring m_search_filter = L" ";
        hstring m_filter_type = L"error"; 
        bool m_alt_search_field_active = false; 
 

        /// @brief Populates the page's filter presets once its controls are available.
        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        /// @brief Rebuilds the value tree view from @p value_map (grouped by key, e.g. SMOPS category).
        void build_treeview(std::unordered_map<std::string, std::vector<std::string>> value_map);
    };
}

namespace winrt::App1::factory_implementation
{
    struct smops : smopsT<smops, implementation::smops>
    {
    };
}

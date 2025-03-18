#pragma once

#include "smops.g.h"
#include <json_parser.h>
#include <winrt/Windows.Foundation.h>

namespace winrt::App1::implementation
{
    struct smops : smopsT<smops>
    {
        smops();
        int32_t MyProperty();
        void MyProperty(int32_t value);

        void search_field_on_change(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& args);
        void ts_alt_search_field(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void rb_one_of_checked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void tv_element_selection_SChanged(winrt::Microsoft::UI::Xaml::Controls::TreeView const& sender, winrt::Microsoft::UI::Xaml::Controls::TreeViewSelectionChangedEventArgs const& args);
        //void ts_alt_filepath(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);


        const hstring& get_filter_type() const;
        const hstring& get_search_filter() const;
        //const hstring& set_direct_output() const;
    private:
        std::shared_ptr<json_parser> m_json_parser;
        hstring m_search_filter = L" ";
        hstring m_alt_search_filter = L" ";
        hstring m_one_of = L"error"; 
        bool m_alt_search_field_active = false; 
 

        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void build_treeview(std::unordered_map<std::string, std::vector<std::string>> value_map);
    };
}

namespace winrt::App1::factory_implementation
{
    struct smops : smopsT<smops, implementation::smops>
    {
    };
}

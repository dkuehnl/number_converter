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
        void OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        //std::vector<hstring> get_filter_options(); 

        void btn_test_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e); 
        
    private:
        std::shared_ptr<json_parser> m_json_parser;
        hstring get_filter_type(); 
        hstring get_search_filter(); 
        hstring get_alternativ_export_path();
        void build_treeview(std::unordered_map<std::string, std::vector<std::string>> value_map);
        

        //void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::App1::factory_implementation
{
    struct smops : smopsT<smops, implementation::smops>
    {
    };
}

#include "pch.h"
#include "smops.xaml.h"
#if __has_include("smops.g.cpp")
#include "smops.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/base.h>
#include "App.xaml.h" 
#include "unordered_map"


using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    int32_t smops::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void smops::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    smops::smops() {
        InitializeComponent(); 
        this->Loaded({ this, &smops::OnLoaded });
    }

    void smops::OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        //for (const auto& [key, value] : json_parser::get_smops_filter())
        json_parser& parser = App::GetJsonParser();
        std::unordered_map<std::string, std::vector<std::string>> smops_filter = parser.get_smops_filter();
        smops::build_treeview(smops_filter); 
         
    }
    
    hstring smops::get_filter_type() {
        if (one_of_button().IsChecked().GetBoolean()) {
            return L"is one of";
        }
        else if (not_one_of_button().IsChecked().GetBoolean()) {
            return L"is not one of"; 
        }
        else {
            return L"error";
        }
    }
    
    hstring smops::get_search_filter() {
        return L" ";
    }

    hstring smops::get_alternativ_export_path() {
        return L" ";
    }

    void smops::btn_test_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        OutputDebugString(L"Button funktioniert\n"); 
        smops::get_filter_type();
    }

    void smops::build_treeview(std::unordered_map<std::string, std::vector<std::string>> value_map) {
        for (const auto& [key, value] : value_map){
            TreeViewNode root_node = TreeViewNode(); 
            root_node.Content(box_value(winrt::to_hstring(key)));

            for (const auto& element : value) {
                TreeViewNode child_node = TreeViewNode(); 
                child_node.Content(box_value(winrt::to_hstring(element))); 
                root_node.Children().Append(child_node); 
            }

            tv_element_selection().RootNodes().Append(root_node);
        }
    }

}

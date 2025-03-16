#include "pch.h"
#include "smops.xaml.h"
#if __has_include("smops.g.cpp")
#include "smops.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

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
        OutputDebugString(L"Test-Output after loading smops-page");
         
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

}

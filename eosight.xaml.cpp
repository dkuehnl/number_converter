#include "pch.h"
#include "eosight.xaml.h"
#if __has_include("eosight.g.cpp")
#include "eosight.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    int32_t eosight::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void eosight::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void eosight::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}

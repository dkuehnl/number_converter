#include "pch.h"
#include "smops.xaml.h"
#if __has_include("smops.g.cpp")
#include "smops.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>

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

    /*void smops::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }*/
}

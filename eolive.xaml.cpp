#include "pch.h"
#include "eolive.xaml.h"
#if __has_include("eolive.g.cpp")
#include "eolive.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    int32_t eolive::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void eolive::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void eolive::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}

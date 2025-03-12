#pragma once

#include "eolive.g.h"

namespace winrt::App1::implementation
{
    struct eolive : eoliveT<eolive>
    {
        eolive()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::App1::factory_implementation
{
    struct eolive : eoliveT<eolive, implementation::eolive>
    {
    };
}

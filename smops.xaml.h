#pragma once

#include "smops.g.h"

namespace winrt::App1::implementation
{
    struct smops : smopsT<smops>
    {
        smops()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);

        //void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
    };
}

namespace winrt::App1::factory_implementation
{
    struct smops : smopsT<smops, implementation::smops>
    {
    };
}

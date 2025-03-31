#pragma once

#include "SettingsPage.g.h"

namespace winrt::App1::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
        SettingsPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::App1::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}

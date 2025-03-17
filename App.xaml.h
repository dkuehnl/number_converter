#pragma once

#include "App.xaml.g.h"
#include "json_parser.h"

namespace winrt::App1::implementation
{
    struct App : AppT<App>
    {
        App();
        static json_parser& GetJsonParser();
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        static json_parser m_json_parser;
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

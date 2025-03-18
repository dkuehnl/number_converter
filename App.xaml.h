#pragma once

#include "App.xaml.g.h"
#include "json_parser.h"
#include "convertion_manager.h"

namespace winrt::App1::implementation
{
    struct App : AppT<App>
    {
        App();
        static json_parser& GetJsonParser();
        static convertion_manager& GetConvertionManager(); 
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        static convertion_manager m_convertion_manager; 
        static json_parser m_json_parser;
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

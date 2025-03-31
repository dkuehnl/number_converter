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
        static ConvertionManager& GetConvertionManager();
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        static ConvertionManager m_convertion_manager;
        static json_parser m_json_parser;
        std::string m_json_file_url; 
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

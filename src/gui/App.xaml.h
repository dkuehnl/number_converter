#pragma once

#include "App.xaml.g.h"
#include "json_parser.h"
#include "convertion_manager.h"

/// @brief Application entry point; owns the process-wide json_parser and ConvertionManager singletons and shows MainWindow.
namespace winrt::App1::implementation
{
    struct App : AppT<App>
    {
        App();

        /// @return The process-wide filter-configuration parser (see json_parser).
        static json_parser& GetJsonParser();

        /// @return The process-wide conversion manager (see ConvertionManager).
        static ConvertionManager& GetConvertionManager();

        /// @brief Creates and activates MainWindow.
        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        static ConvertionManager m_convertion_manager;
        static json_parser m_json_parser;
        // TODO: m_json_file_url is never read anywhere (m_json_parser in the
        // .cpp is constructed from its own separate hardcoded string
        // literal) -- this is dead code carrying a second, independently
        // stale copy of the same machine-specific path. Remove it, or wire
        // it up as the actual single source of truth once the path is fixed
        // (see the TODO in App.xaml.cpp).
        std::string m_json_file_url = "A:\\Workspace\\Programming\\cpp\\number_converter\\testing-space\\smops_values.json";
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}

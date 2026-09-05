#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    // TODO: This is hardcoded to an absolute, machine-specific path (and the
    // commented-out line above it is a *different* machine-specific path from
    // an earlier setup) -- the app currently only finds its filter
    // configuration if smops_values.json happens to exist at this exact
    // location on this exact machine, and it depends on testing-space/ (a
    // dev scratch folder) being present as if it were production data. This
    // should become a relative/deployed path (e.g. next to the executable,
    // or under a proper Windows ApplicationData folder) instead.
    //json_parser App::m_json_parser{ "C:\\Users\\dkueh\\source\\repos\\dkuehnl\\number_converter\\testing-space\\smops_values.json" }; //Laptop-IDE
    json_parser App::m_json_parser{ "A:\\Workspace\\Programming\\cpp\\number_converter\\testing-space\\smops_values.json" };
    ConvertionManager App::m_convertion_manager;
    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    App::App()
    {
        // Xaml objects should not call InitializeComponent during construction.
        // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();
                __debugbreak();
            }
        });
#endif
    }

    /// <summary>
    /// Invoked when the application is launched.
    /// </summary>
    /// <param name="e">Details about the launch request and process.</param>
    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        window = make<MainWindow>();
        window.Activate();
    }

    json_parser& App::GetJsonParser()
    {
        return m_json_parser;
    }

    ConvertionManager& App::GetConvertionManager() {
        return m_convertion_manager; 
    }
}

#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif

#include "App.xaml.h" 
#include "json_parser.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    int32_t SettingsPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void SettingsPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    SettingsPage::SettingsPage() : m_parser(App::GetJsonParser()) {
        this->Loaded({ this, &SettingsPage::OnLoaded });
    }

    void SettingsPage::OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        nmb_preview_lines().Value(m_parser.get_preview_lines());
    }

}

void winrt::App1::implementation::SettingsPage::auto_main_categorie_GotFocus(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    if (auto box = sender.try_as<winrt::Microsoft::UI::Xaml::Controls::AutoSuggestBox>()) {
        auto item_list = winrt::single_threaded_vector<winrt::Windows::Foundation::IInspectable>(); 

        for (const auto& [key, value] : m_parser.get_smops_filter()) {
            //OutputDebugStringA(key.c_str());
            item_list.Append(winrt::box_value(winrt::to_hstring(key)));
        }

        if (item_list.Size() > 0) {
            OutputDebugString(L"If-Zweig");
            box.ItemsSource(item_list);
        }
        else {
            box.ItemsSource(nullptr); 
        }
        
     }
}

void winrt::App1::implementation::SettingsPage::ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    if (auto com_box = sender.try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>()) {
        if (auto com_box_item = com_box.SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>()) {
            m_selected_filter = winrt::to_string(com_box_item.Content().as<hstring>()); 
        }
    }

    if (m_selected_filter == "SMOPS") {
        auto_main_categorie().IsEnabled(true); 
    }
    else {
        auto_main_categorie().IsEnabled(false); 
    }
}

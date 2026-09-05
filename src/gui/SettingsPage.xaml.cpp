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

void winrt::App1::implementation::SettingsPage::ComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
    if (auto com_box = sender.try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBox>()) {
        if (auto com_box_item = com_box.SelectedItem().try_as<winrt::Microsoft::UI::Xaml::Controls::ComboBoxItem>()) {
            m_selected_filter = winrt::to_string(com_box_item.Content().as<hstring>()); 
        }
    }

    if (m_selected_filter == "SMOPS") {
        cb_main_categorie().IsEnabled(true); 
        for (const auto& [key, value] : m_parser.get_smops_filter()) {
            m_header_collection.Append(winrt::to_hstring(key));
        }
        cb_main_categorie().ItemsSource(m_header_collection);
        cb_main_categorie().SelectedIndex(0); 
    }
    else {
        cb_main_categorie().IsEnabled(false); 
    }
}

void winrt::App1::implementation::SettingsPage::btn_save_click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    m_parser.update_preview_lines(static_cast<unsigned int>(nmb_preview_lines().Value()));

    auto content = tb_new_value().Text(); 
    if (!content.empty()) {
        std::string new_value = winrt::to_string(content);
        if (m_selected_filter == "SMOPS") {
            auto selected_item = cb_main_categorie().SelectedItem();
            if (selected_item) {
                std::string selected_key = winrt::to_string(selected_item.as<winrt::hstring>());

                m_parser.add_smops_filter(selected_key, new_value);
            }
        }
        else if (m_selected_filter == "eoLive") {
            m_parser.add_eolive_filter(new_value);
        }
        else if (m_selected_filter == "eoSight") {
            m_parser.add_eosight_filter(new_value);
        }
        else {

        }
    }

    m_parser.save(); 
}

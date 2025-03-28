#include "pch.h"
#include "eosight.xaml.h"
#if __has_include("eosight.g.cpp")
#include "eosight.g.cpp"
#endif
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/base.h>
#include "App.xaml.h" 
#include "unordered_map"
#include "convertion_manager.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::App1::implementation
{
    int32_t eosight::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void eosight::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    eosight::eosight() : m_convert(App::GetConvertionManager()) {
        InitializeComponent();
        this->Loaded({ this, &eosight::OnLoaded });
        tb_alt_search_field().TextChanged({ this, &eosight::search_field_on_change });
    }

    void eosight::OnLoaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        json_parser& parser = App::GetJsonParser();
        std::vector<std::string> smops_filter = parser.get_eosight_filter();
        eosight::build_listview(smops_filter);

        m_convert.register_page("eoSight");
    }

    void eosight::build_listview(std::vector<std::string> value_vector) {
        Windows::Foundation::Collections::IObservableVector<hstring> items = winrt::single_threaded_observable_vector<hstring>();
        for (const auto& element : value_vector) {
            items.Append(winrt::to_hstring(element));
        }
        lv_element_selection().ItemsSource(items);
    }

    void eosight::lv_element_selection_SChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
        if (!m_alt_search_field_active) {
            for (auto const& item : e.AddedItems()) {
                auto text = winrt::unbox_value<winrt::hstring>(item);
                m_search_filter = text;
                m_convert.set_filter_value(winrt::to_string(m_search_filter));
            }
        }
    }

    void eosight::rb_filter_kind(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        if (contains().IsChecked().GetBoolean()) {
            m_filter_type = L"is one of";
        }
        else if (equal().IsChecked().GetBoolean()) {
            m_filter_type = L"is not one of";
        }
        else {
            m_filter_type = L"error";
        }
        m_convert.set_filter_type(winrt::to_string(m_filter_type));
    }

    //void smops::ts_alt_filepath(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
    //    auto toggle = sender.as<winrt::Microsoft::UI::Xaml::Controls::ToggleSwitch>(); 
    //    bool is_active = toggle.IsOn(); 
    //    if (is_active) {
    //        m_alt_filtepath_active = true; 
    //        reb_alt_file_path().IsEnabled(true); 
    //    }
    //    else {
    //        m_alt_filtepath_active = false;
    //        reb_alt_file_path().IsEnabled(false); 
    //    }
    //}

    void eosight::ts_alt_search_field(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        auto toggle = sender.as<winrt::Microsoft::UI::Xaml::Controls::ToggleSwitch>();
        bool is_active = toggle.IsOn();
        if (is_active) {
            m_alt_search_field_active = true;
            tb_alt_search_field().IsEnabled(true);
        }
        else {
            m_alt_search_field_active = false;
            tb_alt_search_field().IsEnabled(false);
        }
    }

    void eosight::search_field_on_change(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& args) {
        auto text_box = sender.as<winrt::Microsoft::UI::Xaml::Controls::TextBox>();
        m_search_filter = text_box.Text();
        m_convert.set_filter_value(winrt::to_string(m_search_filter));
    }
}
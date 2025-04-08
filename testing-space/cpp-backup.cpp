for (int i = 0; i < 4; i++) {
    auto run = winrt::Microsoft::UI::Xaml::Documents::Run(); 
    if (i == 0) {
        run.Text(winrt::to_hstring(m_csv_parser.test_get_firstline(i)) + L"\n");
        auto bold = winrt::Microsoft::UI::Xaml::Documents::Bold(); 
        bold.Inlines().Append(run);
        data_output().Inlines().Append(bold); 
    }
    else {
        run.Text(winrt::to_hstring(m_csv_parser.test_get_firstline(i)) + L"\n");
        data_output().Inlines().Append(run);
    }
}
#pragma once

// TODO: Not implemented yet. The file picker (FileHandler::pick_file())
// accepts .csv/.xls/.xlsx, but MainWindow::display_file() only handles
// .csv (parsed via CSVParser) and .xls (shows a "not implemented yet"
// info bar). Picking a .xlsx file currently falls through both checks
// silently -- see the TODO in MainWindow::display_file().
class XLSXparser
{
};

# Number-Converter

A Windows desktop tool that turns a list of values from a CSV/Excel file (or pasted manually) into ready-to-use filter expressions for SMOPS, eoLive, and eoSight.

> **Status: under active development.** Core CSV-based conversion works for all three target systems; `.xlsx`/`.xls` parsing and a few edge cases are still open — see the `// TODO:` comments throughout `src/` for the current state.

---

## Why Number-Converter?

Building an "is one of these 40 values" filter by hand for a query language is tedious and error-prone, especially when the same list of values needs to become a filter for more than one target system with different query syntax. Number-Converter takes a source file (or pasted text), lets you pick which column/values to filter on, and generates the correctly-formatted expression for the target system you need — SMOPS' Elasticsearch-style bool query, eoLive's `begins (...)` syntax, or eoSight's `CONTAINS()`/equality expressions.

---

## Features

- **CSV import** — pick a `.csv` file, choose the delimiter and header column, and preview the parsed table
- **Manual input** — paste values directly instead of loading a file
- **Per-target-system conversion** — SMOPS, eoLive, and eoSight each get their own page and matching filter syntax
- **Saved filter presets** — frequently-used filter columns/values are stored in a JSON config file and editable from the Settings page
- **Output written next to the source file** — the generated filter expression is saved as a new `.txt` file alongside the input

---

## Architecture

| Component | Responsibility |
|---|---|
| `App` | Application entry point; owns the shared `json_parser`/`ConvertionManager` instances |
| `MainWindow` | Loads/previews the source file and hosts navigation to the conversion pages |
| `SettingsPage`, `eolive`, `eosight`, `smops` | Per-target-system pages for selecting/searching values and triggering conversion |
| `CSVParser` | Parses a delimited file into headers and rows |
| `ConvertionManager` | Builds the target-system-specific filter expression and writes it to file |
| `FileHandler` | File picking and file-writing helpers |
| `json_parser` | Loads/saves the saved filter presets (`smops`/`eolive`/`eosight`/`preview_lines`) |
| `CustomInputParser` | Splits manually pasted multi-line input into values |
| `XLSXparser` | Not implemented yet — reserved for `.xlsx`/`.xls` support |

---

## Requirements

| Dependency | Notes |
|---|---|
| C++ | 17 |
| Visual Studio | 2022, with the Windows App SDK / WinUI3 workload |
| Windows App SDK | via NuGet (`Microsoft.WindowsAppSDK`, `Microsoft.Windows.CppWinRT`) |
| nlohmann/json | via NuGet (`nlohmann.json`) |

Target platform: **Windows only** (WinUI3 / C++/WinRT, packaged as MSIX).

---

## Usage

Open the app and use the file picker to load a `.csv` file (or switch to manual input to paste values directly). Pick the delimiter and header column to preview the parsed data, then switch to the SMOPS, eoLive, or eoSight page to search/select the values you want to filter on and set the filter type. Converting writes the generated filter expression to a new `.txt` file next to the source file. Use the Settings page to manage saved filter presets per target system.

---

## Project Structure

```
src/
  core/        # CSVParser, ConvertionManager, FileHandler, json_parser, CustomInputParser, XLSXparser — business logic, no XAML dependency
  gui/         # App, MainWindow, SettingsPage, eolive, eosight, smops — WinUI3 pages and their .idl definitions
```

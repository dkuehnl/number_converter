#pragma once

/// @brief Parsing for manually-typed/pasted multi-line input (as an alternative to loading a CSV file).
namespace CustomInputParser
{
	/// @brief Splits @p input into non-empty lines.
	/// @param input Raw multi-line text (e.g. pasted by the user).
	/// @return One entry per non-empty line, in order.
	std::vector<std::string> parse_custom_input(winrt::hstring input);
};

#pragma once

#include <string>

/// <summary>
/// Rodzaje mo¿liwych do utworzenia przycisków.
/// </summary>
enum class ButtonType
{
	NEW_GAME, SCORES, OPTIONS, EXIT
};

/// <summary>
/// Konwersja rodzaju przycisku na jego reprezentacjê w postaci stringu.
/// </summary>
/// <param name="bt">Typ przycisku.</param>
/// <returns>Rodzaj przycisku w formie stringu, jeœli nie istnieje, to zwraca nullptr</returns>
static std::string ButtonToString(ButtonType bt)
{
	switch(bt)
	{
	case ButtonType::NEW_GAME:
		return "NewGame";
	case ButtonType::SCORES:
		return "Scores";
	case ButtonType::OPTIONS:
		return "Options";
	case ButtonType::EXIT:
		return "Exit";
	default:
		return nullptr;
	}
};
#pragma once

#include <string>

enum class ButtonType
{
	NEW_GAME, SCORES, OPTIONS, EXIT
};

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
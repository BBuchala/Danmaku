#ifndef _BONUS_TYPE_
#define _BONUS_TYPE_

/// <summary>
/// Rodzaje mo¿liwych do utworzenia bonusów.
/// </summary>
static enum class BonusType
{
	NONE	= 0x00,
	BOMB	= 0x01,
	LIFE	= 0x02,
	POWER	= 0x04,
	SCORE	= 0x08
};

/// <summary>
/// Konwersja rodzaju bonusu na jego reprezentacjê w postaci stringu.
/// </summary>
/// <param name="bt">Typ bonusu.</param>
/// <returns></returns>
static const char * BonusToString(BonusType bt)
{
	switch(bt)
	{
	case BonusType::BOMB:
		return "bonusBomb";
	case BonusType::LIFE:
		return "bonusLife";
	case BonusType::POWER:
		return "bonusPower";
	case BonusType::SCORE:
		return "bonusScore";
	default:
		return nullptr;
	}
};

#endif
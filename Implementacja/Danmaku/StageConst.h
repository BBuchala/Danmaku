#pragma once

namespace StageConst
{
	static struct StageConsts
	{
		//// ==== STA£E
		static const unsigned short BUTTON_NUM		= 2;
		static const unsigned short TEX_NUM		= 3;
		static const unsigned short STAGE_POS_X	= 63;
		static const unsigned short STAGE_POS_Y	= 32;
		static const unsigned short STAGE_WIDTH	= 614;
		static const unsigned short STAGE_HEIGHT	= 706;
		static const unsigned short SCORE_PADDING	= 10;
		static const unsigned short GRAZE_DISTANCE	= 10;
		// wci¹ganie bonusów na 1/5 wysokoœci od góry
		static const unsigned short BONUS_VACUUM_Y	= static_cast<short>((STAGE_POS_Y + STAGE_HEIGHT) * 1.0f / 5.0f);
		static const unsigned short AVATAR_NUMBER	= 4;
		static const unsigned short GAME_POS_X		= 0;
		static const unsigned short GAME_POS_Y		= 0;
		static const unsigned short GAME_WIDTH		= 1024;
		static const unsigned short GAME_HEIGHT	= 768;
	} Consts;

}
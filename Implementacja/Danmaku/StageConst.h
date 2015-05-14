namespace StageConst
{
	static struct StageConsts
	{
		//// ==== STA£E
	static const unsigned short BUTTON_NUM		= 2;
	static const unsigned short TEX_NUM			= 3;
	static const unsigned short STAGE_POS_X		= 63;
	static const unsigned short STAGE_POS_Y		= 32;
	static const unsigned short STAGE_WIDTH		= 614;
	static const unsigned short STAGE_HEIGHT	= 706;
	static const unsigned short SCORE_PADDING	= 10;
	static const unsigned short GRAZE_DISTANCE	= 5;
	// wci¹ganie bonusów na 1/5 wysokoœci od góry
	static const unsigned short BONUS_VACUUM_Y	= static_cast<short>((STAGE_POS_Y + STAGE_HEIGHT) * 1.0f / 5.0f);
	} Consts;

}
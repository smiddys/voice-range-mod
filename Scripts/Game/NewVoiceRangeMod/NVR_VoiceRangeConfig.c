class NVR_VoiceRangeConfig
{
	static const int RANGE_COUNT = 3;
	static const int DEFAULT_RANGE_INDEX = 1;

	static const string ACTION_INCREASE = "NVRVoiceRangeIncrease";
	static const string ACTION_DECREASE = "NVRVoiceRangeDecrease";
	static const string ACTION_TOGGLE_HUD = "NVRVoiceRangeToggleHUD";

	static const string ACTION_INCREASE_OLD = "NVR_IncreaseVoiceRange";
	static const string ACTION_DECREASE_OLD = "NVR_DecreaseVoiceRange";
	static const string ACTION_TOGGLE_HUD_OLD = "NVR_ToggleVoiceRangeHud";

	static const string LOG_PREFIX = "[NEW VOICE RANGE MOD]";

	static int GetRangeMeters(int index)
	{
		if (index <= 0)
			return 5;

		if (index == 1)
			return 30;

		return 60;
	}

	static string GetRangeLabel(int index)
	{
		return string.Format("%1m", GetRangeMeters(index));
	}

	static int ClampRangeIndex(int index)
	{
		if (index < 0)
			return 0;

		if (index >= RANGE_COUNT)
			return RANGE_COUNT - 1;

		return index;
	}
}

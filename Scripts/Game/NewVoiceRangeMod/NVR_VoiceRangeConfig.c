class NVR_VoiceRangeConfig
{
	static const int RANGE_COUNT = 5;
	static const int DEFAULT_RANGE_INDEX = 2;

	static const string ACTION_INCREASE = "NVRVoiceRangeIncrease";
	static const string ACTION_DECREASE = "NVRVoiceRangeDecrease";
	static const string ACTION_TOGGLE_HUD = "NVRVoiceRangeToggleHUD";

	static const string ACTION_INCREASE_OLD = "NVR_IncreaseVoiceRange";
	static const string ACTION_DECREASE_OLD = "NVR_DecreaseVoiceRange";
	static const string ACTION_TOGGLE_HUD_OLD = "NVR_ToggleVoiceRangeHud";

	static const string LOG_PREFIX = "[NEW VOICE RANGE MOD]";
	static const string AUDIO_SIGNAL_RANGE_METERS = "VRM_VonRangeMeters";
	static const string AUDIO_SIGNAL_WCS_RANGE = "WCS_VonRange";
	static const string AUDIO_SIGNAL_VON_AMPLITUDE = "VONAmplitude";

	static int GetRangeMeters(int index)
	{
		if (index <= 0)
			return 5;

		if (index == 1)
			return 15;

		if (index == 2)
			return 30;

		if (index == 3)
			return 45;

		return 60;
	}

	static string GetRangeLabel(int index)
	{
		return string.Format("%1m", GetRangeMeters(index));
	}

	static float GetWCSRangeValue(int index)
	{
		if (index <= 0)
			return 1.0;

		if (index == 1)
			return 1.5;

		if (index == 2)
			return 2.0;

		if (index == 3)
			return 2.5;

		return 3.0;
	}

	static float GetVONAmplitudeValue(int index)
	{
		return GetRangeMeters(index) / 60.0;
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

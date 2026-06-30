class VRM_VoiceRangeConfig
{
	static const int RANGE_COUNT = 5;
	static const float RANGE_WHISPER_METERS = 5.0;
	static const float RANGE_LOW_METERS = 15.0;
	static const float RANGE_NORMAL_METERS = 30.0;
	static const float RANGE_RAISED_METERS = 45.0;
	static const float RANGE_SHOUT_METERS = 60.0;
	static const bool DEBUG_LOGGING = true;

	static float GetRangeMeters(int rangeIndex)
	{
		switch (rangeIndex)
		{
			case 0:
				return RANGE_WHISPER_METERS;
			case 1:
				return RANGE_LOW_METERS;
			case 2:
				return RANGE_NORMAL_METERS;
			case 3:
				return RANGE_RAISED_METERS;
			case 4:
				return RANGE_SHOUT_METERS;
		}

		return RANGE_NORMAL_METERS;
	}

	static string GetRangeLabel(int rangeIndex)
	{
		switch (rangeIndex)
		{
			case 0:
				return "5 m";
			case 1:
				return "15 m";
			case 2:
				return "30 m";
			case 3:
				return "45 m";
			case 4:
				return "60 m";
		}

		return "30 m";
	}

	static string GetCompactRangeLabel(int rangeIndex)
	{
		switch (rangeIndex)
		{
			case 0:
				return "5m";
			case 1:
				return "15m";
			case 2:
				return "30m";
			case 3:
				return "45m";
			case 4:
				return "60m";
		}

		return "30m";
	}
}

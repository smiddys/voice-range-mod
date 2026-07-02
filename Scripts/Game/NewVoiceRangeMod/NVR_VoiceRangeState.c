class NVR_VoiceRangeState
{
	protected static int s_iLocalRangeIndex = NVR_VoiceRangeConfig.DEFAULT_RANGE_INDEX;
	protected static ref map<int, int> s_mPlayerRanges = new map<int, int>();

	static int GetLocalRangeIndex()
	{
		return s_iLocalRangeIndex;
	}

	static int GetLocalRangeMeters()
	{
		return NVR_VoiceRangeConfig.GetRangeMeters(s_iLocalRangeIndex);
	}

	static string GetLocalRangeLabel()
	{
		return NVR_VoiceRangeConfig.GetRangeLabel(s_iLocalRangeIndex);
	}

	static void SetLocalRangeIndex(int index)
	{
		s_iLocalRangeIndex = NVR_VoiceRangeConfig.ClampRangeIndex(index);
	}

	static void StepLocalRange(int direction)
	{
		int nextIndex = s_iLocalRangeIndex + direction;

		if (nextIndex < 0)
			nextIndex = NVR_VoiceRangeConfig.RANGE_COUNT - 1;

		if (nextIndex >= NVR_VoiceRangeConfig.RANGE_COUNT)
			nextIndex = 0;

		SetLocalRangeIndex(nextIndex);
	}

	static void SetPlayerRangeIndex(int playerId, int index)
	{
		if (playerId <= 0)
			return;

		s_mPlayerRanges.Set(playerId, NVR_VoiceRangeConfig.ClampRangeIndex(index));
	}

	static int GetPlayerRangeMeters(int playerId)
	{
		int index;
		if (!s_mPlayerRanges.Find(playerId, index))
			index = NVR_VoiceRangeConfig.DEFAULT_RANGE_INDEX;

		return NVR_VoiceRangeConfig.GetRangeMeters(index);
	}
}

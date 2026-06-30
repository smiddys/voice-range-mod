class VRM_VoiceRangeManager
{
	protected static int s_iSelectedRangeIndex = 2;
	protected static bool s_bIndicatorVisible = true;
	protected static bool s_bDirectVoiceActive;
	protected static ref array<int> s_aPlayerIds = {};
	protected static ref array<int> s_aPlayerRangeIndexes = {};

	static int GetSelectedRangeIndex()
	{
		return s_iSelectedRangeIndex;
	}

	static float GetSelectedRangeMeters()
	{
		return VRM_VoiceRangeConfig.GetRangeMeters(s_iSelectedRangeIndex);
	}

	static string GetSelectedRangeLabel()
	{
		return VRM_VoiceRangeConfig.GetRangeLabel(s_iSelectedRangeIndex);
	}

	static string GetSelectedCompactRangeLabel()
	{
		return VRM_VoiceRangeConfig.GetCompactRangeLabel(s_iSelectedRangeIndex);
	}

	static bool IsIndicatorVisible()
	{
		return s_bIndicatorVisible;
	}

	static void SetDirectVoiceActive(bool active)
	{
		s_bDirectVoiceActive = active;
	}

	static bool IsDirectVoiceActive()
	{
		return s_bDirectVoiceActive;
	}

	static void SetSelectedRangeIndex(int rangeIndex)
	{
		if (rangeIndex < 0)
			rangeIndex = 0;

		if (rangeIndex >= VRM_VoiceRangeConfig.RANGE_COUNT)
			rangeIndex = VRM_VoiceRangeConfig.RANGE_COUNT - 1;

		s_iSelectedRangeIndex = rangeIndex;
		SetLocalPlayerRangeIndex(rangeIndex);
		ApplySelectedRange();
	}

	static void CycleSelectedRange()
	{
		s_iSelectedRangeIndex++;

		if (s_iSelectedRangeIndex >= VRM_VoiceRangeConfig.RANGE_COUNT)
			s_iSelectedRangeIndex = 0;

		SetLocalPlayerRangeIndex(s_iSelectedRangeIndex);
		ApplySelectedRange();
	}

	static void IncreaseSelectedRange()
	{
		SetSelectedRangeIndex(s_iSelectedRangeIndex + 1);
	}

	static void DecreaseSelectedRange()
	{
		SetSelectedRangeIndex(s_iSelectedRangeIndex - 1);
	}

	static void ToggleIndicator()
	{
		s_bIndicatorVisible = !s_bIndicatorVisible;

		if (s_bIndicatorVisible)
		{
			ShowIndicator();
			return;
		}

		if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
			Print("[VoiceRangeMod] Voice range indicator hidden.");
	}

	static void ApplySelectedRange()
	{
		if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
			Print(string.Format("[VoiceRangeMod] Selected proximity VOIP range: %1", GetSelectedRangeLabel()));

		ShowIndicator();

		// The actual range enforcement is receiver-side in SCR_VoNComponent.OnReceive.
		// This must not use radio transceiver range.
	}

	static void ShowIndicator()
	{
		if (!VRM_VoiceRangeConfig.DEBUG_LOGGING || !s_bIndicatorVisible)
			return;

		Print(string.Format("[VoiceRangeMod] Voice range indicator: %1", GetSelectedRangeLabel()));
	}

	static void SetLocalPlayerRangeIndex(int rangeIndex)
	{
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;

		SetPlayerRangeIndex(playerController.GetPlayerId(), rangeIndex);
	}

	static void SetPlayerRangeIndex(int playerId, int rangeIndex)
	{
		if (rangeIndex < 0)
			rangeIndex = 0;

		if (rangeIndex >= VRM_VoiceRangeConfig.RANGE_COUNT)
			rangeIndex = VRM_VoiceRangeConfig.RANGE_COUNT - 1;

		int index = s_aPlayerIds.Find(playerId);
		if (index == -1)
		{
			s_aPlayerIds.Insert(playerId);
			s_aPlayerRangeIndexes.Insert(rangeIndex);
		}
		else
		{
			s_aPlayerRangeIndexes[index] = rangeIndex;
		}
	}

	static int GetPlayerRangeIndex(int playerId)
	{
		int index = s_aPlayerIds.Find(playerId);
		if (index == -1)
			return 2;

		return s_aPlayerRangeIndexes[index];
	}

	static float GetPlayerRangeMeters(int playerId)
	{
		return VRM_VoiceRangeConfig.GetRangeMeters(GetPlayerRangeIndex(playerId));
	}

	static bool IsManagedPlayer(int playerId)
	{
		return s_aPlayerIds.Find(playerId) != -1;
	}

	static bool ShouldReceiveDirectVoice(int senderPlayerId)
	{
		if (!IsManagedPlayer(senderPlayerId))
			return true;

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return true;

		IEntity sender = playerManager.GetPlayerControlledEntity(senderPlayerId);
		PlayerController localController = GetGame().GetPlayerController();
		if (!sender || !localController)
			return true;

		IEntity listener = localController.GetControlledEntity();
		if (!listener)
			return true;

		float rangeMeters = GetPlayerRangeMeters(senderPlayerId);
		float distanceSq = vector.DistanceSq(sender.GetOrigin(), listener.GetOrigin());

		return distanceSq <= rangeMeters * rangeMeters;
	}

	static void LogActiveVoiceEntry(SCR_VONEntry entry)
	{
		if (!VRM_VoiceRangeConfig.DEBUG_LOGGING)
			return;

		if (!entry)
		{
			Print("[VoiceRangeMod] No active voice entry.");
			return;
		}

		Print(string.Format("[VoiceRangeMod] Active VON method: %1", entry.GetVONMethod()));
		Print(string.Format("[VoiceRangeMod] Selected proximity VOIP range: %1", GetSelectedRangeLabel()));
	}
}

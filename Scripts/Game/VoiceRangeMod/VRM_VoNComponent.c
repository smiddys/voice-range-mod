modded class SCR_VoNComponent
{
	override protected void OnReceive(int playerId, bool isSenderEditor, BaseTransceiver receiver, int frequency, float quality)
	{
		if (!receiver && !VRM_VoiceRangeManager.ShouldReceiveDirectVoice(playerId))
		{
			if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
			{
				Print(string.Format(
					"[VoiceRangeMod] Blocked direct proximity VOIP from player %1 outside %2 m",
					playerId,
					VRM_VoiceRangeManager.GetPlayerRangeMeters(playerId)
				));
			}

			return;
		}

		super.OnReceive(playerId, isSenderEditor, receiver, frequency, quality);
	}
}

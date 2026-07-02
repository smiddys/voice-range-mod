modded class SCR_VoNComponent
{
	override protected void OnReceive(int playerId, bool isSenderEditor, BaseTransceiver receiver, int frequency, float quality)
	{
		if (NVR_CanReceiveDirectVoice(playerId, receiver))
		{
			super.OnReceive(playerId, isSenderEditor, receiver, frequency, quality);
			return;
		}

		Print(string.Format("%1 blocked direct voice from player %2 outside selected range.", NVR_VoiceRangeConfig.LOG_PREFIX, playerId));
	}

	protected bool NVR_CanReceiveDirectVoice(int playerId, BaseTransceiver receiver)
	{
		PlayerController localController = GetGame().GetPlayerController();
		if (!localController)
			return true;

		IEntity listener = localController.GetControlledEntity();
		if (!listener)
			return true;

		PlayerManager playerManager = GetGame().GetPlayerManager();
		if (!playerManager)
			return true;

		IEntity speaker = playerManager.GetPlayerControlledEntity(playerId);
		if (!speaker)
			return true;

		NVR_VoiceRangeRepComponent rangeComponent = NVR_VoiceRangeRepComponent.Cast(speaker.FindComponent(NVR_VoiceRangeRepComponent));
		int rangeMeters = NVR_VoiceRangeConfig.GetRangeMeters(NVR_VoiceRangeConfig.DEFAULT_RANGE_INDEX);
		if (rangeComponent)
			rangeMeters = rangeComponent.GetRangeMeters();
		else
			rangeMeters = NVR_VoiceRangeState.GetPlayerRangeMeters(playerId);

		float distance = vector.Distance(listener.GetOrigin(), speaker.GetOrigin());
		bool inRange = distance <= rangeMeters;
		if (!inRange)
			Print(string.Format("%1 voice receive check: speaker %2 distance %3m, selected range %4m, receiver present %5, blocked.", NVR_VoiceRangeConfig.LOG_PREFIX, playerId, distance, rangeMeters, receiver != null));

		return inRange;
	}
}

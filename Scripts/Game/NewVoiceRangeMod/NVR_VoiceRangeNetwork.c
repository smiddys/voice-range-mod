class NVR_VoiceRangeNetwork
{
	static void PublishLocalRange()
	{
		PlayerController controller = GetGame().GetPlayerController();
		if (!controller)
			return;

		int playerId = controller.GetPlayerId();
		int rangeIndex = NVR_VoiceRangeState.GetLocalRangeIndex();
		NVR_VoiceRangeState.SetPlayerRangeIndex(playerId, rangeIndex);

		IEntity controlledEntity = controller.GetControlledEntity();
		if (!controlledEntity)
			return;

		NVR_VoiceRangeRepComponent rangeComponent = NVR_VoiceRangeRepComponent.Cast(controlledEntity.FindComponent(NVR_VoiceRangeRepComponent));
		if (rangeComponent)
		{
			rangeComponent.SetLocalRangeIndex(rangeIndex);
			Print(string.Format("%1 synced replicated voice range %2.", NVR_VoiceRangeConfig.LOG_PREFIX, NVR_VoiceRangeState.GetLocalRangeLabel()));
		}
		else
			Print(string.Format("%1 controlled character has no replicated voice range component.", NVR_VoiceRangeConfig.LOG_PREFIX), LogLevel.WARNING);
	}
}

modded class SCR_VONController
{
	override void SetEntryActive(SCR_VONEntry entry, bool setFromMenu = false)
	{
		super.SetEntryActive(entry, setFromMenu);
		VRM_VoiceRangeManager.LogActiveVoiceEntry(entry);
	}

	override protected void ActionVONTransceiverCycle(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		super.ActionVONTransceiverCycle(value, reason);
	}

	override protected void ActionVONLongRangeToggle(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		super.ActionVONLongRangeToggle(value, reason);
	}

	override protected void ActionVONBroadcast(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		super.ActionVONBroadcast(value, reason);
	}

	override protected void ActionVONProximity(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		super.ActionVONProximity(value, reason);

		if (reason == EActionTrigger.DOWN)
		{
			VRM_VoiceRangeManager.SetDirectVoiceActive(true);
			VRM_VoiceRangeManager.ShowIndicator();
		}
		else if (reason == EActionTrigger.UP)
		{
			VRM_VoiceRangeManager.SetDirectVoiceActive(false);
		}
	}

	override protected void ActionVONProximityToggle(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		super.ActionVONProximityToggle(value, reason);

		if (reason == EActionTrigger.DOWN)
		{
			VRM_VoiceRangeManager.SetDirectVoiceActive(true);
			VRM_VoiceRangeManager.ShowIndicator();
		}
	}

	override protected void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		VRM_VoiceRangeManager.ShowIndicator();
	}
}

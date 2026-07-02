class NVR_VONRangePatch
{
	static void ApplyLocalRange()
	{
		SCR_VONController.NVR_ApplySelectedRange();
		ApplyLocalAudioSignals();
	}

	static void ApplyLocalAudioSignals()
	{
		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;

		int rangeIndex = NVR_VoiceRangeState.GetLocalRangeIndex();
		float rangeMeters = NVR_VoiceRangeConfig.GetRangeMeters(rangeIndex);
		float wcsRangeValue = NVR_VoiceRangeConfig.GetWCSRangeValue(rangeIndex);
		float vonAmplitudeValue = NVR_VoiceRangeConfig.GetVONAmplitudeValue(rangeIndex);
		bool applied = false;

		applied = ApplyAudioSignalsToEntity(playerController, rangeMeters, wcsRangeValue, vonAmplitudeValue) || applied;

		IEntity controlledEntity = playerController.GetControlledEntity();
		if (controlledEntity)
			applied = ApplyAudioSignalsToEntity(controlledEntity, rangeMeters, wcsRangeValue, vonAmplitudeValue) || applied;

		if (applied)
			Print(string.Format("%1 applied voice audio signals: %2m / WCS %3 / amplitude %4", NVR_VoiceRangeConfig.LOG_PREFIX, rangeMeters, wcsRangeValue, vonAmplitudeValue));
		else
			Print(string.Format("%1 no SoundOutputStateComponent accepted voice audio signals for %2m.", NVR_VoiceRangeConfig.LOG_PREFIX, rangeMeters), LogLevel.WARNING);
	}

	static void ApplyRangeToSpeaker(IEntity speaker, int rangeMeters)
	{
		if (!speaker)
			return;

		bool appliedSignal = ApplySoundSignals(speaker, rangeMeters);

		SCR_VoNComponent von = SCR_VoNComponent.Cast(speaker.FindComponent(SCR_VoNComponent));
		if (!von)
		{
			Print(string.Format("%1 controlled character has no SCR_VoNComponent for range application.", NVR_VoiceRangeConfig.LOG_PREFIX), LogLevel.WARNING);
			return;
		}

		if (appliedSignal)
			Print(string.Format("%1 applied proximity voice distance: %2m", NVR_VoiceRangeConfig.LOG_PREFIX, rangeMeters));
		else
			Print(string.Format("%1 found SCR_VoNComponent, but no known distance signal accepted %2m.", NVR_VoiceRangeConfig.LOG_PREFIX, rangeMeters), LogLevel.WARNING);
	}

	protected static bool ApplySoundSignals(IEntity speaker, int rangeMeters)
	{
		SoundOutputStateComponent soundOutput = SoundOutputStateComponent.Cast(speaker.FindComponent(SoundOutputStateComponent));
		if (!soundOutput)
			return false;

		bool applied = false;
		applied = SetSignalIfPresent(soundOutput, "VONDistance", rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, "VoNDistance", rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, "VONRange", rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, "VoiceRange", rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, "ProximityVoiceRange", rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, "Range", rangeMeters) || applied;

		return applied;
	}

	protected static bool ApplyAudioSignalsToEntity(IEntity entity, float rangeMeters, float wcsRangeValue, float vonAmplitudeValue)
	{
		if (!entity)
			return false;

		SoundOutputStateComponent soundOutput = SoundOutputStateComponent.Cast(entity.FindComponent(SoundOutputStateComponent));
		if (!soundOutput)
			return false;

		bool applied = false;
		applied = SetSignalIfPresent(soundOutput, NVR_VoiceRangeConfig.AUDIO_SIGNAL_RANGE_METERS, rangeMeters) || applied;
		applied = SetSignalIfPresent(soundOutput, NVR_VoiceRangeConfig.AUDIO_SIGNAL_WCS_RANGE, wcsRangeValue) || applied;
		applied = SetSignalIfPresent(soundOutput, NVR_VoiceRangeConfig.AUDIO_SIGNAL_VON_AMPLITUDE, vonAmplitudeValue) || applied;

		return applied;
	}

	protected static bool SetSignalIfPresent(SoundOutputStateComponent soundOutput, string signalName, float value)
	{
		int signalIndex = soundOutput.GetSignalIndex(signalName);
		if (signalIndex < 0)
			return false;

		soundOutput.SetSignalValue(signalIndex, value);
		return true;
	}
}

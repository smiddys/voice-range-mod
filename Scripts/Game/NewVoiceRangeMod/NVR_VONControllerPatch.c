modded class SCR_VONController
{
	protected static SCR_VONController s_NVR_Controller;
	protected InputManager m_NVR_InputManager;
	protected bool m_bNVR_ApplyingRange;

	override void SetEntryActive(SCR_VONEntry entry, bool setFromMenu = false)
	{
		s_NVR_Controller = this;
		super.SetEntryActive(entry, setFromMenu);
		NVR_ApplySelectedVoiceRangeComponent();
	}

	override bool AssignVONComponent()
	{
		s_NVR_Controller = this;
		bool assigned = super.AssignVONComponent();
		NVR_ApplySelectedVoiceRangeComponent();
		return assigned;
	}

	override void OnControlledEntityChanged(IEntity from, IEntity to)
	{
		s_NVR_Controller = this;
		super.OnControlledEntityChanged(from, to);
		NVR_ApplySelectedVoiceRangeComponent();
	}

	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);
		s_NVR_Controller = this;

		if (GetGame().GetWorld().IsEditMode())
			return;

		m_NVR_InputManager = GetGame().GetInputManager();
		if (!m_NVR_InputManager)
			return;

		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_INCREASE, EActionTrigger.DOWN, NVR_OnIncreaseVoiceRange);
		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_DECREASE, EActionTrigger.DOWN, NVR_OnDecreaseVoiceRange);
		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_TOGGLE_HUD, EActionTrigger.DOWN, NVR_OnToggleVoiceRangeHud);
		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_INCREASE_OLD, EActionTrigger.DOWN, NVR_OnIncreaseVoiceRange);
		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_DECREASE_OLD, EActionTrigger.DOWN, NVR_OnDecreaseVoiceRange);
		m_NVR_InputManager.AddActionListener(NVR_VoiceRangeConfig.ACTION_TOGGLE_HUD_OLD, EActionTrigger.DOWN, NVR_OnToggleVoiceRangeHud);

		Print(string.Format("%1 build 1.0.31 fixed-vanilla-loud-guid build loaded; registered F3/F4/F5 voice range controls.", NVR_VoiceRangeConfig.LOG_PREFIX));

		NVR_VoiceRangeHud.Ensure();
		NVR_VoiceRangeNetwork.PublishLocalRange();
		NVR_ApplySelectedVoiceRangeComponent();
	}

	override protected void ActionVONProximity(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		s_NVR_Controller = this;

		if (reason == EActionTrigger.DOWN)
			NVR_ApplySelectedVoiceRangeComponent();

		super.ActionVONProximity(value, reason);
	}

	override protected void ActionVONProximityToggle(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		s_NVR_Controller = this;

		if (reason == EActionTrigger.DOWN)
			NVR_ApplySelectedVoiceRangeComponent();

		super.ActionVONProximityToggle(value, reason);
	}

	override void SetVONProximityToggle(bool activate)
	{
		s_NVR_Controller = this;

		if (activate)
			NVR_ApplySelectedVoiceRangeComponent();

		super.SetVONProximityToggle(activate);
	}

	protected void NVR_OnIncreaseVoiceRange(float value, EActionTrigger reason = EActionTrigger.DOWN)
	{
		if (value == 0)
			return;

		Print(string.Format("%1 increase voice range input fired.", NVR_VoiceRangeConfig.LOG_PREFIX));
		NVR_ChangeVoiceRange(1);
	}

	protected void NVR_OnDecreaseVoiceRange(float value, EActionTrigger reason = EActionTrigger.DOWN)
	{
		if (value == 0)
			return;

		Print(string.Format("%1 decrease voice range input fired.", NVR_VoiceRangeConfig.LOG_PREFIX));
		NVR_ChangeVoiceRange(-1);
	}

	protected void NVR_OnToggleVoiceRangeHud(float value, EActionTrigger reason = EActionTrigger.DOWN)
	{
		if (value == 0)
			return;

		Print(string.Format("%1 toggle HUD input fired.", NVR_VoiceRangeConfig.LOG_PREFIX));
		NVR_VoiceRangeHud.ToggleVisible();
	}

	protected void NVR_ChangeVoiceRange(int direction)
	{
		NVR_VoiceRangeState.StepLocalRange(direction);
		NVR_VoiceRangeHud.Update();
		NVR_VoiceRangeNetwork.PublishLocalRange();
		NVR_ApplySelectedVoiceRangeComponent();

		Print(string.Format("%1 selected voice range %2", NVR_VoiceRangeConfig.LOG_PREFIX, NVR_VoiceRangeState.GetLocalRangeLabel()));
	}

	static void NVR_ApplySelectedRange()
	{
		if (!s_NVR_Controller)
		{
			PlayerController playerController = GetGame().GetPlayerController();
			if (playerController)
				s_NVR_Controller = SCR_VONController.Cast(playerController.FindComponent(SCR_VONController));
		}

		if (!s_NVR_Controller)
		{
			Print(string.Format("%1 could not apply voice range: local SCR_VONController was not found.", NVR_VoiceRangeConfig.LOG_PREFIX), LogLevel.WARNING);
			return;
		}

		s_NVR_Controller.NVR_ApplySelectedVoiceRangeComponent();
	}

	void NVR_ApplySelectedVoiceRangeComponent()
	{
		if (m_bNVR_ApplyingRange)
			return;

		PlayerController playerController = GetGame().GetPlayerController();
		if (!playerController)
			return;

		IEntity controlledEntity = playerController.GetControlledEntity();
		if (!controlledEntity)
			return;

		SCR_VoNComponent vonComponent = NVR_FindSelectedVoiceRangeComponent(controlledEntity);
		if (!vonComponent)
		{
			Print(string.Format("%1 no SCR_VoNComponent found on controlled character %2.", NVR_VoiceRangeConfig.LOG_PREFIX, controlledEntity), LogLevel.WARNING);
			return;
		}

		if (m_VONComp == vonComponent)
		{
			return;
		}

		bool wasDirectActive = false;
		bool wasDirectToggled = m_bIsToggledDirect;

		if (m_bIsActive && m_eVONType == EVONTransmitType.DIRECT)
			wasDirectActive = true;

		if (m_bIsActive)
			DeactivateVON(m_eVONType);

		m_bIsToggledDirect = false;

		m_bNVR_ApplyingRange = true;
		SetVONComponent(vonComponent);
		m_bNVR_ApplyingRange = false;

		if (wasDirectActive && !m_bNVR_ApplyingRange)
		{
			if (wasDirectToggled)
				SetVONProximityToggle(true);
			else
				ActionVONProximity(1.0, EActionTrigger.DOWN);
		}

		if (m_VONComp == vonComponent)
			Print(string.Format("%1 proximity VON audio component active for %2.", NVR_VoiceRangeConfig.LOG_PREFIX, NVR_VoiceRangeState.GetLocalRangeLabel()));
		else
			Print(string.Format("%1 tried to set proximity VON audio component for %2, but active component did not match.", NVR_VoiceRangeConfig.LOG_PREFIX, NVR_VoiceRangeState.GetLocalRangeLabel()), LogLevel.WARNING);
	}

	protected SCR_VoNComponent NVR_FindSelectedVoiceRangeComponent(IEntity entity)
	{
		int rangeIndex = NVR_VoiceRangeState.GetLocalRangeIndex();
		switch (rangeIndex)
		{
			case 0:
				return SCR_VoNComponent.Cast(entity.FindComponent(NVR_VoNRange5Component));
			case 1:
				return SCR_VoNComponent.Cast(entity.FindComponent(NVR_VoNRange30Component));
			case 2:
				return SCR_VoNComponent.Cast(entity.FindComponent(NVR_VoNRange60Component));
		}

		return null;
	}

	override void OnDelete(IEntity owner)
	{
		if (m_NVR_InputManager)
		{
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_INCREASE, EActionTrigger.DOWN, NVR_OnIncreaseVoiceRange);
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_DECREASE, EActionTrigger.DOWN, NVR_OnDecreaseVoiceRange);
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_TOGGLE_HUD, EActionTrigger.DOWN, NVR_OnToggleVoiceRangeHud);
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_INCREASE_OLD, EActionTrigger.DOWN, NVR_OnIncreaseVoiceRange);
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_DECREASE_OLD, EActionTrigger.DOWN, NVR_OnDecreaseVoiceRange);
			m_NVR_InputManager.RemoveActionListener(NVR_VoiceRangeConfig.ACTION_TOGGLE_HUD_OLD, EActionTrigger.DOWN, NVR_OnToggleVoiceRangeHud);
		}

		super.OnDelete(owner);
	}
}

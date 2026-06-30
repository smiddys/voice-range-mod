[ComponentEditorProps(category: "GameScripted/VoiceRangeMod", description: "Handles voice range input actions.")]
class VRM_VoiceRangeInputComponentClass : ScriptComponentClass
{
}

class VRM_VoiceRangeInputComponent : ScriptComponent
{
	protected const string VRM_ACTION_RANGE_INCREASE = "VRMVoiceRangeIncrease";
	protected const string VRM_ACTION_RANGE_DECREASE = "VRMVoiceRangeDecrease";

	protected InputManager m_InputManager;
	protected bool m_bIncreaseBlocked;
	protected bool m_bDecreaseBlocked;

	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		m_InputManager = GetGame().GetInputManager();
		if (!m_InputManager)
		{
			if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
				Print("[VoiceRangeMod] Input component could not find InputManager.");

			return;
		}

		m_InputManager.AddActionListener(VRM_ACTION_RANGE_INCREASE, EActionTrigger.DOWN, OnRangeIncrease);
		m_InputManager.AddActionListener(VRM_ACTION_RANGE_INCREASE, EActionTrigger.UP, OnRangeIncrease);
		m_InputManager.AddActionListener(VRM_ACTION_RANGE_DECREASE, EActionTrigger.DOWN, OnRangeDecrease);
		m_InputManager.AddActionListener(VRM_ACTION_RANGE_DECREASE, EActionTrigger.UP, OnRangeDecrease);

		if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
			Print("[VoiceRangeMod] Player controller input component registered range actions.");
	}

	protected void OnRangeIncrease(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		if (value == 0 || m_bIncreaseBlocked)
			return;

		VRM_VoiceRangeManager.IncreaseSelectedRange();
		m_bIncreaseBlocked = true;
		GetGame().GetCallqueue().CallLater(ResetIncreaseBlock, 250, false);
	}

	protected void OnRangeDecrease(float value, EActionTrigger reason = EActionTrigger.UP)
	{
		if (value == 0 || m_bDecreaseBlocked)
			return;

		VRM_VoiceRangeManager.DecreaseSelectedRange();
		m_bDecreaseBlocked = true;
		GetGame().GetCallqueue().CallLater(ResetDecreaseBlock, 250, false);
	}

	protected void ResetIncreaseBlock()
	{
		m_bIncreaseBlocked = false;
	}

	protected void ResetDecreaseBlock()
	{
		m_bDecreaseBlocked = false;
	}

	override void OnDelete(IEntity owner)
	{
		if (m_InputManager)
		{
			m_InputManager.RemoveActionListener(VRM_ACTION_RANGE_INCREASE, EActionTrigger.DOWN, OnRangeIncrease);
			m_InputManager.RemoveActionListener(VRM_ACTION_RANGE_INCREASE, EActionTrigger.UP, OnRangeIncrease);
			m_InputManager.RemoveActionListener(VRM_ACTION_RANGE_DECREASE, EActionTrigger.DOWN, OnRangeDecrease);
			m_InputManager.RemoveActionListener(VRM_ACTION_RANGE_DECREASE, EActionTrigger.UP, OnRangeDecrease);
		}

		super.OnDelete(owner);
	}
}

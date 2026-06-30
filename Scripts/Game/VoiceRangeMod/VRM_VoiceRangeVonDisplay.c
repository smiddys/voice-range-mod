modded class SCR_VonDisplay
{
	protected const ResourceName VRM_RANGE_LAYOUT = "$voicerangemod:Scripts/Game/VoiceRangeMod/UI/layouts/VoiceRange/VoiceLayout.layout";
	protected Widget m_wVRMRangeRoot;
	protected TextWidget m_wVRMRangeText;

	override bool DisplayStartDrawInit(IEntity owner)
	{
		bool result = super.DisplayStartDrawInit(owner);
		VRM_CreateRangeIndicator();
		VRM_UpdateRangeIndicator();
		return result;
	}

	override void DisplayUpdate(IEntity owner, float timeSlice)
	{
		super.DisplayUpdate(owner, timeSlice);
		VRM_UpdateRangeIndicator();
	}

	override void DisplayStopDraw(IEntity owner)
	{
		if (m_wVRMRangeRoot)
		{
			m_wVRMRangeRoot.RemoveFromHierarchy();
			m_wVRMRangeRoot = null;
			m_wVRMRangeText = null;
		}

		super.DisplayStopDraw(owner);
	}

	protected void VRM_CreateRangeIndicator()
	{
		if (m_wVRMRangeRoot)
			return;

		Widget parent = GetContentWidget();
		if (!parent)
			return;

		m_wVRMRangeRoot = GetGame().GetWorkspace().CreateWidgets(VRM_RANGE_LAYOUT, parent);
		if (!m_wVRMRangeRoot)
		{
			if (VRM_VoiceRangeConfig.DEBUG_LOGGING)
				Print(string.Format("[VoiceRangeMod] Could not create voice range layout: %1", VRM_RANGE_LAYOUT));

			return;
		}

		m_wVRMRangeText = TextWidget.Cast(SCR_WidgetHelper.GetWidgetOrChild(m_wVRMRangeRoot, "RangeText"));
		if (!m_wVRMRangeText && VRM_VoiceRangeConfig.DEBUG_LOGGING)
			Print("[VoiceRangeMod] Voice range layout loaded, but RangeText was not found.");
	}

	protected void VRM_UpdateRangeIndicator()
	{
		VRM_CreateRangeIndicator();

		if (!m_wVRMRangeRoot)
			return;

		bool isOutgoingVoiceActive = VRM_VoiceRangeManager.IsDirectVoiceActive();
		if (!isOutgoingVoiceActive && m_OutTransmission)
			isOutgoingVoiceActive = m_OutTransmission.m_bIsActive;

		bool showIndicator = VRM_VoiceRangeManager.IsIndicatorVisible() && isOutgoingVoiceActive;
		m_wVRMRangeRoot.SetVisible(showIndicator);

		if (!showIndicator || !m_wVRMRangeText)
			return;

		m_wVRMRangeText.SetText(VRM_VoiceRangeManager.GetSelectedCompactRangeLabel());
	}
}

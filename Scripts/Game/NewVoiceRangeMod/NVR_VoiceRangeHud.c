class NVR_VoiceRangeHud
{
	protected static Widget s_wRoot;
	protected static TextWidget s_wRangeText;
	protected static bool s_bVisible = true;

	static void Ensure()
	{
		if (s_wRangeText)
			return;

		WorkspaceWidget workspace = GetGame().GetWorkspace();
		if (!workspace)
			return;

		s_wRoot = workspace.CreateWidgets("{72A331E1AB7C4003}UI/layouts/NewVoiceRange/NVR_VoiceRangeHud.layout");
		if (!s_wRoot)
		{
			Print(string.Format("%1 could not create voice range HUD layout.", NVR_VoiceRangeConfig.LOG_PREFIX), LogLevel.WARNING);
			return;
		}

		s_wRangeText = TextWidget.Cast(s_wRoot.FindAnyWidget("NVR_RangeText"));
		if (!s_wRangeText)
			Print(string.Format("%1 voice range HUD text widget not found.", NVR_VoiceRangeConfig.LOG_PREFIX), LogLevel.WARNING);

		s_wRoot.SetVisible(s_bVisible);
		Update();
	}

	static void Update()
	{
		if (!s_wRangeText)
			return;

		s_wRangeText.SetText(NVR_VoiceRangeState.GetLocalRangeLabel());
	}

	static void ToggleVisible()
	{
		s_bVisible = !s_bVisible;
		Ensure();

		if (s_wRoot)
			s_wRoot.SetVisible(s_bVisible);

		Print(string.Format("%1 voice range HUD visible: %2", NVR_VoiceRangeConfig.LOG_PREFIX, s_bVisible));
	}
}

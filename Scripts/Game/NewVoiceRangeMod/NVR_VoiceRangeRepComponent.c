[ComponentEditorProps(category: "GameScripted/NewVoiceRangeMod", description: "Replicates selected proximity voice range.")]
class NVR_VoiceRangeRepComponentClass : ScriptComponentClass
{
}

class NVR_VoiceRangeRepComponent : ScriptComponent
{
	[RplProp(onRplName: "OnVoiceRangeChanged")]
	protected int m_iRangeIndex = NVR_VoiceRangeConfig.DEFAULT_RANGE_INDEX;

	int GetRangeIndex()
	{
		return NVR_VoiceRangeConfig.ClampRangeIndex(m_iRangeIndex);
	}

	int GetRangeMeters()
	{
		return NVR_VoiceRangeConfig.GetRangeMeters(GetRangeIndex());
	}

	void SetLocalRangeIndex(int rangeIndex)
	{
		rangeIndex = NVR_VoiceRangeConfig.ClampRangeIndex(rangeIndex);
		m_iRangeIndex = rangeIndex;
		OnVoiceRangeChanged();
		Rpc(RpcAsk_SetVoiceRangeIndex, rangeIndex);
	}

	[RplRpc(RplChannel.Reliable, RplRcver.Server)]
	protected void RpcAsk_SetVoiceRangeIndex(int rangeIndex)
	{
		rangeIndex = NVR_VoiceRangeConfig.ClampRangeIndex(rangeIndex);
		if (m_iRangeIndex == rangeIndex)
			return;

		m_iRangeIndex = rangeIndex;
		OnVoiceRangeChanged();
		Replication.BumpMe();
	}

	protected void OnVoiceRangeChanged()
	{
	}
}

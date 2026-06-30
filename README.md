# Voice Range Mod for Arma Reforger

An Arma Reforger / Enfusion Workbench mod project for a selectable proximity VOIP range system.

This project does not modify radio range. The installed public script API exposes radio range through `BaseTransceiver.SetRange(float)`, but direct proximity speech is handled by `VoNComponent` and does not expose a public distance/range setter in the installed API docs.

## Files

- `VoiceRangeMod.gproj` - Arma Reforger Workbench project file.
- `Scripts/Game/VoiceRangeMod/VRM_VoiceRangeConfig.c` - the allowed proximity VOIP ranges.
- `Scripts/Game/VoiceRangeMod/VRM_VoiceRangeManager.c` - tracks the selected proximity VOIP range.
- `Scripts/Game/VoiceRangeMod/VRM_VoiceRangeBootstrap.c` - hooks `SCR_VONController.SetEntryActive`.
- `Scripts/Game/VoiceRangeMod/VRM_VoNComponent.c` - receiver-side direct VOIP distance filter prototype.
- `Configs/VoiceRangeMod.conf` - human-readable tuning values.

## Ranges

Players should be able to select one of these direct proximity VOIP ranges:

- 5 m
- 15 m
- 30 m
- 45 m
- 60 m

Default: 30 m

## Workbench Steps

1. Open Arma Reforger Tools.
2. Open this folder as a project using `VoiceRangeMod.gproj`.
3. Compile scripts.
4. Package and publish through Workbench.

## Important

This must use the game's normal proximity VOIP chat, not radios. The current prototype filters direct VOIP in `SCR_VoNComponent.OnReceive()` by comparing listener distance to the speaker's selected range. Workbench/in-game testing is needed to confirm whether returning before `super.OnReceive()` fully suppresses playback.

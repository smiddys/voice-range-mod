# NEW VOICE RANGE MOD

Variable proximity voice range for Arma Reforger.

## Features

- Player-selectable proximity VOIP ranges: 5 m, 15 m, 30 m, 45 m, 60 m.
- Rebindable increase/decrease controls.
- Default keyboard controls: F3 decreases range, F4 increases range, F5 toggles the range HUD.
- Controls should appear in Settings > Controls under "Voice Range Settings".
- Default controller controls: right shoulder + D-pad down decreases range, right shoulder + D-pad up increases range, right shoulder + D-pad right toggles HUD visibility.
- Controls category: Voice Range Settings.
- Persistent left-middle HUD range indicator.
- Multiplayer range state replication hook for real proximity voice filtering.

## Workbench Validation

Open this project in Workbench, run Script Editor validation, then check these assets:

- `Configs/System/chimeraInputCommon.conf`
- `Configs/System/keyBindingMenu.conf`
- `Scripts/Game/NewVoiceRangeMod`

The gameplay hook is intentionally isolated in `NVR_VONRangePatch.c`. If the current game build exposes a different VON distance method name, update only that file.

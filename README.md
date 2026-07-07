# NEW VOICE RANGE MOD

Variable proximity voice range for Arma Reforger.

## Features

- Player-selectable proximity VOIP ranges: 5 m, 30 m, 60 m.
- Rebindable increase/decrease controls.
- Default keyboard controls: F3 decreases range, F4 increases range, F5 toggles the range HUD.
- Controls should appear in Settings > Controls under "Voice Range Settings".
- Default controller controls: right shoulder + D-pad down decreases range, right shoulder + D-pad up increases range, right shoulder + D-pad right toggles HUD visibility.
- Controls category: Voice Range Settings.
- Persistent left-middle HUD range indicator.
- Three-tier VON setup modeled after the reference voice range mod: explicit custom VON components for 5 m, 30 m, and 60 m.

## Workbench Validation

Open this project in Workbench, run Script Editor validation, then check these assets:

- `Configs/System/chimeraInputCommon.conf`
- `Configs/System/keyBindingMenu.conf`
- `Scripts/Game/NewVoiceRangeMod`

The gameplay path is intentionally kept close to the reference mod: prefab-bound VON components provide explicit 5 m, 30 m, and 60 m tiers, and the controller switches directly to the selected component class.

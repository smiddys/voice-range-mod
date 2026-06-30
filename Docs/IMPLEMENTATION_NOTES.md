# Implementation Notes

The installed Arma Reforger script API archive confirms these relevant classes:

- `SCR_VONController`
- `SCR_VONEntry`
- `SCR_VoNComponent`
- `VoNComponent`

`SCR_VONController` manages direct and radio VON entries. `VoNComponent` exposes capture, communication method, and transmit-radio methods.

The public API also exposes `BaseTransceiver.SetRange(float)`, but that is radio-only and is not the requested direct proximity voice range.

Required direct proximity VOIP ranges:

- 5 m
- 15 m
- 30 m
- 45 m
- 60 m

Current status: this project stores and cycles the selected range in script, hooks `SCR_VONController.SetEntryActive()`, and adds a `SCR_VoNComponent.OnReceive()` receiver-side direct VOIP filter.

Prototype behavior:

- If `receiver` is null, the transmission is direct proximity voice.
- The receiver looks up the sender's controlled entity using `PlayerManager.GetPlayerControlledEntity(playerId)`.
- If listener distance is greater than the sender's selected range, `OnReceive()` returns before calling `super.OnReceive()`.

The next test is compiling this in Workbench and checking whether skipping `super.OnReceive()` prevents direct VOIP playback.

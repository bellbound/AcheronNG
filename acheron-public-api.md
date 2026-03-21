# AcheronNG Public API

API surface that other mods can use to integrate with Acheron's defeat system.

All functions are on the `Acheron` global script unless noted otherwise.

## Core Defeat System

```papyrus
Function DefeatActor(Actor akActor) native global
Function RescueActor(Actor akActor, bool abRelease = true) native global
Function PacifyActor(Actor akActor) native global
Function ReleaseActor(Actor akActor) native global

bool Function IsDefeated(Actor akActor) native global
bool Function IsPacified(Actor akActor) native global
Actor[] Function GetDefeated(bool abLoadedOnly = false) native global
Actor[] Function GetPacified(bool abLoadedOnly = false) native global
```

Defeated actors receive the `AcheronDefeated` keyword, pacified actors receive `AcheronPacified`.

## Processing & Consequence Toggles

```papyrus
Function DisableProcessing(bool abDisable) native global
bool Function IsProcessingDisabled() native global
Function DisableConsequence(bool abDisable) native global
bool Function IsConsequenceDisabled() native global
bool Function IsTeleportAllowed() native global
```

## Event System

Four events, each with registration on `Form`, `ReferenceAlias` (`_Alias`), and `ActiveMagicEffect` (`_MgEff`):

### Actor Defeated
```papyrus
Function RegisterForActorDefeated(Form akForm) native global
Function UnregisterForActorDefeated(Form akForm) native global
Event OnActorDefeated(Actor akVictim)
```

### Actor Rescued
```papyrus
Function RegisterForActorRescued(Form akForm) native global
Function UnregisterForActorRescued(Form akForm) native global
Event OnActorRescued(Actor akVictim)
```

### Player Death
```papyrus
Function RegisterForPlayerDeathEvent(Form akForm) native global
Function UnregisterForPlayerDeathEvent(Form akForm) native global
Event OnPlayerDeathEvent()
```

### Hunter's Pride Selection
```papyrus
Function RegisterForHunterPrideSelect(Form akForm) native global
Function UnregisterForHunterPrideSelect(Form akForm) native global
Event OnHunterPrideSelect(int aiOptionID, Actor akTarget)
```

## Hunter's Pride Menu (Dynamic Options)

Lets other mods inject options into the interaction menu when the player activates a defeated NPC.

```papyrus
int Function AddOption(String asOptionID, String asOptionName, String asIconSource, String asConditions = "") native global
bool Function RemoveOption(String asOptionID) native global
bool Function HasOption(String asOptionID) native global
int Function GetOptionID(String asOptionID) native global
```

- `asOptionID`: Unique string ID (prefix with your mod name to avoid conflicts)
- `asOptionName`: Display name (supports localization)
- `asIconSource`: Icon path relative to `Interface\Acheron`
- `asConditions`: JSON string of conditions controlling availability
- Returns integer option ID, or -1 on failure

## Actor Utilities

```papyrus
Armor[] Function GetWornArmor(Actor akActor, int aiIgnoredMasks = 0) native global
Armor[] Function StripActor(Actor akActor, int aiIgnoredFlags = 0) native global
Potion Function GetMostEfficientPotion(Actor akActor, ObjectReference akContainer) native global
Actor[] Function GetFollowers() native global
String Function GetRaceType(Actor akActor) native global
```

`GetRaceType` groups similar races (e.g. all bear variants -> `"Bear"`, dogs/wolves -> `"Wolf"`).

## ObjectReference Utilities

```papyrus
Function SetLinkedRef(ObjectReference akSource, ObjectReference akTarget, Keyword akLink = none) native global
Function RemoveAllItems(ObjectReference akTransferFrom, ObjectReference akTransferTo = none, bool abExcludeWorn = true) native global
Form[] Function GetItemsByKeywords(ObjectReference akContainer, Keyword[] akKeywords, int aiMinValue = 0, bool abIgnoreQuestItems = true) native global
```

## UI / Misc

```papyrus
Function PrintConsole(String asMsg) native global
bool Function OpenCustomMenu(String asFilePath) native global
Function CloseCustomMenu() native global
```

`OpenCustomMenu` loads a SWF from `Interface\` (no extension, doesn't pause game). Menu name is `AcheronCustomMenu`.

## MCM Settings Access (AcheronMCM script)

```papyrus
int Function GetSettingInt(String asSetting) native
float Function GetSettingFloat(String asSetting) native
bool Function GetSettingBool(String asSetting) native
int Function GetSettingColor(String asSetting) native

Function SetSettingInt(String asSetting, int aiValue) native
Function SetSettingFloat(String asSetting, float aiValue) native
Function SetSettingBool(String asSetting, bool abValue) native
Function SetSettingColor(String asSetting, int aiColor) native

String[] Function GetEvents(int aiType) native
String Function SetEventWeight(String asEvent, int aiType, int aiNewWeight) native
Function UpdateKillmoveGlobal() native
```

Event types: 0=Hostile, 1=Follower, 2=Civilian, 3=Guards, 4=NPC, 5=Surrender

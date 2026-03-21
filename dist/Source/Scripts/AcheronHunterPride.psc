Scriptname AcheronHunterPride extends Quest Hidden

Function OpenHunterPrideMenu(Actor akTarget) native

PlayerVampireQuestScript Property PlayerVampireQuest Auto
Activator Property HealTargetFX Auto
Actor Property PlayerRef Auto

Message Property IsEssentialMsg Auto
Message Property NoPotionMsg Auto

bool bFlashMenu = false

Event OnInit()
  bFlashMenu = Acheron.IsFlashMenuAvailable()
EndEvent

Function OpenMenu(Actor akTarget)
  Acheron.RegisterForHunterPrideSelect(self)

  If bFlashMenu
    OpenHunterPrideMenu(akTarget)
  Else
    String[] optNames = Acheron.GetAvailableOptions(akTarget)
    Int[] optIDs = Acheron.GetAvailableOptionIDs(akTarget)

    If optNames.Length == 0
      return
    EndIf

    UIListMenu listMenu = UIExtensions.GetMenu("UIListMenu") as UIListMenu
    If listMenu == None
      Debug.Notification("UIExtensions required for Hunter's Pride menu")
      return
    EndIf

    listMenu.ResetMenu()
    int headerEntry = listMenu.AddEntryItem("HUNTER'S PRIDE")
    int[] entryIDs = new int[128]
    int i = 0
    int entryCount = 0
    While i < optNames.Length
      If optNames[i] != ""
        entryIDs[entryCount] = i
        listMenu.AddEntryItem(optNames[i])
        entryCount += 1
      EndIf
      i += 1
    EndWhile

    listMenu.OpenMenu()
    int selectedEntry = listMenu.GetResultInt()
    String selectedText = listMenu.GetResultString()
    Debug.Trace("HunterPride: selectedEntry=" + selectedEntry + " selectedText=" + selectedText + " entryCount=" + entryCount)

    If selectedEntry < 0 || selectedEntry == headerEntry
      return
    EndIf

    ; selectedEntry is 0-based entry index; header is 0, first option is 1
    int optIndex = selectedEntry - 1
    If optIndex >= 0 && optIndex < entryCount
      Debug.Trace("HunterPride: dispatching optID=" + optIDs[entryIDs[optIndex]] + " for entry " + optIndex)
      Acheron.NotifyOptionSelected(akTarget, optIDs[entryIDs[optIndex]])
    EndIf
  EndIf
EndFunction

Event OnHunterPrideSelect(int aiOptionID, Actor akTarget)
  Debug.Trace("OnHunterPrideSelect: " + aiOptionID + " / " + akTarget)
  If(aiOptionID == 0)
    Potion p = Acheron.GetMostEfficientPotion(akTarget, PlayerRef)
    If(!p)
      NoPotionMsg.Show()
      return
    EndIf
    PlayerRef.RemoveItem(p, 1, true, akTarget)
    akTarget.EquipItem(p, false, true)
    If(Acheron.IsDefeated(akTarget))
      ; Some actors are immune to potion effect
      akTarget.PlaceAtMe(HealTargetFX)
      akTarget.RestoreActorValue("Health", 25.0)
      Acheron.RescueActor(akTarget, true)
    EndIf
  ElseIf(aiOptionID == 1)
    akTarget.OpenInventory(true)
    akTarget.SendAssaultAlarm()
  ElseIf(aiOptionID == 2)
    If(CheckEssential(akTarget))
      return
    EndIf
    ; TODO: Add Animation
    akTarget.Kill(PlayerRef)
  ElseIf(aiOptionID == 3)
    If(CheckEssential(akTarget))
      return
    EndIf
    PlayerRef.StartVampireFeed(akTarget)
    PlayerVampireQuest.VampireFeed()
    akTarget.Kill(PlayerRef)
  EndIf
EndEvent

bool Function CheckEssential(Actor akTarget)
  ActorBase base = akTarget.GetLeveledActorBase()
  If(!base.IsEssential())
    return false
  EndIf
  If(IsEssentialMsg.Show() == 1)
    base.SetEssential(false)
    return false
  EndIf
  return true
EndFunction

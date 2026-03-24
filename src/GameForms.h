#pragma once

namespace Acheron
{
	struct GameForms
	{
		// Vanilla Game
		static inline RE::TESFaction* GuardDiaFac;
		static inline RE::TESGlobal* KillMove;
		static inline RE::TESIdleForm* BleedoutStart;
		static inline RE::TESIdleForm* BleedoutStop;

		// Acheron Forms
		static inline RE::BGSKeyword* Defeated;
		static inline RE::BGSKeyword* Pacified;

		static inline RE::TESQuest* DefaultCommon;
		static inline RE::TESQuest* DefaultGuard;

		static inline RE::SpellItem* HunterPride;
		static inline RE::EffectSetting* HunterPrideEffect;

		static inline RE::TESPackage* BlankPackage;

		static inline RE::TESFaction* IgnoredFaction;

		static inline RE::BGSPerk* InteractionPerk;

		static inline bool formsLoaded{ false };

		[[nodiscard]] static bool LoadForms()
		{
			bool ok = true;

			const auto LogVanillaFailure = [&](const char* name, RE::FormID formid) {
				auto* raw = RE::TESForm::LookupByID(formid);
				if (raw) {
					logger::error("Failed to load vanilla form {} [{:08X}]: exists as FormType {} but expected a different type",
						name, formid, static_cast<uint32_t>(raw->GetFormType()));
				} else {
					logger::error("Failed to load vanilla form {} [{:08X}]: form does not exist", name, formid);
				}
				ok = false;
			};

			const auto LogAcheronFailure = [&](const char* name, RE::FormID formid) {
				auto* handler = RE::TESDataHandler::GetSingleton();
				auto* raw = handler ? handler->LookupForm(formid, "Acheron.esm") : nullptr;
				if (raw) {
					logger::error("Failed to load Acheron.esm form {} [{:03X}]: exists as FormType {} but expected a different type",
						name, formid, static_cast<uint32_t>(raw->GetFormType()));
				} else if (!handler) {
					logger::error("Failed to load Acheron.esm form {} [{:03X}]: TESDataHandler unavailable", name, formid);
				} else {
					logger::error("Failed to load Acheron.esm form {} [{:03X}]: form does not exist. Is Acheron.esm loaded?",
						name, formid);
				}
				ok = false;
			};

			// Vanilla Game forms
			GuardDiaFac = RE::TESForm::LookupByID<RE::TESFaction>(0x0002BE3B);
			if (!GuardDiaFac) LogVanillaFailure("GuardDialogueFaction", 0x0002BE3B);

			KillMove = RE::TESForm::LookupByID<RE::TESGlobal>(0x00100F19);
			if (!KillMove) LogVanillaFailure("KillMove", 0x00100F19);

			BleedoutStart = RE::TESForm::LookupByID<RE::TESIdleForm>(0x00013ECC);
			if (!BleedoutStart) LogVanillaFailure("BleedoutStart", 0x00013ECC);

			BleedoutStop = RE::TESForm::LookupByID<RE::TESIdleForm>(0x00013ECE);
			if (!BleedoutStop) LogVanillaFailure("BleedoutStop", 0x00013ECE);

			// Acheron.esm forms
			auto* handler = RE::TESDataHandler::GetSingleton();

			Defeated = handler ? handler->LookupForm<RE::BGSKeyword>(0x801, "Acheron.esm") : nullptr;
			if (!Defeated) LogAcheronFailure("Defeated", 0x801);

			Pacified = handler ? handler->LookupForm<RE::BGSKeyword>(0x802, "Acheron.esm") : nullptr;
			if (!Pacified) LogAcheronFailure("Pacified", 0x802);

			DefaultCommon = handler ? handler->LookupForm<RE::TESQuest>(0x805, "Acheron.esm") : nullptr;
			if (!DefaultCommon) LogAcheronFailure("DefaultCommon", 0x805);

			DefaultGuard = handler ? handler->LookupForm<RE::TESQuest>(0x809, "Acheron.esm") : nullptr;
			if (!DefaultGuard) LogAcheronFailure("DefaultGuard", 0x809);

			HunterPride = handler ? handler->LookupForm<RE::SpellItem>(0x807, "Acheron.esm") : nullptr;
			if (!HunterPride) LogAcheronFailure("HunterPride", 0x807);

			HunterPrideEffect = handler ? handler->LookupForm<RE::EffectSetting>(0x806, "Acheron.esm") : nullptr;
			if (!HunterPrideEffect) LogAcheronFailure("HunterPrideEffect", 0x806);

			BlankPackage = handler ? handler->LookupForm<RE::TESPackage>(0x804, "Acheron.esm") : nullptr;
			if (!BlankPackage) LogAcheronFailure("BlankPackage", 0x804);

			IgnoredFaction = handler ? handler->LookupForm<RE::TESFaction>(0x80C, "Acheron.esm") : nullptr;
			if (!IgnoredFaction) LogAcheronFailure("IgnoredFaction", 0x80C);

			InteractionPerk = handler ? handler->LookupForm<RE::BGSPerk>(0x803, "Acheron.esm") : nullptr;
			if (!InteractionPerk) LogAcheronFailure("InteractionPerk", 0x803);

			formsLoaded = ok;
			return ok;
		}
	};

}	 // namespace Acheron

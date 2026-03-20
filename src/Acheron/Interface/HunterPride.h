#pragma once

namespace Acheron::Interface
{
	class HunterPride
	{
	public:
		static constexpr std::array DEFAULT_OPTIONS = { "rescue", "plunder", "execute", "vampire" };

		static void SetTarget(RE::Actor* a_target) { _target = a_target;}

		static int32_t AddOption(const RE::BSFixedString& a_option, const std::string& a_conditionstring, const std::string& a_name, const std::string& a_iconsrc);
		static bool RemoveOption(const RE::BSFixedString& a_option);
		static bool HasOption(const RE::BSFixedString& a_option);
		static int32_t GetOptionID(const RE::BSFixedString& a_option);

		// Data provider for Papyrus menu
		static std::vector<std::string> GetAvailableOptionNames(RE::Actor* a_target);
		static std::vector<int32_t> GetAvailableOptionIDs(RE::Actor* a_target);
		static void NotifyOptionSelected(int32_t a_optionID, RE::Actor* a_target);

		// Serialization
		static void Save(SKSE::SerializationInterface* a_intfc);
		static void Load(SKSE::SerializationInterface* a_intfc);
		static void Revert(SKSE::SerializationInterface* a_intfc);

	public:
		struct Option
		{
			struct CONDITION
			{
				union ConditionValue
				{
					RE::TESFaction* faction;
					RE::BGSKeyword* keyword;
					bool boolean;
				};

				enum class ConditionType : uint8_t
				{
					Faction,
					Keyword,
					Essential,
					Hostile
				};

			public:
				CONDITION(ConditionType a_type, const std::string& a_objstring, bool a_reverse);
				CONDITION(ConditionType a_type, bool a_reverse) :
					reverse(a_reverse), type(a_type) { assert(a_type == ConditionType::Essential || a_type == ConditionType::Hostile); }
				CONDITION(ConditionType a_type, ConditionValue a_value, bool a_reverse) :
					reverse(a_reverse), type(a_type), value(a_value) {}
				~CONDITION() = default;

				_NODISCARD bool Check(RE::Actor* a_target) const;

			public:
				bool reverse;
				ConditionType type;
				ConditionValue value;
			};

			enum ConditionTarget
			{
				Player,
				Target,

				Total
			};

		public:
			Option(const RE::BSFixedString& a_option, const std::string& a_conditions, const std::string& a_name, const std::string& a_icon);
			Option() = default;
			~Option() = default;

			_NODISCARD bool Check() const;
			_NODISCARD const RE::BSFixedString& GetID() const;

		public:
			RE::BSFixedString _id;
			std::string _name;
			std::string _iconurl;  // kept for cosave backward compatibility

			std::vector<CONDITION> conditions[ConditionTarget::Total];
		};

	private:
		static inline RE::Actor* _target;
		static inline std::vector<Option> _options;
	};
}

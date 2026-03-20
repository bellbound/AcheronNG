 Complete summary of all 6 hooks

  // ===== ProcessHitData (xbyak) =====
  REL::Relocation<std::uintptr_t> phd{ RELOCATION_ID(37633, 38586), REL::Relocate(0x76, 0x7E) };
  // xbyak uses: REL::Relocate(0xF0, 0xF8), REL::Relocate(r14, r15), REL::Relocate(r15, r13)

  // ===== MagicHit =====
  REL::Relocation<std::uintptr_t> magichit{ RELOCATION_ID(33763, 34547), REL::Relocate(0x52F, 0x7B1, 0x4B1) };

  // ===== DoesMagicHitApply =====
  REL::Relocation<std::uintptr_t> mha{ RELOCATION_ID(33742, 34526), REL::Relocate(0x1E8, 0x20B) };

  // ===== DoDetect =====
  REL::Relocation<std::uintptr_t> det{ RELOCATION_ID(41659, 42742), REL::Relocate(0x526, 0x67B) };

  // ===== FallDamage / ragdoll =====
  REL::Relocation<std::uintptr_t> ragdoll_dmg{ RELOCATION_ID(36346, 37336), 0x35 };

  // ===== FallDamage / movefinish =====
  REL::Relocation<std::uintptr_t> movefinish{ RELOCATION_ID(36973, 37998), REL::Relocate(0xAE, 0xAB) };
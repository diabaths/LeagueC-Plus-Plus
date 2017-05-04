#pragma once
#include "Extension.h"
#include "SpellDatabase.h"
#include "Burst.h"
#include "Damage.h"

PLUGIN_EVENT(void) OnProcessCast(CastedSpell const& spell)
{
	if (GetAsyncKeyState(Burst->GetInteger()))
	{
		Burstonprocess(spell);
	}
	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
	{
		auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);

		if (Contains(std::string(spell.Name_), "VladimirE"))
		{
			if (W->IsReady() && ComboW->Enabled() && myHero->IsValidTarget(Enemy, Q->Range()) && (myHero->HealthPercent() < 5 || Enemy->GetHealth() <= 1.4 * TotalDamage(Enemy)))
			{
				W->CastOnPlayer();
			}
		}
	}
	if (zhonyas->IsOwned() && zhonyas->IsReady() || W->IsReady())
	{

		if (!spell.Caster_->IsEnemy(myHero) && !myHero->IsValidTarget(spell.Caster_, 1200))
			return;
		if (!spell.Caster_->IsHero() || spell.Caster_ == nullptr)
			return;

		if (spell.Target_ != myHero)
			return;

		if (GSpellData->IsAutoAttack(spell.Data_))
			return;

		if (GSpellData->GetBaseDamage(spell.Data_) > 0.f)
		{

			auto slot = GSpellData->GetSlot(spell.Data_);
			if (slot != kSlotUnknown)
			{
				auto spelldmg = GDamage->GetSpellDamage(spell.Caster_, spell.Target_, slot) * 2;
				if (CountEnemiesInRange(Q->Range()) > 0 && (myHero->GetHealth() < spelldmg || myHero->HealthPercent() < 4))
				{
					if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
					{
						zhonyas->CastOnPlayer();
						return;
					}
					if ((zhonyas->IsOwned() && !zhonyas->IsReady() || !zhonyas->IsOwned() || !Usezhonyas->Enabled()) && ComboW->Enabled() && W->IsReady())
					{
						W->CastOnPlayer();
					}

				}
			}
		}
	}
	// 100% Gredits SoNiice
	if (UseWDodge->Enabled() && W->IsReady())
	{
		if (!spell.Caster_->IsEnemy(GEntityList->Player()))
			return;
		if (spell.Caster_->IsHero())
		{
			auto championName = const_cast<char*>(spell.Caster_->GetBaseSkinName());
			auto spellName = const_cast<char*>(GSpellData->GetSpellName(spell.Data_));

			for (auto champion : SpellDatabase::Champions)
			{
				if (strstr(champion.first, championName) != nullptr)
				{
					for (auto championSpell : champion.second.Spells)
					{
						if (strstr(championSpell.Name, spellName) != nullptr)
						{
							if (GetMenuBoolean(std::string(championSpell.Name)))
							{
								auto UseW = false;

								if (spell.Target_ != nullptr && spell.Target_ == myHero)
									UseW = true;

								if (spell.Target_ == nullptr)
								{
									auto currentSpell = GPluginSDK->CreateSpell2(championSpell.Slot, championSpell.SpellType, championSpell.Missile, championSpell.AoE, championSpell.Collisions);
									currentSpell->SetSkillshot(championSpell.Delay, championSpell.Radius, championSpell.Speed, championSpell.Range);

									AdvPredictionOutput pOutput;
									currentSpell->RunPrediction(myHero, championSpell.AoE, championSpell.Collisions, &pOutput);

									if (pOutput.HitChance >= kHitChanceHigh)
									{
										UseW = true;
									}
								}

								if (UseW)
								{
									GPluginSDK->DelayFunctionCall(championSpell.Delay - championSpell.Delay * 0.3, []
									{

										W->CastOnPosition(GGame->CursorPosition());
									});
								}
							}
						}
						break;
					}
				}
			}
		}
	}
}


/*if (E->IsReady() && AutoE->Enabled()&& !GSpellData->IsAutoAttack(spell.Data_))
{
auto epos = myHero->ServerPosition().Extend(target->GetPosition(), -E->Range());
if (myHero->IsValidTarget(spell.Caster_, 900))
{
for (auto spellName : dodgeSkills)
{
if (Contains(std::string(spell.Name_), spellName))
E->CastOnPosition(epos);
}
}
}
}*/

#pragma once
#include "Extensions.h"
#include "Combo.h"
#include "Burst.h"
#include "SpellDatabase.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (spell.Caster_ == myHero)
	{
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo)
		{
			processCombo(spell);
			return;
		}
		if (GetAsyncKeyState(Burst_b->GetInteger()))
		{
			processBurst(spell);
			return;
		}
		if (std::string(spell.Name_) == "RivenTriCleave")
		{
			LastQ = GGame->TickCount();
			if (Debug->Enabled())
			{
				GGame->PrintChat("LastQ");
			}
			return;
		}
		if (Contains(std::string(spell.Name_), "RivenBasicAttack"))
		{
			AutoAttack = true;
			return;
			//GPluginSDK->DelayFunctionCall(AADelay->GetInteger(), []()
			//{
			//	AutoAttack = false;
			//});
		}
		if (GSpellData->IsAutoAttack(spell.Data_))
		{
			AutoAttack = false;
			return;
		}
	}
	
	if (AutoE->Enabled() && E->IsReady())
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
								auto UseE = false;

								if (spell.Target_ != nullptr && spell.Target_ == myHero)
									UseE = true;

							/*	if (spell.Target_ == nullptr)
								{
									auto currentSpell = GPluginSDK->CreateSpell2(championSpell.Slot, championSpell.SpellType, championSpell.Missile, championSpell.AoE, championSpell.Collisions);
									currentSpell->SetSkillshot(championSpell.Delay, championSpell.Radius, championSpell.Speed, championSpell.Range);

									AdvPredictionOutput pOutput;
									currentSpell->RunPrediction(myHero, championSpell.AoE, championSpell.Collisions, &pOutput);

									if (pOutput.HitChance >= kHitChanceHigh)
									{
										UseE = true;
									}
								}

								if (UseE)
								{
									GPluginSDK->DelayFunctionCall(championSpell.Delay - championSpell.Delay * 0.3, []
									{
										auto epos = myHero->GetPosition() + (myHero->GetPosition() - spell.Caster_->GetPosition()).VectorNormalize() * 300;
										E->CastOnPosition(epos);
										return;
									});
								}*/
							}
						}
						break;
					}
				}
			}
		}
	}	
}
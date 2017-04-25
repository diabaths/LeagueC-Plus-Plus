#pragma once
#include "Extension.h"
#include "dodgeSkills.h"
#include "SpellDatabase.h"

PLUGIN_EVENT(void) OnProcessCast(CastedSpell const& spell)
{

	if (spell.Caster_ == myHero)
	{
		if (Contains(std::string(spell.Name_), "EkkoE"))
		{
			Reset();
		}
	}
	if (zhonyas->IsOwned() && zhonyas->IsReady() || R->IsReady())
	{
		
		if (!spell.Caster_->IsEnemy(myHero) && !myHero->IsValidTarget(spell.Caster_, W->Range()))
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
				auto spelldmg = GDamage->GetSpellDamage(spell.Caster_, spell.Target_, slot) *2;
				if (CountEnemiesInRange(W->Range()) > 0 && (myHero->GetHealth() < spelldmg || myHero->HealthPercent() < 2))
				{					
					if (Usezhonyas->Enabled() && zhonyas->IsOwned() && zhonyas->IsReady())
					{
						zhonyas->CastOnPlayer();
						return;
					}
					if ((zhonyas->IsOwned() && !zhonyas->IsReady() || !zhonyas->IsOwned() || !Usezhonyas->Enabled()) && Ultisave->Enabled() && R->IsReady())
					{
						R->CastOnPlayer();
						return;
					}
				}
			}
		}
	}
	// 100% Gredits SoNiice
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
							auto UseE = false;

							if (spell.Target_ != nullptr && spell.Target_ == myHero)
								UseE = true;

							if (spell.Target_ == nullptr)
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
								GPluginSDK->DelayFunctionCall(championSpell.Delay - championSpell.Delay * 0.3, [] {
									auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, Q->Range());

									auto epos = myHero->ServerPosition().Extend(Enemy->GetPosition(), -E->Range());

									E->CastOnPosition(epos);
								});
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

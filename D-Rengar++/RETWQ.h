#pragma once
#include "Extension.h"
#include "Items.h"
#include "Damage.h"
#include "smite.h"

inline void RETWQ(CastedSpell const& spell)
{
	if (spell.Target_ != nullptr && !spell.Target_->IsDead() && spell.Target_->IsHero() && spell.Target_->IsEnemy(myHero))
	{
		if (myHero->GetMana() != 4)
		{
			if (E->IsReady() && ComboE->Enabled() && !passiveup)
			{
				if (myHero->IsValidTarget(spell.Target_, E->Range()))
				{
					E->CastOnTarget(spell.Caster_, kHitChanceHigh);
				}
			}
			if (std::string(spell.Name_) == "RengarE") //E spell
			{
				if (haveitems() && !passiveup)
				{
					Tiamat_hydra(spell.Target_);
				}
			}
			if (std::string(spell.Name_) == "ItemTiamatCleave")
			{
				if (W->IsReady() && ComboW->Enabled() && myHero->IsValidTarget(spell.Target_, W->Range()))
				{
					W->CastOnPlayer();
				}
			}
			if (std::string(spell.Name_) == "RengarW") //E spell
			{
				if (Q->IsReady() && ComboQ->Enabled() && myHero->IsValidTarget(spell.Target_, Q->Range()))
				{
					Q->CastOnTarget(spell.Caster_);
				}
			}
		}
		if(myHero->GetMana() == 4)
		{
			
		}
	}
}

inline void RETWQ()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
	if (useYoumuu->Enabled())
	{
		if (UltiOn() && use_Youmuu())
		{
			GPluginSDK->DelayFunctionCall(300, []()
			{
				Youmuu->CastOnPlayer();
			});
		}
		if (myHero->IsValidTarget(Enemy, E->Range()) && use_Youmuu())
		{
			Youmuu->CastOnPlayer();
		}
	}
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		smitetarget(Enemy);

		if (myHero->GetMana() != 4)
		{
			if (ComboE->Enabled() && E->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, E->Range()) && !passiveup)
				{
					AdvPredictionOutput EPred;
					E->RunPrediction(Enemy, true, kCollidesWithYasuoWall | kCollidesWithMinions, &EPred);

					if (EPred.HitChance >= kHitChanceHigh)
					{
						E->CastOnUnit(Enemy);
					}
				}
			}
			if (haveitems() && !passiveup)
			{
				Tiamat_hydra(Enemy);
			}
			if (Ignite != nullptr)
			{
				if (UseIgnitecombo->Enabled() && Ignite->IsReady())
				{
					if (Enemy->IsValidTarget(myHero, 570))
					{
						if (Enemy->GetHealth() <= TotalDamage(Enemy))
						{
							Ignite->CastOnUnit(Enemy);
						}
					}
				}
			}
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				W->CastOnPlayer();
			}
			if (ComboQ->Enabled() && Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					Q->CastOnUnit(Enemy);
				}
			}
		}

		if (myHero->GetMana() == 4)
		{
			auto Magicdmg = myHero->TotalMagicDamage();
			auto Physicaldmg = myHero->TotalPhysicalDamage();
			if (ComboW->Enabled() && W->IsReady())
			{
				if (Magicdmg >Physicaldmg &&myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
				}
			}

			if (ComboQ->Enabled() && Q->IsReady())
			{
				if (GetDistance(myHero, Enemy) <= Q->Range() && myHero->IsValidTarget(Enemy, Q->Range()))
				{
					Q->CastOnUnit(Enemy);
				}
			}
			if (myHero->IsValidTarget(Enemy, E->Range()) && GetDistance(myHero, Enemy) > Q->Range() && GetDistance(myHero, Enemy) <= E->Range() && !passiveup)
			{
				if (ComboE->Enabled() && E->IsReady())
				{
					AdvPredictionOutput EPred;
					E->RunPrediction(Enemy, true, kCollidesWithYasuoWall | kCollidesWithMinions, &EPred);

					if (EPred.HitChance >= kHitChanceHigh)
					{
						E->CastOnUnit(Enemy);
					}
				}
			}
		}
	}
}
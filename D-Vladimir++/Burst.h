#pragma once
#include "Items.h"

inline void burst()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1800);
	if (Enemy == nullptr || Enemy->IsDead()) return;
	GOrbwalking->Orbwalk(Enemy, GGame->CursorPosition());
	if (Ignite != nullptr)
	{
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				Ignite->CastOnUnit(Enemy);
			}
		}
	}
	if (E->IsReady())
	{
		if (myHero->IsValidTarget(Enemy, 1750))
		{
			E->CastOnPlayer();
			return;
		}
		if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, 1750))
		{
			E->StartCharging();
		}
	}
	
		if (myHero->IsValidTarget(Enemy, 1300))
		{
			if (protobelt->IsOwned() && protobelt->IsReady())
			{
				if (Flash != nullptr && Flash->IsReady() && UseFlash->Enabled() && GetDistance(myHero, Enemy) > 600)
				{
					Flash->CastOnPosition(Enemy->GetPosition());
				}
			}
			if (!protobelt->IsOwned() || !protobelt->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, 800))
				{
					if (Flash != nullptr && Flash->IsReady() && UseFlash->Enabled() && GetDistance(myHero, Enemy) > 600)
					{
						Flash->CastOnPosition(Enemy->GetPosition());
					}
				}
			}
			if (protobelt->IsOwned() && protobelt->IsReady())
			{
				protobelt->CastOnPosition(Enemy->GetPosition());
			}
			if (R->IsReady())
			{
				AdvPredictionOutput RPred;
				R->RunPrediction(Enemy, true, kCollidesWithNothing, &RPred);
				if (myHero->IsValidTarget(Enemy, R->Range() + R->Radius()))
				{
					if (RPred.HitChance >= kHitChanceMedium)
					{
						R->CastOnPosition(RPred.CastPosition);
						return;
					}
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					Q->CastOnUnit(Enemy);
					return;
				}
			}

			if (E->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, E->Range() + 100))
				{
					E->CastOnPlayer();
					return;
				}
				if (myHero->HasBuff("VladimirE") && myHero->IsValidTarget(Enemy, E->Range()))
				{
					E->StartCharging();
				}
			}
		}
	}


inline void Burstonprocess(CastedSpell const& spell)
{
	if (spell.Target_ != nullptr && !spell.Target_->IsDead() && spell.Target_->IsHero() && spell.Target_->IsEnemy(myHero))
	{
		if (std::string(spell.Name_) == "VladimirE") //E spell
		{
			if (myHero->IsValidTarget(spell.Target_, 1300))
			{
				if (protobelt->IsOwned() && protobelt->IsReady())
				{
					if (Flash != nullptr && Flash->IsReady() && UseFlash->Enabled() && GetDistance(myHero, spell.Target_) > 600)
					{
						Flash->CastOnPosition(spell.Target_->GetPosition());
					}
				}
				if (!protobelt->IsOwned() || !protobelt->IsReady())
				{
					if (myHero->IsValidTarget(spell.Target_, 800))
					{
						if (Flash != nullptr && Flash->IsReady() && UseFlash->Enabled() && GetDistance(myHero, spell.Target_) > 600)
						{
							Flash->CastOnPosition(spell.Target_->GetPosition());
						}
					}
				}
				if (protobelt->IsOwned() && protobelt->IsReady())
				{
					protobelt->CastOnPosition(spell.Target_->GetPosition());
				}
			}
		}
		if (std::string(spell.Name_) == "SummonerFlash") //E spell
		{
			if (protobelt->IsOwned() && protobelt->IsReady())
			{
				protobelt->CastOnPosition(spell.Target_->GetPosition());
			}
		}
		if (std::string(spell.Name_) == "ItemsoFBoltSpellBase") //E spell
		{
			if(myHero->HasBuff("VladimirE"))
			{
				E->CastOnPlayer();
				return;
			}
			if (R->IsReady())
			{
				AdvPredictionOutput RPred;
				R->RunPrediction(spell.Target_, true, kCollidesWithNothing, &RPred);
				if (myHero->IsValidTarget(spell.Target_, R->Range() + R->Radius()))
				{
					if (RPred.HitChance >= kHitChanceMedium)
					{
						R->CastOnPosition(RPred.CastPosition);
						return;
					}
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(spell.Target_, Q->Range()))
				{
					Q->CastOnUnit(spell.Target_);
					return;
				}
			}
		}
		if (std::string(spell.Name_) == "VladimirHemoplague") //E spell
		{
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(spell.Target_, Q->Range()))
				{
					Q->CastOnUnit(spell.Target_);
					return;
				}
			}
		}
	}
}


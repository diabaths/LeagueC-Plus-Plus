#pragma once
#include "Spells.h"
#include "Items.h"
#include "Extensions.h"
#include "Ultilogic.h"


inline void Nidalee()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1500);
	if (Enemy == nullptr || Enemy->IsDead()) return;
	GGame->IssueOrder(myHero, kAttackUnit, GGame->CursorPosition());
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
	if (use_Youmuu())
	{
		_Youmuu(Enemy);
	}
	if (Flash != nullptr && UseFlash->Enabled())
	{
		if (myHero->IsValidTarget(Enemy, 600 + Q->Range()))
		{
			if (Enemy != nullptr && !Enemy->IsDead() && E->IsReady())
			{
				E->CastOnPosition(Enemy->GetPosition());
			}
			if (R->IsReady())
			{
				GPluginSDK->DelayFunctionCall(5, []()
				{
					R->CastOnPlayer();
				});
			}
			if (Flash->IsReady() && GetDistance(myHero, Enemy) > E->Range() + 100)
			{
				GPluginSDK->DelayFunctionCall(10, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						Flash->CastOnPosition(Enemy->GetPosition());
					}
				});
			}
			if (W->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, W->Range()))
				{
					GPluginSDK->DelayFunctionCall(25, []()
					{
						W->CastOnPlayer();
					});
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					GPluginSDK->DelayFunctionCall(35, []()
					{
						auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
						if (Enemy != nullptr && !Enemy->IsDead())
						{
							ModeQ(Enemy);
						}
					});
				}
			}
			if (R2->IsReady() && isR2() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				GPluginSDK->DelayFunctionCall(55, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					R2->CastOnTarget(Enemy,kHitChanceHigh);
				});
			}
			if (Q->IsReady())
			{
				GPluginSDK->DelayFunctionCall(56, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						ModeQ(Enemy);
					}
				});
			}
		}
	}
}

static void processNidaleeBurst(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 600);
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (spell.Target_ != nullptr && !spell.Target_->IsDead() && spell.Caster_ == myHero && spell.Target_->IsHero())
		{
			if (use_Youmuu())
			{
				_Youmuu(Enemy);
				return;
			}
			if (std::string(spell.Name_) == "ItemTiamatCleave")
			{
				if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
				}
				else if (!W->IsReady() && Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenFeint") //E spell
			{
				if (R->IsReady() && isR1())
				{
					R->CastOnPlayer();
					return;
				}

				if (W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
				{
					W->CastOnPlayer();
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenMartyr") //W spell
			{
				if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenTriCleave")
			{
				if (isR2() && R2->IsReady())
				{
					R2->CastOnTarget(Enemy, kHitChanceHigh);
					return;
				}

			}
			if (std::string(spell.Name_) == "RivenIzunaBlade")
			{
				if (!R2->IsReady() && Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
				}
			}
		}
	}
}

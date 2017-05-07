#pragma once
#include "Spells.h"
#include "Items.h"
#include "Extensions.h"
#include "Ultilogic.h"


inline void Burstshy()
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
			GPluginSDK->DelayFunctionCall(35, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					UseItems(Enemy);
				}
			});
			if (isR2() && R->IsReady() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				GPluginSDK->DelayFunctionCall(55, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						R2->CastOnTarget(Enemy, kHitChanceHigh);
					}
				});
			}
			if (Q->IsReady())
			{
				GPluginSDK->DelayFunctionCall(59, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						ModeQ(Enemy);
					}
				});
			}
			return;
		}
		if (Qstack < 2 && GGame->CurrentTick() - LastQ > 850)
		{
			ModeQ(Enemy);
		}
	}
	else if (!UseFlash->Enabled())
	{
		if (myHero->IsValidTarget(Enemy, 175 + Q->Range()) && Qstack == 0 && E->IsReady() && R->IsReady() && isR1() && W->IsReady())
		{
			if (Enemy != nullptr && !Enemy->IsDead() && E->IsReady())
			{
				E->CastOnPosition(Enemy->GetPosition());
			}
			if (R->IsReady())
			{
				GPluginSDK->DelayFunctionCall(1, []()
				{
					R->CastOnPlayer();
				});
			}
			if (W->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, W->Range()))
				{
					GPluginSDK->DelayFunctionCall(10, []()
					{
						W->CastOnPlayer();
					});
				}
			}
			GPluginSDK->DelayFunctionCall(25, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems() && Enemy != nullptr && !Enemy->IsDead())
				{
					UseItems(Enemy);
				}
			});
			if (isR2() && R->IsReady() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				GPluginSDK->DelayFunctionCall(45, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						R2->CastOnPosition(Enemy->GetPosition());
					}
				});
			}
			if (Q->IsReady())
			{
				GPluginSDK->DelayFunctionCall(49, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr && !Enemy->IsDead())
					{
						ModeQ(Enemy);
					}
				});
			}
			return;
		}

		if (myHero->IsValidTarget(Enemy, 780 + Q->Range()))
		{
			if (Qstack < 2 && GGame->CurrentTick() - LastQ >= 850)
			{
				ModeQ(Enemy);
			}
		}
	}
}


static void ShyBurstafter(IUnit* source, IUnit* target)
{

	if (target != nullptr && target->IsValidTarget() && !target->IsDead() && target->IsHero())
	{
		if (E->IsReady() && myHero->IsValidTarget(target, 325 + myHero->AttackRange() - 30))
		{
			E->CastOnPosition(target->ServerPosition());
			return;
		}
		if (R->IsReady() && isR1())
		{
			R->CastOnPlayer();
			return;
		}
		/*	if (Q->IsReady() && myHero->IsValidTarget(target, Q->Range()))
		{
		Q->CastOnUnit(target);
		GGame->PrintChat("Q-cast-after-shy");
		return;
		}*/
		if (W->IsReady() && myHero->IsValidTarget(target, W->Range()))
		{
			W->CastOnPlayer();
			return;
		}
		if (haveitems())
		{
			UseItems(target);
			return;
		}
		if (R2->IsReady() && isR2()&& myHero->IsValidTarget(target, R2->Range()))
		{
			R2->CastOnTarget(target,kHitChanceHigh);
			return;
		}
		if (!W->IsReady() && !R->IsReady() && Q->IsReady() && myHero->IsValidTarget(target, Q->Range()))
		{
			ModeQ(target);
		}
	}
}


static void processShyBurst(CastedSpell const& spell)
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
				if (R2->IsReady() && isR2() && myHero->IsValidTarget(Enemy, R2->Range()))
				{
					R2->CastOnPosition(Enemy->GetPosition());
					return;
				}
				if (!R->IsReady() && Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
					return;
				}
			}
			if (std::string(spell.Name_) == "RivenIzunaBlade")
			{
				if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
				{
					ModeQ(Enemy);
					AutoAttack = true;
				}
			}
		}
	}
}
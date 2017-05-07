#pragma once
#include "Spells.h"
#include "Items.h"
#include "Extensions.h"
#include "Ultilogic.h"

inline void Werhli()
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
		if (myHero->IsValidTarget(Enemy, 425 + E->Range()))
		{

			if (Enemy != nullptr &&  !Enemy->IsDead() && E->IsReady())
			{
				E->CastOnPosition(Enemy->GetPosition());
			}
			if (Enemy != nullptr &&  !Enemy->IsDead() && isR2() && R2->IsReady() && myHero->IsValidTarget(Enemy, R2->Range()))
			{
				GPluginSDK->DelayFunctionCall(5, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr &&  !Enemy->IsDead())
					{
						R2->CastOnPosition(Enemy->GetPosition());
					}
				});
			}

			if (Flash != nullptr && Flash->IsReady() && GetDistance(myHero, Enemy) > E->Range())
			{
				GPluginSDK->DelayFunctionCall(10, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (Enemy != nullptr &&  !Enemy->IsDead())
					{
						Flash->CastOnPosition(Enemy->GetPosition());
					}
				});
			}
			if (Enemy != nullptr &&  !Enemy->IsDead() && W->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, W->Range()))
				{
					GPluginSDK->DelayFunctionCall(15, []()
					{
						W->CastOnPlayer();
					});
				}
			}
			if (Q->IsReady())
			{
				if (myHero->IsValidTarget(Enemy, Q->Range()))
				{
					GPluginSDK->DelayFunctionCall(25, []()
					{
						auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
						if (Enemy != nullptr &&  !Enemy->IsDead())
						{
							ModeQ(Enemy);
						}
					});
				}
			}
			GPluginSDK->DelayFunctionCall(45, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					UseItems(Enemy);
				}
			});
			if (Q->IsReady() && Qstack < 2 && GGame->CurrentTick() - LastQ > 850)
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}
	}


	else if (!UseFlash->Enabled())
	{
		if (myHero->IsValidTarget(Enemy, 175 + Q->Range()) && Qstack == 0 && E->IsReady() && R->IsReady() && isR1() && W->IsReady())
		{
			if (myHero->IsValidTarget(Enemy, 100 + E->Range()))
			{
				if (Enemy != nullptr &&  !Enemy->IsDead() && E->IsReady())
				{
					E->CastOnPosition(Enemy->GetPosition());
				}
				if (isR2() && R2->IsReady() && myHero->IsValidTarget(Enemy, R2->Range()))
				{
					GPluginSDK->DelayFunctionCall(5, []()
					{
						auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
						if (Enemy != nullptr &&  !Enemy->IsDead())
						{
							R2->CastOnTarget(Enemy, kHitChanceHigh);
						}
					});
				}
				if (W->IsReady())
				{
					if (myHero->IsValidTarget(Enemy, W->Range()))
					{
						GPluginSDK->DelayFunctionCall(15, []()
						{
							W->CastOnPlayer();
						});
					}
				}
				if (Q->IsReady())
				{
					if (myHero->IsValidTarget(Enemy, Q->Range()))
					{
						GPluginSDK->DelayFunctionCall(20, []()
						{
							auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
							if (Enemy != nullptr &&  !Enemy->IsDead())
							{
								ModeQ(Enemy);
							}
						});
					}
				}
				GPluginSDK->DelayFunctionCall(30, []()
				{
					auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
					if (haveitems())
					{
						UseItems(Enemy);
					}
				});
				return;
			}

			if (myHero->IsValidTarget(Enemy, 780 + Q->Range()))
			{
				if (Q->IsReady() && Qstack < 2 && GGame->CurrentTick() - LastQ >= 850)
				{
					ModeQ(Enemy);
				}
			}
		}
	}
}

static void processWerhliBurst(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R2->Range());
	if (Enemy != nullptr && !Enemy->IsDead())
	{
		if (spell.Target_ != nullptr && !spell.Target_->IsDead() && spell.Caster_ == myHero)
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
				if (R2->IsReady() && isR2() && myHero->IsValidTarget(Enemy, R2->Range()))
				{
					R2->CastOnPosition(Enemy->GetPosition());
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
static void WerhliBurstafter(IUnit* source, IUnit* target)
{
	if (target != nullptr && target->IsValidTarget() && !target->IsDead() && target->IsHero())
	{
		if (E->IsReady() && myHero->IsValidTarget(target, R2->Range()))
		{
			E->CastOnPosition(target->ServerPosition());
			return;
		}
		if (R2->IsReady() && isR2() && myHero->IsValidTarget(target, R2->Range()))
		{
			R2->CastOnTarget(target, kHitChanceHigh);
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
		if (Q->IsReady() && myHero->IsValidTarget(target, Q->Range()))
		{
			ModeQ(target);
		}
	}
}
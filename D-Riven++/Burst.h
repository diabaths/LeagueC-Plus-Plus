#pragma once

#include "Spells.h"
#include "Extensions.h"
#include "Items.h"
#include "Ultilogic.h"

/*inline void Burst()
{
	//auto Enemy = GTargetSelector->GetFocusedTarget();
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
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
	_Youmuu(Enemy);
	if (E->IsReady() && R->IsReady() && W->IsReady() && !isR2())
	{
		if (myHero->IsValidTarget(Enemy, 325 + myHero->AttackRange() - 30))
		{
			E->CastOnPosition(Enemy->GetPosition());
			GPluginSDK->DelayFunctionCall(10, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				R2->CastOnPosition(Enemy->GetPosition());
			});
			GPluginSDK->DelayFunctionCall(60, []()
			{
				W->CastOnPlayer();
			});

			GPluginSDK->DelayFunctionCall(150, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (myHero->IsValidTarget(Enemy, Q->Range()))
					Q->CastOnPosition(Enemy->GetPosition());
			});

			return;
		}
	}
	else
	{
		if (W->IsReady() && myHero->IsValidTarget(Enemy, Wrange))
		{
			W->CastOnPlayer();
		}
	}
}*/
	
inline void Burst()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
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
	_Youmuu(Enemy);
	if (Flash != nullptr && Flash->IsReady() && UseFlash->Enabled())
	{
		if (myHero->IsValidTarget(Enemy, 600 + Q->Range()) && Qstack > 0 && E->IsReady() && W->IsReady())
		{
			E->CastOnPosition(Enemy->GetPosition());
			if (R->IsReady() && isR1())
			{
				GPluginSDK->DelayFunctionCall(10, []()
				{
					R->CastOnPlayer();
				});
			}
			GPluginSDK->DelayFunctionCall(50, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				Flash->CastOnPosition(Enemy->GetPosition());
			});
			GPluginSDK->DelayFunctionCall(61, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				Q->CastOnPosition(GGame->CursorPosition());
			});
			GPluginSDK->DelayFunctionCall(64, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					UseItems(Enemy);
				}
			});
			GPluginSDK->DelayFunctionCall(68, []()
			{
				W->CastOnPlayer();
			});
			GPluginSDK->DelayFunctionCall(71, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				R2->CastOnPosition(Enemy->GetPosition());
			});
			return;
		}
		if (Qstack < 2 && GGame->CurrentTick() - LastQ > 850)
		{
			Q->CastOnPosition(GGame->CursorPosition());
		}
	}
	else
	{
		if (myHero->IsValidTarget(Enemy, 175 + Q->Range()) && Qstack == 0 && E->IsReady() && R->IsReady() && isR1() && W->IsReady())
		{
			E->CastOnPosition(Enemy->GetPosition());
			GPluginSDK->DelayFunctionCall(10, []()
			{
				R->CastOnPlayer();
			});
			GPluginSDK->DelayFunctionCall(50, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				Q->CastOnPosition(Enemy->GetPosition());
			});
			GPluginSDK->DelayFunctionCall(61, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				if (haveitems())
				{
					UseItems(Enemy);
				}
			});
			GPluginSDK->DelayFunctionCall(62, []()
			{
				W->CastOnPlayer();
			});
			GPluginSDK->DelayFunctionCall(70, []()
			{
				auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
				R2->CastOnPosition(Enemy->GetPosition());
			});
			return;
		}
		if (myHero->IsValidTarget(Enemy, 780 + Q->Range()))
		{
			if (Qstack < 2 && GGame->CurrentTick() - LastQ >= 850)
			{
				Q->CastOnPosition(GGame->CursorPosition());
			}
		}
	}
	
}
static void afterattackBurst(IUnit* source, IUnit* target)
{
	if (target->IsHero())
	{
		if (haveitems())
		{
			UseItems(target);
		}
		if (R->IsReady() && isR2())
		{
			R2->CastOnPosition(target->GetPosition());
			return;
		}

		if (Q->IsReady() && myHero->IsValidTarget(target, Q->Range()))
		{
			Q->CastOnPosition(target->GetPosition());
			return;
		}

		if (W->IsReady() && myHero->IsValidTarget(target, W->Range()))
		{
			WLogic(target);
			return;
		}

		if (E->IsReady() && myHero->IsValidTarget(target, 325 + myHero->AttackRange() - 30))
		{
			EDash(target);
		}
	}
}
static void processBurst(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 600);
	if (spell.Data_ == nullptr) return;
	if (spell.Caster_ == myHero && spell.Target_ != nullptr && myHero->IsValidTarget(Enemy, 600) && spell.Target_->IsHero())
	{
		if (std::string(spell.Name_) == "ItemTiamatCleave")
		{
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				W->CastOnPlayer();
			}
			else if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				Q->CastOnUnit(Enemy);
				AutoAttack = true;
			}
		}
		if (std::string(spell.Name_) == "RivenMartyr")
		{
			if (ComboR2->Enabled() && R->IsReady() && myHero->HasBuff("RivenFengShuiEngine") && R2Logic(Enemy))
			{
				return;
			}
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				Q->CastOnUnit(Enemy);
				AutoAttack = true;
			}
		}
		/*if (std::string(spell.Name_) == "RivenFeint")
		{
			_Youmuu(Enemy);
			if (R->IsReady() && isR1())
			{
				R->CastOnPlayer();
				return;
			}
		}*/
		if (std::string(spell.Name_) == "RivenIzunaBlade")
		{
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				Q->CastOnPosition(Enemy->GetPosition());
				AutoAttack = true;
			}
		}
	}
}

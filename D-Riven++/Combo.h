#pragma once
#include "Spells.h"
#include "Extensions.h"
#include "Ultilogic.h"
#include "Items.h"

inline void Combo()
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (Ignite != nullptr)
	{
		if (UseIgnitecombo->Enabled() && Ignite->IsReady())
		{
			if (Enemy != nullptr && Enemy->IsValidTarget(myHero, 570))
			{
				if (Enemy->GetHealth() <= TotalDamage(Enemy))
				{
					Ignite->CastOnUnit(Enemy);
				}
			}
		}
	}
	if (Enemy !=nullptr && myHero->IsValidTarget(Enemy, 600) && ComboE->Enabled() && E->IsReady() && CanMoveMent(myHero) && GetDistance(myHero, Enemy) <= 650 &&
		GetDistance(myHero, Enemy) > myHero->AttackRange() + 100) //GetDistance(myHero, Enemy) > IsInAutoAttackRange(Enemy) + 100 )
	{
		if (Debug->Enabled())
		{
			GGame->PrintChat("E_COMBO");
		}
		EDash(Enemy);
	}
	_Youmuu(Enemy);
	if (Enemy != nullptr && ComboQ->Enabled() && Q->IsReady() && CanMoveMent(myHero) && Qstack == 0 &&
		GetDistance(myHero, Enemy) <= myHero->AttackRange() + Q->Range() &&
		GetDistance(myHero, Enemy) > myHero->AttackRange() + 50 && GGame->TickCount() - LastQ > 1100)
	{
		if (!myHero->IsDashing())
		{
			if (Debug->Enabled())
			{
				GGame->PrintChat("Q_COMBO");
			}
			AutoAttack = true;
			ModeQ(Enemy);
		}
	}

	if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
	{
		WLogic(Enemy);
	}
	if (haveitems())
	{
		UseItems(Enemy);
		return;
	}
	if (Enemy != nullptr  && R->IsReady())
	{
		if (Enemy->GetHealth() <TotalDamage(Enemy)*(DmgPercent->GetInteger()/100) && ComboR->Enabled()  && myHero->IsValidTarget(Enemy,500))
		{
			R1Logic(Enemy);
			return;
		}
	}
	if (Enemy != nullptr  && R2->IsReady())
	{
		if (ComboR2->Enabled() && myHero->HasBuff("RivenFengShuiEngine") && myHero->IsValidTarget(Enemy, R2->Range()) && R2->IsReady() && R2Logic(Enemy))
		{
		}
	}
}

/*static void processCombo(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 600);

	if (spell.Data_ == nullptr) return;
	if (spell.Caster_ == myHero && spell.Target_ != nullptr && myHero->IsValidTarget(Enemy, 600) && spell.Target_ ->IsHero())
	{
		if (std::string(spell.Name_) == "ItemTiamatCleave")
		{
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, Wrange))
			{
				W->CastOnPlayer();
			}
			else if (!AutoAttack && Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				Q->CastOnUnit(Enemy);
				AutoAttack = true;
			}
		}
		if (std::string(spell.Name_) == "RivenMartyr")
		{
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				Q->CastOnUnit(Enemy);
				AutoAttack = true;
			}
			else if (ComboR2->Enabled() && R->IsReady() && myHero->HasBuff("RivenFengShuiEngine") && R2Logic(Enemy))
			{
				return;
			}
		}
	}
}*/
static void processCombo(CastedSpell const& spell)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, R2->Range());

	if (spell.Data_ == nullptr) return;
	if (spell.Target_ != nullptr && spell.Caster_ == myHero && spell.Target_->IsHero())
	{
		if (std::string(spell.Name_) == "ItemTiamatCleave")
		{
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				//ModeQ(Enemy);
				AutoAttack = true;
				return;
			}
		}
		if (std::string(spell.Name_) == "RivenMartyr")
		{			
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400) && !myHero->IsWindingUp())
			{
				ModeQ(Enemy);
				AutoAttack = true;
			}
			else if (ComboR2->Enabled() && R->IsReady() && myHero->HasBuff("RivenFengShuiEngine") && R2Logic(Enemy))
			{
				return;
			}
		}
		if (std::string(spell.Name_) == "RivenFeint")
		{
			if (haveitems())
			{
				UseItems(Enemy);
				return;
			}
			if (Enemy != nullptr  && R->IsReady())
			{
				if (Enemy->GetHealth() <TotalDamage(Enemy)*(DmgPercent->GetInteger() / 100) && ComboR->Enabled() && myHero->IsValidTarget(Enemy, 500))
				{
					R1Logic(Enemy);
					return;
				}
			}
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400))
			{
				ModeQ(Enemy);
				AutoAttack = true;
				return;
			}
			if (ComboR2->Enabled() && R->IsReady() && myHero->HasBuff("RivenFengShuiEngine") && R2Logic(Enemy))
			{
				return;
			}
		}
		if (std::string(spell.Name_) == "RivenFengShuiEngine")
		{
			if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(Enemy, W->Range()))
			{
				W->CastOnPlayer();
				return;
			}
		}
		if (std::string(spell.Name_) == "RivenIzunaBlade" && Qstack ==2)
		{
			if (Q->IsReady() && myHero->IsValidTarget(Enemy, 400) && !myHero->IsWindingUp())
			{
				ModeQ(Enemy);
				AutoAttack = true;
			}
		}
	}
}

static void afterattackCombo(IUnit* source, IUnit* target)
{
	
	if (target != nullptr && myHero->IsValidTarget(target, 400))
	{		
		if (Q->IsReady() && myHero->IsValidTarget(target, 400))
		{
			ModeQ(target);
			AutoAttack = true;
			return;
		}

		if (ComboR2->Enabled() && R2->IsReady() && myHero->HasBuff("RivenFengShuiEngine") && Qstack == 2 && Q->IsReady() && R2Logic(target))
		{
			return;
		}

		if (ComboW->Enabled() && W->IsReady() && myHero->IsValidTarget(target,W->Range()))
		{
			WLogic(target);
			return;
		}

		if (ComboE->Enabled() && !Q->IsReady() && !W->IsReady() && E->IsReady() && myHero->IsValidTarget(target, 400))
		{
			EDash(target);
			
		}		
	}
}

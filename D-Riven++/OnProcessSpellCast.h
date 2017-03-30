#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& spell)
{
	auto target = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);
	if (spell.Caster_ == myHero && (GOrbwalking->GetOrbwalkingMode() == kModeMixed || GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger())))
	{
		if (target != nullptr && target->IsHero() && !target->IsDead())
		{
			if (Hydra->Enabled())
			{
				if (!AutoAttack)
				{
					Titanic(target);
					GOrbwalking->ResetAA();
				}
			}
			if (Q->IsReady() && ComboQ->Enabled() && (!W->IsReady() || !ComboW->Enabled()))
			{
				if (myHero->IsValidTarget(target, 385))
					if (_tiamat->Enabled() || RHydra->Enabled())
					{
						if (!AutoAttack)
						{
							Tiamat_hydra(target);
							GOrbwalking->ResetAA();
						}
					}
				if (Qstack == 1 && !AutoAttack)
				{
					if (target != nullptr && myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) + 75))
					{
						if (Debug->Enabled())
						{
							GGame->PrintChat("ONATTACK_1");
						}
						AutoAttack = true;
						Q->CastOnPosition(target->ServerPosition());
						
					}
				}
				if (Qstack == 2 && !AutoAttack)
				{
					if (myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) + 75))
					{
						if (Debug->Enabled())
						{
							GGame->PrintChat("ONATTACK_2");
						}
						AutoAttack = true;
						Q->CastOnPosition(target->ServerPosition());
					
					}
				}
				if (Qstack == 0 && !AutoAttack)
				{
					if (myHero->IsValidTarget(target, Q->Range() + IsInAutoAttackRange(target) + 75))
					{
						if (Debug->Enabled())
						{
							GGame->PrintChat("ONATTACK_3");
						}
						AutoAttack = true;
						Q->CastOnPosition(target->ServerPosition());
						
					}
				}
			}
		}
	}
	if (spell.Caster_ == myHero)
	{
		if (GetAsyncKeyState(Burst_b->GetInteger()) && std::string(spell.Name_) == "RivenFengShuiEngine")
		{
			if (target != nullptr && myHero->IsValidTarget(target, Q->Range()) && R2->IsReady())
			{
				R2->CastOnPosition(target->ServerPosition());
			}
		}
		if (std::string(spell.Name_) == "RivenTriCleave")
		{
			LastQ = GGame->CurrentTick();
			if (Debug->Enabled())
			{
				GGame->PrintChat("LastQ");
			}
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			if (Contains(std::string(spell.Name_), "RivenBasicAttack"))
			{
				AutoAttack = true;
				GPluginSDK->DelayFunctionCall(AADelay->GetInteger(), []()
				{
					AutoAttack = false;
				});
			}
		}
	}
	if (spell.Caster_->IsHero() && spell.Name_ != nullptr && spell.Caster_ != myHero && E->IsReady()
		&& spell.Target_ == myHero && AutoE->Enabled() && CanMoveMent(myHero) && !GSpellData->IsAutoAttack(spell.Data_))
	{
		auto epos = myHero->GetPosition() + (myHero->GetPosition() - target->GetPosition()).VectorNormalize() * 300;
		if (myHero->IsValidTarget(target, 900))
		{
			if (Contains(spell.Name_, "FizzPiercingStrike"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "HungeringStrike"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "YasuoDash"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "KatarinaRTrigger"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "KatarinaE"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "DariusR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "GarenQ"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "GarenR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "IreliaE"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "LeeSinR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "OlafE"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "RenektonW"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "RenektonPreExecute"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "RengarQ"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "VeigarR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "VolibearW"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(spell.Name_, "XenZhaoThrust3"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "TwitchEParticle"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "MonkeyKingSpinToWin"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "RengarPassiveBuffDash"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "TalonCutthroat"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(spell.Name_, "attack") && (spell.Caster_->HasBuff("BlueCardAttack") || spell.Caster_->HasBuff("GoldCardAttack") || spell.Caster_->HasBuff("RedCardAttack")))
			{
				E->CastOnPosition(epos);
			}
		}
	}
	/*if (std::string(args.Name_) == "RivenMartyr")
	{

	ResetW();
	if (Debug->Enabled())
	{
	GGame->PrintChat("reset_W:");
	}
	}
	if (std::string(args.Name_) == "RivenFeint")
	{
	GOrbwalking->ResetAA();
	if (Debug->Enabled())
	{
	GGame->PrintChat("reset_E:");
	}
	}
	if (std::string(args.Name_) == "RivenIzunaBlade")
	{
	ResetR2();
	if (Debug->Enabled())
	{
	GGame->PrintChat("reset_R:");
	}
	}*/
}

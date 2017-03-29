#pragma once
#include "Extensions.h"

PLUGIN_EVENT(void) OnProcessSpellCast(CastedSpell const& args)
{
	auto Enemy = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 900);

	if (args.Caster_ == myHero)
	{
		if (GetAsyncKeyState(Burst_b->GetInteger()) && std::string(args.Name_) == "RivenFengShuiEngine")
		{
			if (Enemy != nullptr && myHero->IsValidTarget(Enemy, Q->Range()) && R2->IsReady())
			{
				R2->CastOnPosition(Enemy->ServerPosition());
			}
		}
		if (GOrbwalking->GetOrbwalkingMode() == kModeCombo || GetAsyncKeyState(Burst_b->GetInteger()) || GOrbwalking->GetOrbwalkingMode() == kModeMixed)
		{
			if (std::string(args.Name_) == "RivenTriCleave")
			{
				LastQ = GGame->CurrentTick();
				if (Debug->Enabled())
				{
					GGame->PrintChat("LastQ");
				}
			}
		}
		if (Contains(std::string(args.Name_), "RivenBasicAttack"))
		{
			AutoAttack = true;
			GPluginSDK->DelayFunctionCall(AADelay->GetInteger(), []()
			{
				AutoAttack = false;
			});

		}
	}
	if (args.Caster_->IsHero() && args.Name_ != nullptr && args.Caster_ != myHero && E->IsReady()
		&& args.Target_ == myHero && AutoE->Enabled() && CanMoveMent(myHero) && !GSpellData->IsAutoAttack(args.Data_))
	{
		auto epos = myHero->GetPosition() + (myHero->GetPosition() - Enemy->GetPosition()).VectorNormalize() * 300;
		if (myHero->IsValidTarget(Enemy, 900))
		{
			if (Contains(args.Name_, "FizzPiercingStrike"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "HungeringStrike"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "YasuoDash"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "KatarinaRTrigger"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "KatarinaE"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "DariusR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "GarenQ"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "GarenR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "IreliaE"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "LeeSinR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "OlafE"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "RenektonW"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "RenektonPreExecute"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "RengarQ"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "VeigarR"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "VolibearW"))
			{
				E->CastOnPosition(epos);
			}

			if (Contains(args.Name_, "XenZhaoThrust3"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "TwitchEParticle"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "MonkeyKingSpinToWin"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "RengarPassiveBuffDash"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "TalonCutthroat"))
			{
				E->CastOnPosition(epos);
			}
			if (Contains(args.Name_, "attack") && (args.Caster_->HasBuff("BlueCardAttack") || args.Caster_->HasBuff("GoldCardAttack") || args.Caster_->HasBuff("RedCardAttack")))
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

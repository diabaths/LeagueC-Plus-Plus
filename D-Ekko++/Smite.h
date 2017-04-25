#pragma once
#include "Menu.h"
inline void smitestatus()
{
	keyDown = GetAsyncKeyState(smitekey->GetInteger()); //smite key

	if (GUtility->IsLeagueWindowFocused() && !GGame->IsChatOpen())
	{
		if (keyDown < 0)
		{
			if (SmiteDown == false)
			{
				if (smitejungle->GetInteger() == 0) { smitejungle->UpdateInteger(1); }
				else { smitejungle->UpdateInteger(0); }
				SmiteDown = true;
			}
		}
		else
		{
			SmiteDown = false;
		}
	}
}

inline void smitetarget()
{
	if (smite != nullptr)
	{
		if (!usesmitetarget->Enabled() || !smite->IsReady()) return;
		auto enemy = GTargetSelector->FindTarget(QuickestKill, SpellDamage, 1500);
		if (enemy != nullptr && myHero->IsValidTarget(enemy, 570))
		{
			auto Dmg = GDamage->GetSummonerSpellDamage(myHero, enemy, kSummonerSpellSmite);
			smite->CastOnUnit(enemy);
		}
	}
}

inline void Smiteuse()
{
	if (smite != nullptr && smite->IsReady())
	{
		auto minions = GEntityList->GetAllMinions(false, false, true);
		for (IUnit* minion : minions)
		{
			auto smitestage = usesmitejungle->GetInteger();
			if (smitestage == 0)
			{
				if (strstr(minion->GetObjectName(), "Blue") || strstr(minion->GetObjectName(), "Gromp")
					|| strstr(minion->GetObjectName(), "Murkwolf") || strstr(minion->GetObjectName(), "Razorbeak")
					|| strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Red")
					|| strstr(minion->GetObjectName(), "Krug") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
				}
			}
			if (smitestage == 1)
			{
				if (strstr(minion->GetObjectName(), "RiftHerald") || strstr(minion->GetObjectName(), "Dragon")
					|| strstr(minion->GetObjectName(), "Baron"))
				{
					auto Dmg = GDamage->GetSummonerSpellDamage(myHero, minion, kSummonerSpellSmite);
					if (minion != nullptr && !minion->IsDead() && minion->GetHealth() <= Dmg && myHero->IsValidTarget(minion, 570))
					{
						smite->CastOnUnit(minion);
					}
				}
			}
		}
	}
}


#pragma once
#include "Damage.h"
#include "Color.h"

int xOffset = 10;
int yOffset = 15;
int Width = 103;
int Height = 8;

PLUGIN_EVENT(void) OnRender()
{
	if (DrawReady->Enabled())
	{
		if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Wrange); }

		if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range()); }

		if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Wrange); }

		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range()); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), R->Range()); }
	}
	//100%  SoNiice code
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy->IsDead() || !enemy->IsVisible())
			continue;

		Vec3 worldToScreen;
		GGame->Projection(enemy->GetPosition(), &worldToScreen);


		if (Drawdmg->Enabled())
		{
			auto Damage =TotalDamage(enemy);
			auto currentPercentage = ceil(Damage / enemy->GetHealth() * 100);

			GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), currentPercentage >= 100 ? Vec4(255, 255, 0, 255) : Vec4(255, 255, 255, 255), currentPercentage >= 100 ? "Killable" : "%d (%.1f%%)", Damage, currentPercentage);
		}

		if (Drawhealthbar->Enabled()) //Damage.Healthbar"))
		{
			Vec2 barPos = Vec2();
			if (enemy->GetHPBarPosition(barPos))
			{
				auto Damage = TotalDamage(enemy);
				float percentHealthAfterDamage = max(0, enemy->GetHealth() - float(Damage)) / enemy->GetMaxHealth();
				float yPos = barPos.y + yOffset;
				float xPosDamage = (barPos.x + xOffset) + Width * percentHealthAfterDamage;
				float xPosCurrentHp = barPos.x + xOffset + Width * (enemy->GetHealth() / enemy->GetMaxHealth());
				if (!enemy->IsDead() && enemy->IsValidTarget())
				{
					float differenceInHP = xPosCurrentHp - xPosDamage;
					float pos1 = barPos.x + 9 + (107 * percentHealthAfterDamage);

					for (int i = 0; i < differenceInHP; i++)
					{
						GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), Color::Magenta().Get());
					}
					if (!enemy->IsVisible())
					{

					}
				}
			}
			/*auto Damage = TotalDamage(enemy);

			if (Damage > 0)
			{
				auto DamagePercentage = (enemy->GetHealth() - Damage) / enemy->GetMaxHealth();
				auto missingHealthPercentage = 100 - enemy->GetHealth() / enemy->GetMaxHealth() * 100;

				Vec2 barPosition;

				if (enemy->GetHPBarPosition(barPosition))
				{
					if (strcmp(enemy->ChampionName(), "XinZhao") == 0)
					{
						auto startPoint = Vec2(barPosition.x + 10 + DamagePercentage * 104, barPosition.y + 22);
						auto size = Vec2(104 - DamagePercentage * 104 - 104 * missingHealthPercentage / 100, 8.5f);
						//auto color = healthbarcolor->GetColor();
						GRender->DrawFilledBox(startPoint, size, Vec4(255, 239, 213, 255));
					}
					if (strcmp(enemy->ChampionName(), "XinZhao") != 0)
					{
						auto startPoint = Vec2(barPosition.x + 10 + DamagePercentage * 104, barPosition.y + 9);
						auto size = Vec2(104 - DamagePercentage * 104 - 104 * missingHealthPercentage / 100, 8.5f);
						//auto color = healthbarcolor->GetColor();
						GRender->DrawFilledBox(startPoint, size, Vec4(255, 239, 213, 255));
					}

				}
			}*/
		}
	}
}
 
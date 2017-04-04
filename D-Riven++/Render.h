#pragma once
#include "Damage.h"
#include "Color.h"

int xOffset = 10;
int yOffset = 15;
int Width = 103;
int Height = 8;

PLUGIN_EVENT(void) OnRender()
{	
	Vec4 color;
	Vec4 colorw;
	Vec4 colore;
	Vec4 colorr;
	Vec4 colordmg;
	Vec4 colorheal;
	qRangeColor->GetColor(&color);
	wRangeColor->GetColor(&colorw);
	eRangeColor->GetColor(&colore);
	rRangeColor->GetColor(&colorr);
	dmgRangeColor->GetColor(&colordmg);
	healRangeColor->GetColor(&colorheal);

	if (DrawReady->Enabled())
	{
		
		if (Q->IsReady() && DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, Q->Range()); }

		if (W->IsReady() && DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, Wrange); }

		if (E->IsReady() && DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, E->Range()); }

		if (R->IsReady() && DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range()); }
	}
	else
	{
		if (DrawQ->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, Q->Range()); }

		if (DrawW->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, Wrange); }

		if (DrawE->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, E->Range()); }

		if (DrawR->Enabled()) { GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range()); }
	}
	//100%  SoNiice code
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy->IsDead() || !enemy->IsVisible())
			continue;
		
		static IFont* pFont = nullptr;

		if (pFont == nullptr)
		{
			pFont = GRender->CreateFont("Rockwell", 16.f, kFontWeightNormal);
			pFont->SetOutline(true);
			pFont->SetLocationFlags(kFontLocationNormal);
		}
		/*Vec2 pos;
		if (GGame->Projection(GEntityList->Player()->GetPosition(), &pos))
		{
			if (R->IsReady() && myHero->IsValidTarget(enemy, 1200))
			{
				if (enemy->HealthPercent() <= DmgPercentmin->GetInteger())
				{
					std::string text = std::string("Ulti Will Disable");
					Vec4 clr = Vec4(250, 20, 3, 255);
					pFont->SetColor(clr);
					pFont->Render(pos.x, pos.y, text.c_str());
				}
				if (enemy->HealthPercent() >= DmgPercentmin->GetInteger() && enemy->GetHealth() < TotalDamage(enemy)*(DmgPercent->GetInteger() / 100))
				{
					std::string text = std::string("Ulti Will Enable");
					Vec4 clr = Vec4(3, 252, 19, 255);
					pFont->SetColor(clr);
					pFont->Render(pos.x, pos.y, text.c_str());
				}
			}
		}*/
		Vec3 worldToScreen;
		GGame->Projection(enemy->GetPosition(), &worldToScreen);


		if (Drawdmg->Enabled())
		{
			auto Damage =TotalDamage(enemy);
			auto currentPercentage = ceil(Damage / enemy->GetHealth() * 100);

			GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), currentPercentage >= 100 ? Vec4(255, 255, 0, 255) : colordmg, currentPercentage >= 100 ? "Killable" : "%d (%.1f%%)", Damage, currentPercentage);
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
						GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), colorheal);
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
 
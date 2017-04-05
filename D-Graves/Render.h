#pragma once
#include "Damage.h""

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
	Vec4 colorburst;
	BurstColor->GetColor(&colorburst);
	qRangeColor->GetColor(&color);
	wRangeColor->GetColor(&colorw);
	rRangeColor->GetColor(&colorr);
	dmgRangeColor->GetColor(&colordmg);
	if (DrawReady->Enabled())
	{	
		if (Q->IsReady() && R->IsReady() && E->IsReady() && DrawBurst->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorburst, Q->Range() - 300);
		}
		if (Q->IsReady() && DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, QRange->GetInteger());
		}

		if (W->IsReady() && DrawW->Enabled())
		{
		GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, W->Range());
		}

		if (R->IsReady() && DrawR->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range());
		}
	}
	else
	{
		if (DrawBurst->Enabled())
		{
		    GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorburst, Q->Range() - 300);
		}
		if (DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, QRange->GetInteger());
		}

		if (DrawW->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, W->Range());
		}

		if (DrawR->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range());
		}
	}
	for (auto enemy : GEntityList->GetAllHeros(false, true))
	{
		if (enemy->IsDead() || !enemy->IsVisible())
			continue;

		Vec3 worldToScreen;
		GGame->Projection(enemy->GetPosition(), &worldToScreen);


		if (Drawdmg->Enabled())
		{
			auto Damage = TotalDamage(enemy);
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
						GRender->DrawLine(Vec2(pos1 + i, yPos), Vec2(pos1 + i, yPos + Height), colordmg);
					}
					if (!enemy->IsVisible())
					{

					}
				}
			}
		}
	}
}
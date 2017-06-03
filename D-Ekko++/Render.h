#pragma once
#include "Extension.h"
#include "Damage.h"


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
	Vec4 colorrpos;
	qRangeColor->GetColor(&color);
	wRangeColor->GetColor(&colorw);
	eRangeColor->GetColor(&colore);
	rRangeColor->GetColor(&colorr);
	RposRangeColor->GetColor(&colorrpos);
	if (DrawSmite->Enabled())
	{
		if (smitejungle->Enabled())
		{
			Vec2 pos;
			if (GGame->Projection(myHero->GetPosition(), &pos))
			GRender->DrawTextW(Vec2(pos.x + 72, pos.y + 10), Vec4(0, 255, 0, 255), "SMITE: ON");
		}
		else {
			Vec2 pos;
			if (GGame->Projection(myHero->GetPosition(), &pos))
				GRender->DrawTextW(Vec2(pos.x + 72, pos.y + 10), Vec4(255, 0, 0, 255), "SMITE: OFF");
		}
	}
	if(Rpos !=nullptr && DrawRpos->Enabled())
	{
		GRender->DrawOutlinedCircle(Rpos->GetPosition(), colorrpos, R->Radius());
	}
	/*if (DrawCombomode->Enabled())
	{
		Vec3 worldToScreen;
		GGame->Projection(myHero->GetPosition(), &worldToScreen);

		if (mode == 0)
		{
			GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), Vec4(255, 255, 0, 255), "Combo:Q-R");
		}
		if (mode == 1)
		{
			GRender->DrawTextW(Vec2(worldToScreen.x, worldToScreen.y), Vec4(255, 255, 0, 255), "Combo:R-Q");
		}
	}*/
	if (DrawReady->Enabled())
	{
		if (Q->IsReady() && DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, Q->Range());
		}
		if (W->IsReady() && DrawW->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, W->Range());
		}
		if (E->IsReady() && DrawE->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, E->Range());
		}
		if (R->IsReady() && DrawR->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range());
		}
	}
	else
	{
		if (DrawQ->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), color, Q->Range());
		}
		if (DrawW->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorw, W->Range());
		}
		if (DrawE->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colore, E->Range());
		}
		if (DrawR->Enabled())
		{
			GRender->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), colorr, R->Range());
		}
	}
	
	if (Drawhealthbar->Enabled()) //Damage.Healthbar"))
	{
		for (auto enemy : GEntityList->GetAllHeros(false, true))
		{
			Vec4 colorheal;
			healRangeColor->GetColor(&colorheal);
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
		}
	}
}
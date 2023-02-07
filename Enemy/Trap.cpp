#include "Trap.h"
#include "EnemyBlack.h"
#include "../Stage.h"

namespace
{
	EnemyBlack* pEnemy;
	Stage* pStage;
}

//コンストラクタ
Trap::Trap(GameObject* parent)
	:GameObject(parent, "Trap")
{
}

//デストラクタ
Trap::~Trap()
{
}

//初期化
void Trap::Initialize()
{
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);
}

//更新
void Trap::Update()
{
}

//描画
void Trap::Draw()
{
}

//開放
void Trap::Release()
{
}

void Trap::SetTrap(int x, int y)
{
	pStage->SetType(x,y,3);
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//xが同じなら
		if ((*itr).first == x)
		{
			//yの方が小さいなら
			if ((*itr).second > y)
			{
				pos_.insert(itr,{ x,y });
				return;
			}
			//yも同じなら
			else if ((*itr).second == y)
			{
				return;
			}
		}
		//xのほうが小さくなったら
		else if ((*itr).first > x)
		{
			pos_.insert(itr, { x,y });
			return;
		}
	}
	pos_.push_back({x,y});
}

bool Trap::IsTrap(int x, int y)
{
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		if ((*itr).first == x)
		{
			if ((*itr).second == y)
			{
				pEnemy = (EnemyBlack*)FindObject("EnemyBlack");
				assert(pEnemy != nullptr);
				pEnemy->SetDirection(x, y);
				pStage->SetType(x, y, 0);
				pos_.erase(itr);

				return true;
			}
			else if ((*itr).second > y)
			{
				break;
			}
		}
		else if ((*itr).first > x)
		{
			break;
		}
	}
	return false;
}

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
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			map_[x][z] = false;
		}
	}
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
	map_[x][y] = true;
	pStage->SetType(x,y,3);
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//xが同じなら
		if ((*itr).first == x)
		{
			//yの方が小さいなら
			if ((*itr).second > y)
			{
				pos_.insert(--itr,{ x,y });
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
			pos_.insert(--itr, { x,y });
			return;
		}
	}
}

bool Trap::IsTrap(int x, int y)
{
	if (map_[x][y])
	{
		pEnemy = (EnemyBlack*)FindObject("EnemyBlack");
		assert(pEnemy != nullptr);
		pEnemy->SetDirection(x, y);
		map_[x][y] = false;
		pStage->SetType(x, y, 0);

		return true;
	}
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		if ((*itr).first == x)
		{
			if ((*itr).second == y)
			{

			}
			else if ((*itr).second > y)
			{

			}
		}
		else if ((*itr).first > x)
		{

		}
	}
	return false;
}

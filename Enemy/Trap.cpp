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

	//リストが空なら
	if (pos_.empty())
	{
		pos_.push_back({ x,y });
		return;
	}

	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//xが同じなら
		if ((*itr).first == x)
		{
			//リスト内のyのほうが大きくなったら差し込む
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
		//リスト内のxのほうが大きくなったら差し込む
		else if ((*itr).first > x)
		{
			pos_.insert(itr, { x,y });
			return;
		}
	}

	//リスト内のxとyの両方が小さいなら最後に入れる
	pos_.push_back({ x,y });
}

bool Trap::IsTrap(int x, int y)
{
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//xが同じなら
		if ((*itr).first == x)
		{
			//yが同じなら
			if ((*itr).second == y)
			{
				pEnemy = (EnemyBlack*)FindObject("EnemyBlack");
				assert(pEnemy != nullptr);
				pEnemy->SetDirection(x, y);
				pStage->SetType(x, y, 0);
				pos_.erase(itr);

				return true;
			}
			//リスト内のyのほうが大きくなったら抜ける
			else if ((*itr).second > y)
			{
				break;
			}
		}
		//リスト内のxのほうが大きくなったら抜ける
		else if ((*itr).first > x)
		{
			break;
		}
	}
	return false;
}

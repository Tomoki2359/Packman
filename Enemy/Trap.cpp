#include "Trap.h"
#include "EnemyBlack.h"

namespace
{
	EnemyBlack* pEnemy;
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

bool Trap::IsTrap(int x, int y)
{
	if (map_[x][y])
	{
		pEnemy = (EnemyBlack*)FindObject("EnemyBlack");
		assert(pEnemy != nullptr);
		pEnemy->SetDirection(x, y);
		map_[x][y] = false;
		isTrap_ = true;
		return true;
	}
	return false;
}

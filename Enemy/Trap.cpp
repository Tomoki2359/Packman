#include "Trap.h"
#include "EnemyBlack.h"

namespace
{
	EnemyBlack* pEnemy;
}
//�R���X�g���N�^
Trap::Trap(GameObject* parent)
	:GameObject(parent, "Trap")
{
}

//�f�X�g���N�^
Trap::~Trap()
{
}

//������
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

//�X�V
void Trap::Update()
{
}

//�`��
void Trap::Draw()
{
}

//�J��
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

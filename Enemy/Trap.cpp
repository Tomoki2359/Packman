#include "Trap.h"
#include "EnemyBlack.h"
#include "../Stage.h"

namespace
{
	EnemyBlack* pEnemy;
	Stage* pStage;
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
	pStage = (Stage*)FindObject("Stage");
	assert(pStage != nullptr);

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

void Trap::SetTrap(int x, int y)
{
	map_[x][y] = true;
	pStage->SetType(x,y,3);
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//x�������Ȃ�
		if ((*itr).first == x)
		{
			//y�̕����������Ȃ�
			if ((*itr).second > y)
			{
				pos_.insert(--itr,{ x,y });
				return;
			}
			//y�������Ȃ�
			else if ((*itr).second == y)
			{
				return;
			}
		}
		//x�̂ق����������Ȃ�����
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

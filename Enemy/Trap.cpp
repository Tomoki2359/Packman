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
	pStage->SetType(x,y,3);
	for (auto itr = pos_.begin(); itr != pos_.end(); itr++)
	{
		//x�������Ȃ�
		if ((*itr).first == x)
		{
			//y�̕����������Ȃ�
			if ((*itr).second > y)
			{
				pos_.insert(itr,{ x,y });
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

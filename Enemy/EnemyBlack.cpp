#include "EnemyBlack.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"
#include "Trap.h"
#include "../Engine/Global.h"
#include <random>

//�R���X�g���N�^
EnemyBlack::EnemyBlack(GameObject* parent)
    :Enemy(parent, "EnemyBlack"),maxCounter_(30)
{
    pDij_ = new Dijkstra();
}

//�f�X�g���N�^
EnemyBlack::~EnemyBlack()
{
    SAFE_DELETE(pDij_);
}

int EnemyBlack::EnemyMove()
{
    //��苗���i�񂾂�g���b�v��u��
    moveCounter_ -= pMove->GetSpeed();
    if (moveCounter_ <= 0)
    {
        pTrap_->SetTrap((int)transform_.position_.x, (int)transform_.position_.z);
        moveCounter_ = maxCounter_ - (rand() % 15);
    }

    //0�ȏ�̎��̓g���b�v�𓥂�ł�����
    if (dir.first > 0)
    {
        pMove->SetSpeed(0.35f);
        move = pDij_->GetDijkstra(XMFLOAT3{(float)dir.first,0.0f,(float)dir.second}, transform_.position_, pStage);
        //�ړI�n�ɓ���������
        if ((int)(transform_.position_.x) == dir.first && (int)(transform_.position_.z) == dir.second)
        {
            dir.first = -1;
        }
        return move;
    }
    else
    {
        pMove->SetSpeed(0.1f);
        movecounter_--;
        if (movecounter_ < 0)
        {
            movecounter_ = 10;
            move = pDij_->RandamMoveDirection(transform_.position_, pStage, pMove->GetSpeed(), move);
        }
        return move;
    }

    //return pAst_->GetAster(transform_.position_, pPlayer_->GetPosition(), pStage);
}

void EnemyBlack::Init()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("EnemyBlack.fbx");
    assert(hModel_ >= 0);

    pTrap_ = (Trap*)FindObject("Trap");
    assert(pTrap_ != nullptr);
    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
    pTrap_->SetTrap((int)transform_.position_.x,(int)transform_.position_.z);
    moveCounter_ = maxCounter_ - (rand() % 15);
    move = PREVIOUS_MOVE;
    dir.first = -1.0f;
    dir.second = -1.0f;
    movecounter_ = 5;
}

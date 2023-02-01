#include "EnemyRed.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"
#include "../Aster.h"

//�R���X�g���N�^
EnemyRed::EnemyRed(GameObject* parent)
    :Enemy(parent, "EnemyRed")
{
    pDij_ = new Dijkstra();
    pAst_ = new Aster();
}

//�f�X�g���N�^
EnemyRed::~EnemyRed()
{
}

int EnemyRed::EnemyMove()
{
    
    return pDij_->GetDijkstra(pPlayer_->GetPosition(), transform_.position_,pStage);
    //return pAst_->GetAster(transform_.position_, pPlayer_->GetPosition(), pStage);
}

void EnemyRed::Init()
{
    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
}

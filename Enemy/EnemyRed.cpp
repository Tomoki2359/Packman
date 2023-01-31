#include "EnemyRed.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"

//�R���X�g���N�^
EnemyRed::EnemyRed(GameObject* parent)
    :Enemy(parent, "EnemyRed")
{
    pDij_ = new Dijkstra();
}

//�f�X�g���N�^
EnemyRed::~EnemyRed()
{
}

int EnemyRed::EnemyMove()
{
    
    return pDij_->GetDijkstra(transform_.position_, pPlayer_->GetPosition(),pStage);
}
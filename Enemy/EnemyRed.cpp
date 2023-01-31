#include "EnemyRed.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"

//コンストラクタ
EnemyRed::EnemyRed(GameObject* parent)
    :Enemy(parent, "EnemyRed")
{
    pDij_ = new Dijkstra();
}

//デストラクタ
EnemyRed::~EnemyRed()
{
}

int EnemyRed::EnemyMove()
{
    
    return pDij_->GetDijkstra(transform_.position_, pPlayer_->GetPosition(),pStage);
}
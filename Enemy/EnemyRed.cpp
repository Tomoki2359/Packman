#include "EnemyRed.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"
#include "../Engine/Global.h"

//コンストラクタ
EnemyRed::EnemyRed(GameObject* parent)
    :Enemy(parent, "EnemyRed")
{
    pDij_ = new Dijkstra();
}

//デストラクタ
EnemyRed::~EnemyRed()
{
    SAFE_DELETE(pDij_);
}

int EnemyRed::EnemyMove()
{
    
    return pDij_->GetDijkstra(pPlayer_->GetPosition(), transform_.position_,pStage);
}

void EnemyRed::Init()
{
    //モデルデータのロード
    hModel_ = Model::Load("EnemyRed.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
    pMove->SetSpeed(0.15f);
}

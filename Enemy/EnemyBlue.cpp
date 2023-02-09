#include "EnemyBlue.h"
#include "EnemyBlue.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"
#include "../Engine/Global.h"

//コンストラクタ
EnemyBlue::EnemyBlue(GameObject* parent)
    :Enemy(parent, "EnemyBlue")
{
    pDij_ = new Dijkstra();
}

//デストラクタ
EnemyBlue::~EnemyBlue()
{
    SAFE_DELETE(pDij_);
}

int EnemyBlue::EnemyMove()
{
    movecounter_ -= pMove->GetSpeed();
    float x = (pPlayer_->GetPosition().x - transform_.position_.x);
    float z = (pPlayer_->GetPosition().z - transform_.position_.z);
    float d = sqrt((x * x) + (z * z));
    if (d < 3)
    {
        isDiscovery_ = true;
        dir.first = (int)pPlayer_->GetPosition().x;
        dir.second = (int)pPlayer_->GetPosition().z;
    }
    if (isDiscovery_)
    {
        move = pDij_->GetDijkstra(XMFLOAT3{ dir.first,0.0f,dir.second }, transform_.position_, pStage);
        //目的地に到着したら
        if ((int)transform_.position_.x == (int)dir.first && (int)transform_.position_.z == (int)dir.second)
        {
            isDiscovery_ = false;
        }
    }
    else if (movecounter_ < 0)
    {
        movecounter_ = 1;
        move = pDij_->RandamMoveDirection(transform_.position_, pStage, pMove->GetSpeed(), move);
    }
    return move;
    //return pDij_->GetDijkstra(pPlayer_->GetPosition(), transform_.position_, pStage);
}

void EnemyBlue::Init()
{
    //モデルデータのロード
    hModel_ = Model::Load("EnemyBlue.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
    pMove->SetSpeed(0.15f);
    move = PREVIOUS_MOVE;
    movecounter_ = 1;
}

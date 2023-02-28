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
    XMFLOAT3 p = pPlayer_->GetPosition();
    float x = (p.x - transform_.position_.x);
    float z = (p.z - transform_.position_.z);
    float d = sqrt((x * x) + (z * z));  //プレイヤーとの距離

    XMVECTOR vp = XMLoadFloat3(&p);
    XMVECTOR ve = XMLoadFloat3(&transform_.position_);
    XMVECTOR vdot = XMVector3Dot(vp, ve);

    //基準となる視野
    XMVECTOR enemyView_ = { 0,0,1,0 };
    //transform_.rotate_.yの値に合わせてＹ軸回転させる行列
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //目線を回転
    enemyView_ = XMVector3Normalize(XMVector3TransformCoord(enemyView_, mRotate));    //戦車の向きに合わせて回転

    //プレイヤーの方向
    XMVECTOR vmove = vp - ve;

    //角度を求めるために長さを１にする(正規化)
    vmove = XMVector3Normalize(vmove);

    //frontとmoveの内積を求める
    XMVECTOR vecDot = XMVector3Dot(enemyView_, vmove);
    float dot = XMVectorGetX(vecDot);

    //向いてる角度を求める(ラジアン)
    float angle = acos(dot);

    //角度に変換
    float a = angle * 180.0f / 3.14f;
    if (d < 10.0f)
    {
        //aが-30度~30度なら(視野)
        if (-30 <= a && a <= 30)
        {
            isDiscovery_ = true;
            dir.first = (int)pPlayer_->GetPosition().x;
            dir.second = (int)pPlayer_->GetPosition().z;
        }
    }
    //発見したら
    if (isDiscovery_)
    {
        move = pDij_->GetDijkstra(XMFLOAT3{ dir.first,0.0f,dir.second }, transform_.position_, pStage);
        //目的地に到着したら
        if ((int)transform_.position_.x == (int)dir.first && (int)transform_.position_.z == (int)dir.second)
        {
            isDiscovery_ = false;
        }
    }
    //movecounter_が0になったら後ろ以外のランダムに移動
    else if (movecounter_ < 0)
    {
        movecounter_ = 1;
        move = pDij_->RandamMoveDirection(transform_.position_, pStage, move);
    }
    return move;
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

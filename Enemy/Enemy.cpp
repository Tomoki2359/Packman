#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
}

Enemy::Enemy(GameObject* parent, std::string name)
    : GameObject(parent, name){
}

//デストラクタ
Enemy::~Enemy()
{
}

//初期化
void Enemy::Initialize()
{
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pPlayer_ = (Player*)FindObject("Player");
    assert(pPlayer_ != nullptr);

    pMove = new Move(pStage);

    Init();

}

//更新
void Enemy::Update()
{
    //移動前の位置ベクトル
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    pMove->MoveSelect(EnemyMove(), &transform_.position_);

    //現在の位置ベクトル
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //今回の移動ベクトル
    XMVECTOR move = nowPosition - prevPosition;

    //移動ベクトルの長さを図る
    XMVECTOR length = XMVector3Length(move);

    //0.1以上移動してたなら回転処理
    if (XMVectorGetX(length) > 0.1f)
    {

        //角度を求めるために長さを１にする(正規化)
        move = XMVector3Normalize(move);

        //基準となる奥行きベクトル
        XMVECTOR front = { 0,0,1,0 };

        //frontとmoveの内積を求める
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //向いてる角度を求める(ラジアン)
        float angle = acos(dot);

        //frontとmoveの外積
        XMVECTOR cross = XMVector3Cross(front, move);

        //外積の結果のYがマイナス　＝　下向き　＝　左に進んでる
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //その分回転させる
        transform_.rotate_.y = angle * 180.0f / 3.14;
    }

    ////壁との衝突判定
    //int checkX, checkZ;

    ////右
    //checkX = (int)(transform_.position_.x + 0.3f);
    //checkZ = (int)(transform_.position_.z);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    //XMStoreFloat3(&transform_.position_, prevPosition);
    //    transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    //}

    ////左
    //checkX = (int)(transform_.position_.x - 0.3f);
    //checkZ = (int)(transform_.position_.z);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    //XMStoreFloat3(&transform_.position_, prevPosition);
    //    transform_.position_.x = (float)((int)(transform_.position_.x - 0.5f)) + 0.3f;
    //}

    ////上
    //checkX = (int)(transform_.position_.x);
    //checkZ = (int)(transform_.position_.z + 0.3f);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    XMStoreFloat3(&transform_.position_, prevPosition);
    //}

    ////下
    //checkX = (int)(transform_.position_.x);
    //checkZ = (int)(transform_.position_.z - 0.3f);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    XMStoreFloat3(&transform_.position_, prevPosition);
    //}

    if (pStage->IsWall((int)transform_.position_.x, (int)transform_.position_.z))
    {
        XMStoreFloat3(&transform_.position_, prevPosition);
    }
    /*
    if (pStage->IsWall((int)transform_.position_.x, (int)transform_.position_.z))
    {
        XMStoreFloat3(&transform_.position_, prevPosition);
    }*/
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Enemy::Release()
{
    SAFE_DELETE(pMove);
}
#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Global.h"
//コンストラクタ
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),move_(-1)
{
}

//デストラクタ
Player::~Player()
{
}

//初期化
void Player::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("Pacman.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 1.5f;
    transform_.position_.z = 1.5f;

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pMove = new Move();

}

//更新
void Player::Update()
{
    //移動前の位置ベクトル
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    if (Input::IsKey(DIK_UP))
    {
        //何らかの処理
        move_ = PREVIOUS_MOVE;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        //何らかの処理
        move_ = BACK_MOVE;
    }
    if (Input::IsKey(DIK_LEFT))
    {
        //何らかの処理
        move_ = LEFT_MOVE;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        //何らかの処理
        move_ = RIGHT_MOVE;
    }

    pMove->MoveSelect(move_, &transform_.position_);

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
        transform_.rotate_.y = angle * 180.0f / 3, 14;
    }

    //壁との衝突判定
    int checkX, checkZ;

    //右
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)(transform_.position_.z);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    }

    //左
    checkX = (int)(transform_.position_.x - 0.3f);
    checkZ = (int)(transform_.position_.z);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x - 0.5f)) + 0.3f;
    }

    //上
    checkX = (int)(transform_.position_.x);
    checkZ = (int)(transform_.position_.z + 0.3f);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        XMStoreFloat3(&transform_.position_, prevPosition);
    }

    //下
    checkX = (int)(transform_.position_.x);
    checkZ = (int)(transform_.position_.z - 0.3f);
    if (pStage->IsWall((int)checkX, (int)checkZ))
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
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
    SAFE_DELETE(pMove);
}

//void Player::PreviousMove()
//{
//    transform_.position_.z += speed_;
//}
//
//void Player::BackMove()
//{
//    transform_.position_.z -= speed_;
//}
//
//void Player::LeftMove()
//{
//    transform_.position_.x -= speed_;
//}
//
//void Player::RightMove()
//{
//    transform_.position_.x += speed_;
//}

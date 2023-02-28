#include "Enemy.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Engine/Global.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
    :GameObject(parent, "Enemy"), hModel_(-1)
{
}

Enemy::Enemy(GameObject* parent, std::string name)
    : GameObject(parent, name){
}

//�f�X�g���N�^
Enemy::~Enemy()
{
}

//������
void Enemy::Initialize()
{
    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pPlayer_ = (Player*)FindObject("Player");
    assert(pPlayer_ != nullptr);

    pMove = new Move(pStage);

    Init();

}

//�X�V
void Enemy::Update()
{
    //�ړ��O�̈ʒu�x�N�g��
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    pMove->MoveSelect(EnemyMove(), &transform_.position_);

    //���݂̈ʒu�x�N�g��
    XMVECTOR nowPosition = XMLoadFloat3(&transform_.position_);

    //����̈ړ��x�N�g��
    XMVECTOR move = nowPosition - prevPosition;

    //�ړ��x�N�g���̒�����}��
    XMVECTOR length = XMVector3Length(move);

    //0.1�ȏ�ړ����Ă��Ȃ��]����
    if (XMVectorGetX(length) > 0.1f)
    {

        //�p�x�����߂邽�߂ɒ������P�ɂ���(���K��)
        move = XMVector3Normalize(move);

        //��ƂȂ鉜�s���x�N�g��
        XMVECTOR front = { 0,0,1,0 };

        //front��move�̓��ς����߂�
        XMVECTOR vecDot = XMVector3Dot(front, move);
        float dot = XMVectorGetX(vecDot);

        //�����Ă�p�x�����߂�(���W�A��)
        float angle = acos(dot);

        //front��move�̊O��
        XMVECTOR cross = XMVector3Cross(front, move);

        //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
        if (XMVectorGetY(cross) < 0)
        {
            angle *= -1;
        }

        //���̕���]������
        transform_.rotate_.y = angle * 180.0f / 3.14;
    }

    ////�ǂƂ̏Փ˔���
    //int checkX, checkZ;

    ////�E
    //checkX = (int)(transform_.position_.x + 0.3f);
    //checkZ = (int)(transform_.position_.z);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    //XMStoreFloat3(&transform_.position_, prevPosition);
    //    transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    //}

    ////��
    //checkX = (int)(transform_.position_.x - 0.3f);
    //checkZ = (int)(transform_.position_.z);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    //XMStoreFloat3(&transform_.position_, prevPosition);
    //    transform_.position_.x = (float)((int)(transform_.position_.x - 0.5f)) + 0.3f;
    //}

    ////��
    //checkX = (int)(transform_.position_.x);
    //checkZ = (int)(transform_.position_.z + 0.3f);
    //if (pStage->IsWall((int)checkX, (int)checkZ))
    //{
    //    XMStoreFloat3(&transform_.position_, prevPosition);
    //}

    ////��
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

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Enemy::Release()
{
    SAFE_DELETE(pMove);
}
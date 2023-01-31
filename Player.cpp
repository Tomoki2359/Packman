#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Global.h"
//�R���X�g���N�^
Player::Player(GameObject* parent)
    :GameObject(parent, "Player"), hModel_(-1),move_(-1)
{
}

//�f�X�g���N�^
Player::~Player()
{
}

//������
void Player::Initialize()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("Pacman.fbx");
    assert(hModel_ >= 0);
    transform_.position_.x = 1.5f;
    transform_.position_.z = 1.5f;

    pStage = (Stage*)FindObject("Stage");
    assert(pStage != nullptr);

    pMove = new Move();

}

//�X�V
void Player::Update()
{
    //�ړ��O�̈ʒu�x�N�g��
    XMVECTOR prevPosition = XMLoadFloat3(&transform_.position_);

    if (Input::IsKey(DIK_UP))
    {
        //���炩�̏���
        move_ = PREVIOUS_MOVE;
    }
    if (Input::IsKey(DIK_DOWN))
    {
        //���炩�̏���
        move_ = BACK_MOVE;
    }
    if (Input::IsKey(DIK_LEFT))
    {
        //���炩�̏���
        move_ = LEFT_MOVE;
    }
    if (Input::IsKey(DIK_RIGHT))
    {
        //���炩�̏���
        move_ = RIGHT_MOVE;
    }

    pMove->MoveSelect(move_, &transform_.position_);

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
        transform_.rotate_.y = angle * 180.0f / 3, 14;
    }

    //�ǂƂ̏Փ˔���
    int checkX, checkZ;

    //�E
    checkX = (int)(transform_.position_.x + 0.3f);
    checkZ = (int)(transform_.position_.z);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x + 0.5f)) - 0.3f;
    }

    //��
    checkX = (int)(transform_.position_.x - 0.3f);
    checkZ = (int)(transform_.position_.z);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        //XMStoreFloat3(&transform_.position_, prevPosition);
        transform_.position_.x = (float)((int)(transform_.position_.x - 0.5f)) + 0.3f;
    }

    //��
    checkX = (int)(transform_.position_.x);
    checkZ = (int)(transform_.position_.z + 0.3f);
    if (pStage->IsWall((int)checkX, (int)checkZ))
    {
        XMStoreFloat3(&transform_.position_, prevPosition);
    }

    //��
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

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
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

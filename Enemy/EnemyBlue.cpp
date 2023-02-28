#include "EnemyBlue.h"
#include "EnemyBlue.h"
#include "../Engine/Model.h"
#include "../Engine/Input.h"
#include "../Dijkstra.h"
#include "../Engine/Global.h"

//�R���X�g���N�^
EnemyBlue::EnemyBlue(GameObject* parent)
    :Enemy(parent, "EnemyBlue")
{
    pDij_ = new Dijkstra();
}

//�f�X�g���N�^
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
    float d = sqrt((x * x) + (z * z));  //�v���C���[�Ƃ̋���

    XMVECTOR vp = XMLoadFloat3(&p);
    XMVECTOR ve = XMLoadFloat3(&transform_.position_);
    XMVECTOR vdot = XMVector3Dot(vp, ve);

    //��ƂȂ鎋��
    XMVECTOR enemyView_ = { 0,0,1,0 };
    //transform_.rotate_.y�̒l�ɍ��킹�Ăx����]������s��
    XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));

    //�ڐ�����]
    enemyView_ = XMVector3Normalize(XMVector3TransformCoord(enemyView_, mRotate));    //��Ԃ̌����ɍ��킹�ĉ�]

    //�v���C���[�̕���
    XMVECTOR vmove = vp - ve;

    //�p�x�����߂邽�߂ɒ������P�ɂ���(���K��)
    vmove = XMVector3Normalize(vmove);

    //front��move�̓��ς����߂�
    XMVECTOR vecDot = XMVector3Dot(enemyView_, vmove);
    float dot = XMVectorGetX(vecDot);

    //�����Ă�p�x�����߂�(���W�A��)
    float angle = acos(dot);

    //�p�x�ɕϊ�
    float a = angle * 180.0f / 3.14f;
    if (d < 10.0f)
    {
        //a��-30�x~30�x�Ȃ�(����)
        if (-30 <= a && a <= 30)
        {
            isDiscovery_ = true;
            dir.first = (int)pPlayer_->GetPosition().x;
            dir.second = (int)pPlayer_->GetPosition().z;
        }
    }
    //����������
    if (isDiscovery_)
    {
        move = pDij_->GetDijkstra(XMFLOAT3{ dir.first,0.0f,dir.second }, transform_.position_, pStage);
        //�ړI�n�ɓ���������
        if ((int)transform_.position_.x == (int)dir.first && (int)transform_.position_.z == (int)dir.second)
        {
            isDiscovery_ = false;
        }
    }
    //movecounter_��0�ɂȂ�������ȊO�̃����_���Ɉړ�
    else if (movecounter_ < 0)
    {
        movecounter_ = 1;
        move = pDij_->RandamMoveDirection(transform_.position_, pStage, move);
    }
    return move;
}

void EnemyBlue::Init()
{
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("EnemyBlue.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
    pMove->SetSpeed(0.15f);
    move = PREVIOUS_MOVE;
    movecounter_ = 1;
}

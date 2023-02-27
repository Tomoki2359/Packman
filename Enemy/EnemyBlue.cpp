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

    //��ƂȂ鉜�s���x�N�g��
    XMVECTOR front = { 0,0,1,0 };

    //����̈ړ��x�N�g��
    XMVECTOR vmove = vp - ve;

    //�p�x�����߂邽�߂ɒ������P�ɂ���(���K��)
    vmove = XMVector3Normalize(vmove);

    //front��move�̓��ς����߂�
    XMVECTOR vecDot = XMVector3Dot(front, vmove);
    float dot = XMVectorGetX(vecDot);

    //�����Ă�p�x�����߂�(���W�A��)
    float angle = acos(dot);

    //front��move�̊O��
    XMVECTOR cross = XMVector3Cross(front, vmove);

    //�O�ς̌��ʂ�Y���}�C�i�X�@���@�������@���@���ɐi��ł�
    if (XMVectorGetY(cross) < 0)
    {
        angle *= -1;
    }

    //float angle = acos(XMVectorGetX(dot));
    float a = angle * 180.0f / 3.14f;
    if (d < 10.0f)
    {

        
        if (transform_.rotate_.y - 30 <= a && a <= transform_.rotate_.y + 30)
        {
            isDiscovery_ = true;
            dir.first = (int)pPlayer_->GetPosition().x;
            dir.second = (int)pPlayer_->GetPosition().z;
        }
    }
    if (isDiscovery_)
    {
        move = pDij_->GetDijkstra(XMFLOAT3{ dir.first,0.0f,dir.second }, transform_.position_, pStage);
        //�ړI�n�ɓ���������
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
    //���f���f�[�^�̃��[�h
    hModel_ = Model::Load("EnemyBlue.fbx");
    assert(hModel_ >= 0);

    transform_.position_.x = 13.5f;
    transform_.position_.z = 10.5f;
    pMove->SetSpeed(0.15f);
    move = PREVIOUS_MOVE;
    movecounter_ = 1;
}

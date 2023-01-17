#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"

//���������Ǘ�����N���X
class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�

    int map_[15][15];

    Stage* pStage;

public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    //�f�X�g���N�^
    ~Enemy();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void PreviousMove();
    
    void BackMove();
    
    void LeftMove();
    
    void RightMove();
};
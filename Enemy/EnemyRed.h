#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"

//���������Ǘ�����N���X
class EnemyRed : public GameObject
{
    int hModel_;    //���f���ԍ�

    int map_[15][15];

    Stage* pStage;

public:
    //�R���X�g���N�^
    EnemyRed(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyRed();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};
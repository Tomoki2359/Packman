#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Move.h"

//���������Ǘ�����N���X
class Player : public GameObject
{
    int hModel_;    //���f���ԍ�

    int map_[15][15];

    int move_;

    Stage* pStage;

    Move* pMove;

public:
    //�R���X�g���N�^
    Player(GameObject* parent);

    //�f�X�g���N�^
    ~Player();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

};
#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"
#include "../Move.h"
#include "../Player.h"

//���������Ǘ�����N���X
class Enemy : public GameObject
{
    int hModel_;    //���f���ԍ�

    int map_[15][15];

protected:
    Player* pPlayer_;

    Stage* pStage;

    Move* pMove;

public:
    //�R���X�g���N�^
    Enemy(GameObject* parent);

    Enemy(GameObject* parent, std::string name);

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

    virtual int EnemyMove() = 0;

    virtual void Init() {};
};
#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"
class Dijkstra;
//���������Ǘ�����N���X
class EnemyRed : public Enemy
{
    Dijkstra* pDij_;
public:
    //�R���X�g���N�^
    EnemyRed(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyRed();

    int EnemyMove() override;
};
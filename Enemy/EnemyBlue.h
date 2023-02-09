#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"

class Dijkstra;
class EnemyRed;

class EnemyBlue : public Enemy
{
	Dijkstra* pDij_;
    float movecounter_;
    int move;
    bool isDiscovery_;  //����������
    std::pair<float, float> dir;    //�ړI�n
public:
    //�R���X�g���N�^
    EnemyBlue(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyBlue();

    int EnemyMove() override;

    void Init() override;
};


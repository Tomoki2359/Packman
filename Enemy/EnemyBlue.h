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
    bool isDiscovery_;  //発見したか
    std::pair<float, float> dir;    //目的地
public:
    //コンストラクタ
    EnemyBlue(GameObject* parent);

    //デストラクタ
    ~EnemyBlue();

    int EnemyMove() override;

    void Init() override;
};


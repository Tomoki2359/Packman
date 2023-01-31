#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"
class Dijkstra;
//◆◆◆を管理するクラス
class EnemyRed : public Enemy
{
    Dijkstra* pDij_;
public:
    //コンストラクタ
    EnemyRed(GameObject* parent);

    //デストラクタ
    ~EnemyRed();

    int EnemyMove() override;
};
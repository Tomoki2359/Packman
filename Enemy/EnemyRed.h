#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"
class Dijkstra;
class Aster;
//◆◆◆を管理するクラス
class EnemyRed : public Enemy
{
    Dijkstra* pDij_;
    Aster* pAst_;
public:
    //コンストラクタ
    EnemyRed(GameObject* parent);

    //デストラクタ
    ~EnemyRed();

    int EnemyMove() override;

    void Init() override;
};
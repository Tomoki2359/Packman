#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"
class Dijkstra;
class Trap;
//class Aster;
//◆◆◆を管理するクラス
class EnemyBlack : public Enemy
{
    Dijkstra* pDij_;
    Trap* pTrap_;
   // Aster* pAst_;
    float moveCounter_;
    int move;
    int movecounter_;
    const int maxCounter_;
    std::pair<int, int> dir;
public:
    //コンストラクタ
    EnemyBlack(GameObject* parent);

    //デストラクタ
    ~EnemyBlack();

    int EnemyMove() override;

    void Init() override;

    void SetDirection(int x, int y) { dir = {x,y}; };
};
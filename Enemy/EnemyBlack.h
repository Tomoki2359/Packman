#pragma once
#include "../Engine/GameObject.h"
#include "Enemy.h"
class Dijkstra;
class Trap;
//class Aster;
//���������Ǘ�����N���X
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
    //�R���X�g���N�^
    EnemyBlack(GameObject* parent);

    //�f�X�g���N�^
    ~EnemyBlack();

    int EnemyMove() override;

    void Init() override;

    void SetDirection(int x, int y) { dir = {x,y}; };
};
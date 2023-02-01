#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"
#include "../Move.h"
#include "../Player.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;    //モデル番号

    int map_[15][15];

protected:
    Player* pPlayer_;

    Stage* pStage;

    Move* pMove;

public:
    //コンストラクタ
    Enemy(GameObject* parent);

    Enemy(GameObject* parent, std::string name);

    //デストラクタ
    ~Enemy();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    virtual int EnemyMove() = 0;

    virtual void Init() {};
};
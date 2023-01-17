#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Move.h"

//◆◆◆を管理するクラス
class Player : public GameObject
{
    int hModel_;    //モデル番号

    int map_[15][15];

    int move_;

    Stage* pStage;

    Move* pMove;

public:
    //コンストラクタ
    Player(GameObject* parent);

    //デストラクタ
    ~Player();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

};
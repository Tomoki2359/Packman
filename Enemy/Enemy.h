#pragma once
#include "../Engine/GameObject.h"
#include "../Stage.h"

//◆◆◆を管理するクラス
class Enemy : public GameObject
{
    int hModel_;    //モデル番号

    int map_[15][15];

    Stage* pStage;

public:
    //コンストラクタ
    Enemy(GameObject* parent);

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

    void PreviousMove();
    
    void BackMove();
    
    void LeftMove();
    
    void RightMove();
};
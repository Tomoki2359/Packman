#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Stage : public GameObject
{
    int hModel_[2];    //モデル番号

    int map_[15][15];


public:
    //コンストラクタ
    Stage(GameObject* parent);

    //デストラクタ
    ~Stage();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    ;//そこは壁？
    bool IsWall(int x, int z);

    int GetType(int x, int y) { return map_[x][y]; };
};
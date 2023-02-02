#pragma once
#include "../Engine/GameObject.h"

//◆◆◆を管理するクラス
class Trap : public GameObject
{
    bool map_[15][15];
    bool isTrap_;
public:
    //コンストラクタ
    Trap(GameObject* parent);

    //デストラクタ
    ~Trap();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetTrap(int x, int y) { map_[x][y] = true; };

    bool IsTrap(int x, int y);
};
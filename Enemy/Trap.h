#pragma once
#include "../Engine/GameObject.h"

//◆◆◆を管理するクラス
class Trap : public GameObject
{
    std::list<std::pair<int, int>> pos_;    //トラップの位置
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

    void SetTrap(int x, int y);

    bool IsTrap(int x, int y);
};
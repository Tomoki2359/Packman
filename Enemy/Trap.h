#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class Trap : public GameObject
{
    bool map_[15][15];
    bool isTrap_;
public:
    //�R���X�g���N�^
    Trap(GameObject* parent);

    //�f�X�g���N�^
    ~Trap();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    void SetTrap(int x, int y) { map_[x][y] = true; };

    bool IsTrap(int x, int y);
};
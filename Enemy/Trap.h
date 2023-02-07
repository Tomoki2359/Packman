#pragma once
#include "../Engine/GameObject.h"

//���������Ǘ�����N���X
class Trap : public GameObject
{
    std::list<std::pair<int, int>> pos_;    //�g���b�v�̈ʒu
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

    void SetTrap(int x, int y);

    bool IsTrap(int x, int y);
};
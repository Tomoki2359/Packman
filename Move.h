#pragma once
#include "Stage.h"
enum MOVE
{
    PREVIOUS_MOVE = 0,
    BACK_MOVE,
    LEFT_MOVE,
    RIGHT_MOVE
};

class Move
{
    float speed_;
public:
    Move(Stage* pStage);

    void MoveSelect(int move, XMFLOAT3* trans);

    void PreviousMove(XMFLOAT3* trans);

    void BackMove(XMFLOAT3* trans);

    void LeftMove(XMFLOAT3* trans);

    void RightMove(XMFLOAT3* trans);

    void SetSpeed(float s) { speed_ = s; };

    float GetSpeed() { return speed_; };
};


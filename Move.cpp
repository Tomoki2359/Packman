#include "Move.h"

Move::Move()
{
	speed_ = 0.2f;
}

void Move::MoveSelect(int move, XMFLOAT3* trans)
{
    switch (move)
    {
    case PREVIOUS_MOVE:
    {
        PreviousMove(trans);
        break;
    }
    case BACK_MOVE:
    {
        BackMove(trans);
        break;
    }
    case LEFT_MOVE:
    {
        LeftMove(trans);
        break;
    }
    case RIGHT_MOVE:
    {
        RightMove(trans);
        break;
    }
    default:
        break;
    }
}

void Move::PreviousMove(XMFLOAT3* trans)
{
    trans->z += speed_;
}

void Move::BackMove(XMFLOAT3* trans)
{
    trans->z -= speed_;
}

void Move::LeftMove(XMFLOAT3* trans)
{
    trans->x -= speed_;
}

void Move::RightMove(XMFLOAT3* trans)
{
    trans->x += speed_;
}

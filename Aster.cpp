#include "Aster.h"
#include "Engine/Model.h"
#include "Move.h"
#include <cstdlib>

//コンストラクタ
Aster::Aster()
{
}

//目的地までの最短距離を求める
int Aster::GetAster(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage)
{
	/*for (auto itr = moveList_.begin(); moveList_.end() != itr; itr++)
	{
		if ((*itr).first != 9999)
		{
			pStage->SetType((*itr).second.x, (*itr).second.z, 0);
		}
	}*/

	Reset();

	int x = abs((Pos_.x - Des.x));
	int z = abs((Pos_.z - Des.z));
	sPlace_ = x + z;
	SearchDistance(Pos_, moveCount_, pStage, Des);
	while (isGoal_ != true)
	{
		sPlace_++;
		SearchDistanceList(pStage, Des);
		if (sPlace_ == 300)
			break;
	}
	int a = 0;
	if (isGoal_)
	{
		//ChangeDraw(Pos_, pStage,Des);
		return MoveDirection();
	}
	return -1;
}

//現在地からの距離の調査
void Aster::SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des)
{
	if (isGoal_)
	{
		return;
	}
	for (auto itr = moveList_.begin(); itr != moveList_.end(); itr++)
	{
		if ((*itr).first <= count && (*itr).second.x == Pos.x && (*itr).second.y == Pos.y && (*itr).second.z == Pos.z)
		{
			return;
		}
		else if ((*itr).first > count && (*itr).second.x == Pos.x && (*itr).second.y == Pos.y && (*itr).second.z == Pos.z)
		{
			moveList_.erase(itr);
			break;
		}
	}
	if (pStage->GetType(Pos.x, Pos.z) == 1)
	{
		moveList_.push_back({ 9999, XMFLOAT3(Pos.x, Pos.y, Pos.z) });
		return;
	}
	moveList_.push_back({ count, XMFLOAT3(Pos.x, Pos.y, Pos.z) });
	//一歩先が通れるかどうか
	//count++;
	int disX = abs((Pos.x + 1 - Des.x));
	int disZ = abs((Pos.z - Des.z));
	Dis_ = disX + disZ;
	add_ = count + Dis_;
	int hj = 0;
	if (Pos.x == Des.x && Pos.z == Des.z)
	{
		moveCount_ = count;
		isGoal_ = true;
	}
	if (isGoal_ != true)
	{
		if (add_ <= sPlace_)
		{
			if (pStage->GetType(Pos.x + 1, Pos.z))
			{
				SearchDistance(XMFLOAT3(Pos.x + 1, Pos.y, Pos.z), count + 1, pStage, Des);
			}
		}
		disX = abs((Pos.x - 1 - Des.x));
		disZ = abs((Pos.z - Des.z));
		Dis_ = disX + disZ;
		add_ = count + Dis_;
		if (add_ == sPlace_)
		{
			if(pStage->GetType(Pos.x - 1, Pos.z))
			{
				SearchDistance(XMFLOAT3(Pos.x - 1, Pos.y, Pos.z), count + 1, pStage, Des);
			}
		}
		disX = abs((Pos.x - Des.x));
		disZ = abs((Pos.z + 1 - Des.z));
		Dis_ = disX + disZ;
		add_ = count + Dis_;
		if (add_ == sPlace_)
		{
			if(pStage->GetType(Pos.x, Pos.z + 1))
			{
				SearchDistance(XMFLOAT3(Pos.x, Pos.y, Pos.z + 1), count + 1, pStage, Des);
			}
		}
		disX = abs((Pos.x - Des.x));
		disZ = abs((Pos.z - 1 - Des.z));
		Dis_ = disX + disZ;
		add_ = count + Dis_;
		if (add_ == sPlace_)
		{
			if (pStage->GetType(Pos.x, Pos.z - 1))
			{
				SearchDistance(XMFLOAT3(Pos.x, Pos.y, Pos.z - 1), count + 1, pStage, Des);
			}
		}
	}
}

void Aster::SearchDistanceList(Stage* pStage, XMFLOAT3 Des)
{
	auto itrEnd = moveList_.end();
	for (auto itr = moveList_.begin(); itr != itrEnd; itr++)
	{
		if ((pStage->GetType((*itr).second.x, (*itr).second.z)) != 1)
		{
			SearchDistance(XMFLOAT3((*itr).second.x + 1, (*itr).second.y, (*itr).second.z), (*itr).first + 1, pStage, Des);
			SearchDistance(XMFLOAT3((*itr).second.x - 1, (*itr).second.y, (*itr).second.z), (*itr).first + 1, pStage, Des);
			SearchDistance(XMFLOAT3((*itr).second.x, (*itr).second.y, (*itr).second.z + 1), (*itr).first + 1, pStage, Des);
			SearchDistance(XMFLOAT3((*itr).second.x, (*itr).second.y, (*itr).second.z - 1), (*itr).first + 1, pStage, Des);
		}
		if (isGoal_)
		{
			return;
		}
	}
}

//目的地から自分の場所までの最短距離の道に変更
void Aster::ChangeDraw(XMFLOAT3 Pos, Stage* pStage,XMFLOAT3 Des)
{
	//pStage->SetType(Pos.x, Pos.z, 2);
	/*if ((*moveList_.end()).first == 0)
	{
		return;
	}*/

	auto itr = moveList_.rbegin();
	XMFLOAT3 nextPos = (*itr).second;
	moveCount_--;
	//pStage->SetType(nextPos.x, nextPos.z, 2);
	for (itr; moveList_.rend() != itr; itr++)
	{
		if ((*itr).first == 0)
		{
			//pStage->SetType((*itr).second.x, (*itr).second.z, 2);
			return;
		}
		if ((*itr).first == moveCount_ )
		{
			if ((*itr).second.x == nextPos.x - 1 && (*itr).second.z == nextPos.z)
			{
				moveCount_--;
				nextPos.x--;
				//pStage->SetType((*itr).second.x, (*itr).second.z, 2);
			}
			else if ((*itr).second.x == nextPos.x + 1 && (*itr).second.z == nextPos.z)
			{
				moveCount_--;
				nextPos.x++;
				//pStage->SetType((*itr).second.x, (*itr).second.z, 2);
			}
			else if ((*itr).second.x == nextPos.x && (*itr).second.z == nextPos.z - 1)
			{
				moveCount_--;
				nextPos.z--;
				//pStage->SetType((*itr).second.x, (*itr).second.z, 2);
			}
			else if ((*itr).second.x == nextPos.x && (*itr).second.z == nextPos.z + 1)
			{
				moveCount_--;
				nextPos.z++;
				//pStage->SetType((*itr).second.x, (*itr).second.z, 2);
			}
		}
	}
}

int Aster::MoveDirection()
{
	auto itr = moveList_.rbegin();
	itr++;
	XMFLOAT3 nextPos = (*itr).second;
	moveCount_--;
	//pStage->SetType(nextPos.x, nextPos.z, 2);
	//for (itr; moveList_.rend() != itr; itr++)
	//{
		if ((*itr).first == 0)
		{
			return -1;
		}
		if ((*itr).first == moveCount_)
		{
			if ((*itr).second.x == nextPos.x - 1 && (*itr).second.z == nextPos.z)
			{
				return RIGHT_MOVE;
			}
			else if ((*itr).second.x == nextPos.x + 1 && (*itr).second.z == nextPos.z)
			{
				return LEFT_MOVE;
			}
			else if ((*itr).second.x == nextPos.x && (*itr).second.z == nextPos.z - 1)
			{
				return PREVIOUS_MOVE;
			}
			else if ((*itr).second.x == nextPos.x && (*itr).second.z == nextPos.z + 1)
			{
				return BACK_MOVE;
			}
		}
	//}
}

void Aster::Reset()
{
	moveCount_ = 0;
	Dis_ = -1;
	sPlace_ = -1;
	isGoal_ = false;
	moveList_.clear();
}

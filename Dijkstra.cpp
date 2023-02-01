#include "Dijkstra.h"
#include "Engine/Model.h"
#include "Move.h"
#include <cstdlib>

namespace
{
	int move = -1;
	float dis = 0.3f;
}

//コンストラクタ
Dijkstra::Dijkstra()
{
	Reset();
}

//目的地までの最短距離を求める
int Dijkstra::GetDijkstra(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage)
{
	Reset();

	//現在地からの距離を求める(今回は必要なさそう)
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			if (pStage->GetType(x, z) == 1)
			{
				Dij_[x][z].Dis_ = -1;
			}
			else
			{
				Dij_[x][z].Dis_ = abs((Pos_.x - x + Pos_.z - z));
				pStage->SetType(x, z, 0);
			}
		}
	}

	//目的地についていない場合の処理
	if (Des.x != Pos_.x || Des.z != Pos_.z)
	{
		SearchDistance(Pos_, 1, pStage,Des);
		
		//目的地にたどり着いたら
		if (Dij_[(int)Des.x][(int)Des.z].count_ != 9999)
		{
			ChangeDraw(Des, pStage);
			return MoveDirection(Des);
		}
	}
	return move;
}

//現在地からの距離の調査
void Dijkstra::SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des)
{
	//目的地にたどり着くか端っこまでいったら終わる
	if (Pos.x == Des.x && Pos.z == Des.z || Pos.x > 15 || Pos.x < 0 || Pos.z > 15 || Pos.z < 0)
	{
		return;
	}

	//一歩先が通れるかどうか
	switch (pStage->GetType(Pos.x + 1, Pos.z))
	{
	case 0:
	case 2:
		if (Dij_[(int)Pos.x + 1][(int)Pos.z].count_ > count)
		{
			Dij_[(int)Pos.x + 1][(int)Pos.z].count_ = count;
			SearchDistance(XMFLOAT3(Pos.x + 1,Pos.y,Pos.z),count + 1, pStage,Des);
		}
			break;
	case 1:
		Dij_[(int)Pos.x + 1][(int)Pos.z].count_ = 9999;
		break;
	}
	switch (pStage->GetType(Pos.x - 1, Pos.z))
	{
	case 0:
	case 2:
		if (Dij_[(int)Pos.x - 1][(int)Pos.z].count_ > count)
		{
			Dij_[(int)Pos.x - 1][(int)Pos.z].count_ = count;
			SearchDistance(XMFLOAT3(Pos.x - 1, Pos.y, Pos.z), count + 1, pStage,Des);
		}
			break;
	case 1:
		Dij_[(int)Pos.x - 1][(int)Pos.z].count_ = 9999;
		break;
	}
	switch (pStage->GetType(Pos.x, Pos.z + 1))
	{
	case 0:
	case 2:
		if (Dij_[(int)Pos.x][(int)Pos.z + 1].count_ > count)
		{
			Dij_[(int)Pos.x][(int)Pos.z + 1].count_ = count;
			SearchDistance(XMFLOAT3(Pos.x, Pos.y, Pos.z + 1), count + 1, pStage,Des);
		}
			break;
	case 1:
		Dij_[(int)Pos.x][(int)Pos.z + 1].count_ = 9999;
		break;
	}
	switch (pStage->GetType(Pos.x, Pos.z - 1))
	{
	case 0:
	case 2:
		if (Dij_[(int)Pos.x][(int)Pos.z - 1].count_ > count)
		{
			Dij_[(int)Pos.x][(int)Pos.z - 1].count_ = count;
			SearchDistance(XMFLOAT3(Pos.x, Pos.y, Pos.z - 1), count + 1, pStage,Des);
		}
			break;
	case 1:
		Dij_[(int)Pos.x][(int)Pos.z - 1].count_ = 9999;
		break;
	}
}

//目的地から自分の場所までの最短距離の道に変更
void Dijkstra::ChangeDraw(XMFLOAT3 Pos, Stage* pStage)
{
	pStage->SetType(Pos.x, Pos.z, 2);
	if (Dij_[(int)Pos.x][(int)Pos.z].count_ == 0)
	{
		return;
	}
	if (Dij_[(int)Pos.x + 1][(int)Pos.z].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		ChangeDraw(XMFLOAT3(Pos.x + 1,Pos.y,Pos.z),pStage);
	}
	if (Dij_[(int)Pos.x - 1][(int)Pos.z].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		ChangeDraw(XMFLOAT3(Pos.x - 1, Pos.y, Pos.z),pStage);
	}
	if (Dij_[(int)Pos.x][(int)Pos.z + 1].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		ChangeDraw(XMFLOAT3(Pos.x, Pos.y, Pos.z + 1), pStage);
	}
	if (Dij_[(int)Pos.x][(int)Pos.z - 1].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		ChangeDraw(XMFLOAT3(Pos.x, Pos.y, Pos.z - 1), pStage);
	}
}

int Dijkstra::MoveDirection(XMFLOAT3 Pos)
{
	if (Dij_[(int)Pos.x - 1][(int)Pos.z].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		move = LEFT_MOVE;
	}
	else if (Dij_[(int)Pos.x + 1][(int)Pos.z].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		move = RIGHT_MOVE;
	}
	else if (Dij_[(int)Pos.x][(int)Pos.z - 1].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		move = BACK_MOVE;
	}
	else if (Dij_[(int)Pos.x][(int)Pos.z + 1].count_ < Dij_[(int)Pos.x][(int)Pos.z].count_)
	{
		move = PREVIOUS_MOVE;
	}
	//return -1;
	return move;
}

void Dijkstra::Reset()
{
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			Dij_[x][z].Dis_ = -1;
			Dij_[x][z].count_ = 9999;
		}
	}
}

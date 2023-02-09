#pragma once
#include "Stage.h"


//■■シーンを管理するクラス
class Dijkstra
{
	struct Dij
	{
		int Dis_;	//距離
		int count_; //動いた数
	} Dij_[15][15];
public:
	//コンストラクタ
	Dijkstra();

	//目的地までの最短距離を求める
	//引数: 第一引数:現在地 第二引数: 目的地　第三引数; ステージ情報
	int GetDijkstra(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage);

	//距離の調査
	//引数: 第一引数: 現在地、　第二引数: 動いた数
	void SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des);

	//目的地までの最短距離の場所の表示するものを変える
	//引数:　第一引数: 現在地
	void ChangeDraw(XMFLOAT3 Pos, Stage* pStage);

	int MoveDirection(XMFLOAT3 Pos);

	//Dijの中身を初期化する
	void Reset();

	int RandamMoveDirection(XMFLOAT3 Pos,Stage* pStage,float s, int m);
};
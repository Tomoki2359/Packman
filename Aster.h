#pragma once
#include "Stage.h"

//■■シーンを管理するクラス
class Aster
{
	int moveCount_;	//動いた数
	int Dis_;		//距離
	int add_;		//距離＋動いた数
	int sPlace_;	//最短地
	bool isGoal_;
	//int: 動いた数、XMFLOAT3: 現在地
	std::list<std::pair<int,XMFLOAT3>> moveList_;	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Aster();

	//目的地までの最短距離を求める
	//引数: 第一引数:現在地 第二引数: 目的地　第三引数; ステージ情報
	int GetAster(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage);

	//距離の調査
	//引数: 第一引数: 現在地、　第二引数: 動いた数
	void SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des);

	void SearchDistanceList(Stage* pStage, XMFLOAT3 Des);

	//目的地までの最短距離の場所の表示するものを変える
	//引数:　第一引数: 現在地
	void ChangeDraw(XMFLOAT3 Pos, Stage* pStage, XMFLOAT3 Des);


	int MoveDirection();

	//初期化する
	void Reset();
};
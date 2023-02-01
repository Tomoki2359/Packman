#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReaDer.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")//, hModel_(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initialize()
{
	//モデルデータのロード
	hModel_[0] = Model::Load("Floor.fbx");
	assert(hModel_[0] >= 0);
	//モデルデータのロード
	hModel_[1] = Model::Load("Wall.fbx");
	assert(hModel_ [1]>= 1);
	hModel_[2] = Model::Load("BoxDefault.fbx");
	assert(hModel_[2] >= 2);
	CsvReader csv;
	csv.Load("Map.csv");
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			map_[x][z] = (int)csv.GetValue(x, z);
		}
	}
	
}

//更新
void Stage::Update()
{
}

//描画
void Stage::Draw()
{
	for (int x = 0; x < 15; x++)
	{
		for (int z = 0; z < 15; z++)
		{
			int type = map_[x][z];
			transform_.position_.x = x;
			transform_.position_.z = z;
			Model::SetTransform(hModel_[type], transform_);
			Model::Draw(hModel_[type]);
		}
	}
}

//開放
void Stage::Release()
{
}

//そこは壁かどうか
bool Stage::IsWall(int x, int z)
{
	return (map_[x][z] == 1);

	//↓これもif文と同じ
	//return map_[x][z] == 1 ? true : false;



	///////////////////////////////////////////////
	//if (map_[x][z] == 1)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}

}
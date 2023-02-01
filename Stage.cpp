#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/CsvReaDer.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage")//, hModel_(-1)
{
}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
	//���f���f�[�^�̃��[�h
	hModel_[0] = Model::Load("Floor.fbx");
	assert(hModel_[0] >= 0);
	//���f���f�[�^�̃��[�h
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

//�X�V
void Stage::Update()
{
}

//�`��
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

//�J��
void Stage::Release()
{
}

//�����͕ǂ��ǂ���
bool Stage::IsWall(int x, int z)
{
	return (map_[x][z] == 1);

	//�������if���Ɠ���
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
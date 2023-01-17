#include "PlayScene.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Player.h"
//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Player>(this);
	Camera::SetPosition(XMFLOAT3{ 7,20,6 });
	Camera::SetTarget(XMFLOAT3{ 7,0,7 });
}

//�X�V
void PlayScene::Update()
{
}

//�`��
void PlayScene::Draw()
{

}

//�J��
void PlayScene::Release()
{
}
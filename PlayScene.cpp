#include "PlayScene.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Enemy/EnemyRed.h"
#include "Enemy/EnemyBlack.h"
#include "Enemy/EnemyBlue.h"
#include "Enemy/Trap.h"
//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene")
{
}

//������
void PlayScene::Initialize()
{
	Instantiate<Stage>(this);
	Instantiate<Trap>(this);
	Instantiate<Player>(this);
	//Instantiate<EnemyRed>(this);
	Instantiate<EnemyBlue>(this);
	Instantiate<EnemyBlack>(this);
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
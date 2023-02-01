#pragma once
#include "Stage.h"

//�����V�[�����Ǘ�����N���X
class Aster
{
	int moveCount_;	//��������
	int Dis_;		//����
	int add_;		//�����{��������
	int sPlace_;	//�ŒZ�n
	bool isGoal_;
	//int: ���������AXMFLOAT3: ���ݒn
	std::list<std::pair<int,XMFLOAT3>> moveList_;	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Aster();

	//�ړI�n�܂ł̍ŒZ���������߂�
	//����: ������:���ݒn ������: �ړI�n�@��O����; �X�e�[�W���
	int GetAster(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage);

	//�����̒���
	//����: ������: ���ݒn�A�@������: ��������
	void SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des);

	void SearchDistanceList(Stage* pStage, XMFLOAT3 Des);

	//�ړI�n�܂ł̍ŒZ�����̏ꏊ�̕\��������̂�ς���
	//����:�@������: ���ݒn
	void ChangeDraw(XMFLOAT3 Pos, Stage* pStage, XMFLOAT3 Des);


	int MoveDirection();

	//����������
	void Reset();
};
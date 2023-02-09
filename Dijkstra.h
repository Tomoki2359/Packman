#pragma once
#include "Stage.h"


//�����V�[�����Ǘ�����N���X
class Dijkstra
{
	struct Dij
	{
		int Dis_;	//����
		int count_; //��������
	} Dij_[15][15];
public:
	//�R���X�g���N�^
	Dijkstra();

	//�ړI�n�܂ł̍ŒZ���������߂�
	//����: ������:���ݒn ������: �ړI�n�@��O����; �X�e�[�W���
	int GetDijkstra(XMFLOAT3 Pos_, XMFLOAT3 Des, Stage* pStage);

	//�����̒���
	//����: ������: ���ݒn�A�@������: ��������
	void SearchDistance(XMFLOAT3 Pos, int count, Stage* pStage, XMFLOAT3 Des);

	//�ړI�n�܂ł̍ŒZ�����̏ꏊ�̕\��������̂�ς���
	//����:�@������: ���ݒn
	void ChangeDraw(XMFLOAT3 Pos, Stage* pStage);

	int MoveDirection(XMFLOAT3 Pos);

	//Dij�̒��g������������
	void Reset();

	int RandamMoveDirection(XMFLOAT3 Pos,Stage* pStage,float s, int m);
};
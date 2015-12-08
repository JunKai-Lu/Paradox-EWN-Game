#include "stdafx.h"
#include "EWNdefine.h"

#pragma  once

#define MC_CONSTANT 30000				//���ؿ���ģ�ⳣ��
#define GUMC_CONSTANT 10000				//���ؿ�����������
#define ESTIMATE_CONSTANT 10000			//���ֲ��Գ���
#define FILTER_MC_CONSTANT 10000		//FILTER�㷨����
#define FIX_FILTER_MC_CONSTANT 10000	//FILTER�㷨����
#define BOARD_TEST_CONSTANT 20000		//���ֲ��Գ���

#define UCT_MC_TIMES 1					//UCT�е�MC���۳���
#define UCT_TIMES 10000000				//UCT�����Ĵ���
#define UCT_LIMIT 120					//UCT�㷨�����ʱ��

//MC

void RndMove(Board &CB,int Piece);
int GetMCWinner(Board &CB,int NextPlayer);
float GetMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void MonteCarloMove(Board &CB,int Piece);

//Filter

void RndFilterMove(Board &CB,int Piece);
int GetFilterMCWinner(Board &CB,int NextPlayer);
float GetFilterMCEvalution(Board &CB,int NextPlayer,int Winner,int times);
void FilterMCMove(Board &CB,int Piece);

//FixFilter

void RndFixFilterMove(Board &CB,int Piece);
int GetFixFilterMCWinner(Board &CB,int NextPlayer);
float GetFixFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void FixFilterMCMove(Board &CB,int Piece);

//GreedUtilityMC
int GetFMCWinnerByFirstDice(Board &CB,int NextPlayer,int FirstPiece);
float GetGUMCEvalution(Board &CB, int NextPlayer, int Winner, int times);
void GreedUtilityMCMove(Board &CB,int Piece);

//FilterBoardEvalution
int GetFilterBoardEvalution(Board &CB,int NextPlayer,int Winner,int times);



//UCT For EWN
class UCTBoard:public Board
{
public:
	UCTBoard();//���캯����һ����Ϊ�˸���
	UCTBoard(int Player,int Array[SIZE][SIZE],int step);//���캯����һ������������ڵ�
	UCTBoard(int Player,int Array[SIZE][SIZE],int Piece,Loc mLoc,int step);//���캯����һ�����������ӽڵ�

	//�̶���Ϣ
	int Owner;//UCTBoard���������
	int Times;//�����Թ��Ĵ���
	int BoardWinner;//��������ʤ����
	bool PieceLife[7];//�����ӵ�����״̬
	int ExistChildNum[7];//ÿ�����ʽڵ����Ѵ��ڵ��ӽڵ��������ChildNodes[N]��0��ChildNum[N]-1����ָ����Ҫ��ʼ����R��������
	int TotalChildNum[7];//ÿ�����ʽڵ��������ӽڵ���Ŀ
	Move UCTMove[7][3];//�洢��ʽ����UCTBoard���ɵ�ʱ������һ����ʽ�б��б���[ĳ����][��ʽ���]���д洢�����洢���ڵ����ӵ���ʽ
	UCTBoard* ChildNodes[7][3];//ָ���ӽڵ��ǵ�ָ�룬�����3*6 = 18��

	//������UCBֵ
	float UCBValue;//UCBֵ
	float AvgValue;//ƽ������
	float RefreshAvgValue();//ˢ�±��ڵ�����档
	float RefreshUCBValue(int Total);//����ƽ���������UCBֵ
	UCTBoard* ExpandUCTBoard(int ExpandNum,int &Total);//��չUCT�ڵ�
};
float UCT_Iteration(UCTBoard &B, int &Total);
void UCTMove(Board &CB,int Piece);
void DeleteUCTBoard(UCTBoard* Root);
void DeleteUCTTree(UCTBoard Root);

extern UCTBoard *UCTNodes[UCT_TIMES];
extern int UCTNodeNum;


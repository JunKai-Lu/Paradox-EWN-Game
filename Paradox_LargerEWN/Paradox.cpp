#include "stdafx.h"
#include "EWNdefine.h"
#include "Paradox.h"
#include "windows.h"
#include "stdio.h"
#include "time.h"
#include <iostream>
#include <sstream>

using namespace std;

//MonteCarlo �������ؿ����㷨
void RndMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetAllMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetMCWinner(Board &CB,int NextPlayer)
{
	//���ƴ���������ϣ����ݴ�����������н��в���������һ������ƶ���ʤ���ߡ�
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void MonteCarloMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetAllMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//�ȴ���һ��������
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//�����ƶ��˵�iλ
		float Val = GetMCEvalution(NCB, -f, f, MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FilterMC ���ؿ��������㷨
void RndFilterMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetFilterMCWinner(Board &CB,int NextPlayer)
{
	//���ƴ���������ϣ����ݴ�����������н��в���������һ������ƶ���ʤ���ߡ�
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void FilterMCMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//�ȴ���һ��������
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//�����ƶ��˵�iλ
		float Val = GetFilterMCEvalution(NCB, -f, f, FILTER_MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FixFilterMC ���ؿ��������㷨������
void RndFixFilterMove(Board &CB,int Piece)
{
	int dice;
	Move Moves[6];
	int MoveNum = CB.GetFixFilterMoves(Moves,Piece);
	dice = rand()%MoveNum;
	CB.Move(Moves[dice].Loc,Moves[dice].Piece);
}
int GetFixFilterMCWinner(Board &CB,int NextPlayer)
{
	//���ƴ���������ϣ����ݴ�����������н��в���������һ������ƶ���ʤ���ߡ�
	Board NCB = CB;
	int player = NextPlayer;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
		{
			return w;
		}
		RndFixFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetFixFilterMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFixFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	float Result = (float)Eva / (float)times;
	return Result;
}
void FixFilterMCMove(Board &CB,int Piece)
{
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFixFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//�ȴ���һ��������
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//�����ƶ��˵�iλ
		float Val = GetFixFilterMCEvalution(NCB, -f, f, FIX_FILTER_MC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//GreedUtilityMC ̰��Ч�����ؿ����㷨
int GetFMCWinnerByFirstDice(Board &CB,int NextPlayer,int FirstPiece)
{
	//���ƴ���������ϡ������ƶ�ָ�������ӣ�Ȼ���ٿ�ʼ����ƶ������ӷ�ΧΪ-6��6
	Board NCB = CB;
	int player = NextPlayer;
	int w = NCB.Winner();
	if(w!=0)
		return w;
	RndFilterMove(NCB,FirstPiece);
	player = -player;
	for(int i =0;i>-1;i++)
	{
		int w = NCB.Winner();
		if(w!=0)
			return w;
		RndFilterMove(NCB,player*RndDice());
		player = -player;
	}
	return 0;
}
float GetGUMCEvalution(Board &CB, int NextPlayer, int Winner, int times)
{
	//���һ�����ӵ�����
	//����ĳ�����Ӳ����ڣ�������Ϊ�ܱ������е�����ߡ�
	//һ�����ӵ����棬Ϊ��������6��������ʱ�����ؿ��޹��̵�ƽ������

	Board NCB = CB;
	int Eva[7];
	bool PieceAlive[7];
	//���ȣ��б��������ӵ�����״̬��
	for(int i=1;i<=6;i++)
	{
		Eva[i]=0;//˳����ʼ��һ��Eva����
		if(CB.GetPieceLife(NextPlayer*i))
			PieceAlive[i]=true;
		else
			PieceAlive[i]=false;
	}

	//�����д��ڵ�������һ�����ؿ����б�ȷ������
	for(int PieceNum=1;PieceNum<=6;PieceNum++)
	{
		if(PieceAlive[PieceNum])
		{
			for(int i =0;i<times;i++)
			{
				if(GetFMCWinnerByFirstDice(NCB,NextPlayer,PieceNum)==Winner)
					Eva[PieceNum]++;
			}
		}
	}
	//ȷ�������ڵ����ӵ�����
	for(int PieceNum=1;PieceNum<=6;PieceNum++)
	{
		if(PieceAlive[PieceNum]==false)
		{
			int s_Piece = CB.GetSmallerPiece(PieceNum);
			int l_Piece = CB.GetLargerPiece(PieceNum);
			if(s_Piece!=0&&l_Piece!=0)//ͬʱ����s_Piece��l_Piece������£�ȡ����ֵ�ϴ��һ��
			{
				if(Eva[s_Piece]>=Eva[l_Piece])
					Eva[PieceNum] = Eva[s_Piece];
				else
					Eva[PieceNum] = Eva[l_Piece];
			}
			else if(s_Piece==0&&l_Piece!=0)//ֻ����l_Piece������£�ȡl_Piece��ֵ
				Eva[PieceNum] = Eva[l_Piece];
			else if(s_Piece!=0&&l_Piece==0)//ֻ����s_Piece������£�ȡs_Piece��ֵ
				Eva[PieceNum] = Eva[s_Piece];
			else//�������ڵ������
			{
				cout<<"GetFMCAvgEvalution���������������κ�����";
				system("pause");
			}
		}
	}
	
	//ȷ����������
	float Result = 0;
	for(int i=1;i<=6;i++)
	{
		Result += ((float)Eva[i] / (float)times) / 6;
	}
	return Result;
}
void GreedUtilityMCMove(Board &CB,int Piece)
{
	//̰��Ч�����ؿ���
	int f = CB.GetPieceFaction(Piece);
	Move Moves[6];
	int MoveNum = CB.GetFilterMoves(Moves,Piece);
	float BestVal = -1;
	int BestMove =0;
	for(int i=0;i<MoveNum;i++)
	{
		Board NCB = CB;//�ȴ���һ��������
		NCB.Move(Moves[i].Loc,Moves[i].Piece);//�����ƶ��˵�iλ
		float Val = GetGUMCEvalution(NCB, -f, f, GUMC_CONSTANT);
		if(Val>=BestVal)
		{
			BestVal = Val;
			BestMove = i;
		}
	}
	CB.Move(Moves[BestMove].Loc,Moves[BestMove].Piece);
}

//FilterBoardEvalution
int GetFilterBoardEvalution(Board &CB,int NextPlayer,int Winner,int times)
{
	Board NCB = CB;
	int Eva = 0;
	for(int i =0;i<times;i++)
	{
		if(GetFilterMCWinner(NCB,NextPlayer)==Winner)
			Eva++;
	}
	return Eva;
}

//UCT For EWN ����˹̹UCT�㷨
UCTBoard::UCTBoard()
{
	for(int i=1;i<=6;i++)
	{
		ExistChildNum[i] = 0;//����ʱ����ӽڵ���ĿΪ0
		//HaveFirstTimeNode[i] = true;//����ʱ�����н����ڵ㶼δ�������
	}
	UCBValue =0;//����ʱ��UCBֵΪ0
	AvgValue =0;//����ʱ���ƽ������Ϊ0
	Times=1;//������ʱ���Ӧ����������һ����
}
UCTBoard::UCTBoard(int Player,int Array[SIZE][SIZE],int step)
{
	//��������
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			board[j][i] = Array[j][i];
		}
	}
	//ΪĳЩ������ֵ
	Owner = Player;
	BoardWinner = Winner();
	Step = step;
	for(int i=1;i<=6;i++)
		PieceLife[i] = GetPieceLife(Owner*i);
	UCBValue =0;//����ʱ��UCBֵΪ0
	AvgValue =0;//����ʱ���ƽ������Ϊ0
	Times=1;//������ʱ���Ӧ����������һ����

	//�������е���ʽ��
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//�����N�����Ӵ���
		{
			TotalChildNum[i] = GetFilterMoves(UCTMove[i],Owner*i);//ȷ��ÿ�����������������ʽ����ʽ����
			ExistChildNum[i] = 0;//����ʱ����ӽڵ���ĿΪ0
			//HaveFirstTimeNode[i] = true;//����ʱ�����н����ڵ㶼δ�������
		}
	}
}
UCTBoard::UCTBoard(int Player,int Array[SIZE][SIZE],int Piece,Loc mLoc,int step)
{
	//�����ƶ��������
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			board[j][i] = Array[j][i];
		}
	}
	Step = step;
	Move(mLoc,Piece);//�ƶ�����
	
	//ΪĳЩ������ֵ
	Owner = Player;
	BoardWinner = Winner();
	for(int i=1;i<=6;i++)
		PieceLife[i] = GetPieceLife(Owner*i);
	UCBValue =0;//����ʱ��UCBֵΪ0
	AvgValue =0;//����ʱ���ƽ������Ϊ0
	Times=1;//������ʱ���Ӧ����������һ����

	//�������е���ʽ��
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//�����N�����Ӵ���
		{
			TotalChildNum[i] = GetFilterMoves(UCTMove[i],Owner*i);//ȷ��ÿ�����������������ʽ����ʽ����
			ExistChildNum[i] = 0;//����ʱ����ӽڵ���ĿΪ0
			//HaveFirstTimeNode[i] = true;//����ʱ�����н����ڵ㶼δ�������
		}
	}
}
float UCTBoard::RefreshAvgValue()
{
	/*	����ԭ��Ϊ������һ�����Ӷ�Ӧ�����Ӵ��ڡ�������Ϊ�����Ӷ�Ӧ���ӽڵ��ƽ�����档
		���һ�����Ӷ�Ӧ�����Ӳ����ڣ����ֻ��һ����ѡ���ӵ�����£�Ϊ��ѡ���ӵ��ӽڵ��ƽ�����档
		�������������ѡ���ӣ���Ϊ��������ѡ���ӵ������ӽڵ��ƽ�����档
		��������Ϊ ��(N������/6),n ={1,2,3,4,5,6}
	*/
	float PieceValue[7];
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//��������i����
		{
			float Value = 0;
			for(int j=0;j<ExistChildNum[i];j++)
				Value+=ChildNodes[i][j]->AvgValue;
			PieceValue[i] = Value/ExistChildNum[i];
		}
	}
	float TotalValue = 0;
	for(int i=1;i<=6;i++)
	{
		if(PieceLife[i])//��������i����
		{
			TotalValue+= PieceValue[i];//����������������������
			//cout<<i<<" = "<<PieceValue[i]<<endl;
		}
		else//�������i������
		{
			//���Ȼ�ñ�ѡ��
			int s_i = 0;//�趨s_iΪ�������С������
			int l_i = 0;//�趨l_iΪ��������������
			for(int p = i;p<=6;p++)
			{
				if(PieceLife[p])
				{
					l_i = p;
					break;
				}
			}
			for(int p = i;p>=1;p--)
			{
				if(PieceLife[p])
				{
					s_i = p;
					break;
				}
			}
			//Ȼ����ݱ�ѡ������������ж�
			if(s_i!=0&&l_i!=0)
			{
				//���ݱ�ѡ�����������
				if(PieceValue[s_i]>PieceValue[l_i])
					TotalValue+=PieceValue[s_i];
				else
					TotalValue+=PieceValue[l_i];
				//TotalValue += (PieceValue[s_i]+PieceValue[l_i])/2;//������������ܱ߱�ѡ����ƽ��ƽ��
			}
			else if(s_i!=0&&l_i==0)
				TotalValue += PieceValue[s_i];//�������������Ψһ�ı�ѡ����ͬ
			else if(s_i==0&&l_i!=0)
				TotalValue += PieceValue[l_i];//�������������Ψһ�ı�ѡ����ͬ
			else
			{
				cout<<"UCTBoard::RefreshAvgValue���������������κ�����";
				system("pause");
			}
		}
	}
	TotalValue = TotalValue/6;
	AvgValue = 1-TotalValue;//���о���֮���ƽ������
	return AvgValue;
}
float UCTBoard::RefreshUCBValue(int Total)
{
	float t = (float)Times;
	float n = (float)Total;
	float h = (log10(n)) * 2;
	float exploitation = sqrt((h / t));
	float UCBValue = AvgValue + exploitation;
	return UCBValue;
}
UCTBoard* UCTBoard::ExpandUCTBoard(int ExpandNum,int &Total)
{
	Total++;//��׼����ʱ���ܳ��Դ�����������1
	UCTBoard *NewB = new UCTBoard(-Owner,board,UCTMove[ExpandNum][ExistChildNum[ExpandNum]].Piece,UCTMove[ExpandNum][ExistChildNum[ExpandNum]].Loc,Step);//����һ���µ�����
	UCTNodes[UCTNodeNum] = NewB;
	UCTNodeNum++;
	Board TestB(NewB->board,NewB->Step);//������������
	NewB->AvgValue = GetFilterMCEvalution(TestB,-Owner,Owner,UCT_MC_TIMES);//�õ�MC����ֵ
	return NewB;
}
float UCT_Iteration(UCTBoard &B, int &Total)
{
	B.Times++;//��̽��Ĵ���+1
	if(B.BoardWinner !=0)//�����Ϸ�Ѿ�����
	{
		B.AvgValue = 1;//���ڸ��ڵ���ԣ�����ڵ������϶���1
		Total++;
		return B.AvgValue;
	}
	if(B.Times ==2)//��׼����֮һ�����ĳ���ڵ㲻�����κ��Ӹ���������Ϊ��ÿһ���Ӹ�����������һ���ڵ㡣
	{
		for(int i=1;i<=6;i++)
		{
			if(B.PieceLife[i]==true)//������ڵĻ�
			{
				B.ChildNodes[i][B.ExistChildNum[i]] = B.ExpandUCTBoard(i,Total);//��չ����ڵ�
				B.ExistChildNum[i]++;//���ڵ��ӽڵ�������1
			}
		}
		//cout<<"Msg  Toatl UCT Times : "<<Total<<endl;
		B.RefreshAvgValue();//����ȫ����Ҫ���ӽڵ��ˢ��һ������ֵ��
		//cout<<"Msg : Value ="<<B.AvgValue<<endl;
		return B.AvgValue;
	}
	else
	{
		int Dice = RndDice();
		int NextNum;//��һ��Ҫ�ߵ�����
		int SmallerNum = 0;//�趨SmallerNumΪ�������С������
		int LargerNum = 0;//�趨LargerNumΪ��������������
		bool SinglePiece = true;//�Ƿ�ѡ���֧��������������ӿ���ѡ��Ļ�Ϊ˫ѡ��
		if(B.PieceLife[Dice])//���ѡ�е����Ӵ���
		{
			NextNum = Dice;
		}
		else//�����ڵĻ���Ҫ����ɸѡ
		{
			for(int p = Dice;p<=6;p++)
			{
				if(B.PieceLife[p])
				{
					LargerNum = p;
					break;
				}
			}
			for(int p = Dice;p>=1;p--)
			{
				if(B.PieceLife[p])
				{
					SmallerNum = p;
					break;
				}
			}
			if(SmallerNum!=0&&LargerNum!=0)
				SinglePiece = false;
			else if(SmallerNum!=0&&LargerNum==0)
				NextNum = SmallerNum;
			else if(LargerNum!=0&&SmallerNum==0)
				NextNum = LargerNum; 
		}
		//����������SinglePiece = TRUE ����£�NextNumΪ���������ӡ�ΪFALSE����£�SmallerNum��LargerNumΪ˫��������

		//��ʼ���߲�
		bool SingleBaseCase = SinglePiece==true&&B.TotalChildNum[NextNum]>B.ExistChildNum[NextNum];//��ѡ���׼���
		bool DoubleBaseCase = SinglePiece==false&&((B.TotalChildNum[LargerNum]>B.ExistChildNum[LargerNum])||(B.TotalChildNum[SmallerNum]>B.ExistChildNum[SmallerNum]));//˫ѡ���׼���

		if(SingleBaseCase||DoubleBaseCase)//��׼����֮������ѡ����չNextNum��������Ӹ�����
		{
			if(DoubleBaseCase)//�����˫ѡ��Ļ���Ҫ�ȸ�����һ����ӵ��Ϊ���ԵĽڵ�����ɵ�ѡ��
			{
				if((B.TotalChildNum[LargerNum]>B.ExistChildNum[LargerNum]))
					NextNum = LargerNum;
				else
					NextNum = SmallerNum;
			}
			B.ChildNodes[NextNum][B.ExistChildNum[NextNum]] = B.ExpandUCTBoard(NextNum,Total);//��չNextNum��һ���ڵ�
			B.ExistChildNum[NextNum]++;//NextNum���ڵ��ӽڵ�������1
			//cout<<"Msg  Toatl UCT Times : "<<Total<<endl;
			B.RefreshAvgValue();//����ȫ����Ҫ���ӽڵ��ˢ��һ������ֵ��
			return B.AvgValue;
		}
		else//�ƽ�,Ҳ����˵����Ӹ��������еĽڵ㶼�Ѿ������Թ��ˡ�
		{
			int BestNum=0;
			int BestNodeNum=0;
			float BestNodeUCBValue = 0;
			//����Ҫ��ѡ������UCTֵ
			if(SinglePiece)//��ѡ��
			{
				for(int i =0;i<B.ExistChildNum[NextNum];i++)//һ����ChildNum���ڵ㣬���Ҷ��Ѿ���̽�����ˡ�Ѱ��ȫ���ӽڵ�������UCBֵ��
				{
					B.ChildNodes[NextNum][i]->RefreshUCBValue(Total);//���¼���ڵ��UCBֵ
					if(B.ChildNodes[NextNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum=NextNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[NextNum][i]->UCBValue;
					}
				}
			}
			else//˫ѡ��
			{	
				for(int i =0;i<B.ExistChildNum[LargerNum];i++)//�Ȳ���LargerNum������UCB��
				{
					B.ChildNodes[LargerNum][i]->RefreshUCBValue(Total);//���¼���ڵ��UCBֵ
					if(B.ChildNodes[LargerNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum=LargerNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[LargerNum][i]->UCBValue;
					}
				}
				for(int i =0;i<B.ExistChildNum[SmallerNum];i++)//�ٲ���SmallerNum������UCB��
				{
					B.ChildNodes[SmallerNum][i]->RefreshUCBValue(Total);//���¼���ڵ��UCBֵ
					if(B.ChildNodes[SmallerNum][i]->UCBValue>=BestNodeUCBValue)
					{
						BestNum = SmallerNum;
						BestNodeNum =i;
						BestNodeUCBValue = B.ChildNodes[SmallerNum][i]->UCBValue;
					}
				}
			}
			//cout<<"Msg: BestUCB is Number["<<BestNum<<"] Node["<<BestNodeNum<<"]"<<endl;
			//���UCBѡȡ��������������ڵ��ֵ�����UCB��ChildNode[BestNum][BestNodeNum]
			UCT_Iteration(*B.ChildNodes[BestNum][BestNodeNum],Total);
			B.RefreshAvgValue();//ˢ����һ������
			return B.AvgValue;
		}
	}
	return 0;
}
void UCTMove(Board &CB,int Piece)
{
	UCTNodeNum = 0;
	int f = CB.GetPieceFaction(Piece);
	UCTBoard UCTB(f,CB.board,CB.Step);//�����µ�UCT�ڵ�
	if(CB.GetPieceLife(Piece))//���������Ӵ��ڵĻ�
	{
		int n = f*Piece;
		for(int i=1;i<=6;i++)
			UCTB.PieceLife[i]=false;//�趨Ϊ������ʵ����Ϊ���ø��ڵ㲻����չ����ָ����Piece֮��Ľڵ�
		UCTB.PieceLife[n]=true;
	}
	else//�����ڵĻ�
	{
		int s=CB.GetSmallerPiece(Piece);
		int l=CB.GetLargerPiece(Piece);
		if(s!=0&&l==0)//ֻ��s����
		{
			int n = f*s;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//�趨Ϊ������ʵ����Ϊ���ø��ڵ㲻����չ����ָ����Piece֮��Ľڵ�
			UCTB.PieceLife[n]=true;
		}
		else if(s==0&&l!=0)//ֻ��l����
		{
			int n = f*l;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//�趨Ϊ������ʵ����Ϊ���ø��ڵ㲻����չ����ָ����Piece֮��Ľڵ�
			UCTB.PieceLife[n]=true;
		}
		else if(s!=0&&l!=0)//s��l������
		{
			int n = f*l;
			int m = f*s;
			for(int i=1;i<=6;i++)
				UCTB.PieceLife[i]=false;//�趨Ϊ������ʵ����Ϊ���ø��ڵ㲻����չ����ָ����Piece֮��Ľڵ�
			UCTB.PieceLife[n]=true;
			UCTB.PieceLife[m]=true;
		}
		else
		{
			cout<<"��������"<<endl;
			system("pause");
		}
	}
	
	int Total =0;
	clock_t start;	//���ü�ʱ���ı���
	start=clock();
	for(int t=0;t<UCT_TIMES;t++)
	{
		UCT_Iteration(UCTB,Total);
		double totaltime=(double)(clock()-start)/CLOCKS_PER_SEC;
		if(totaltime>=UCT_LIMIT)
			break;
	}
	int BestNum =0;
	int BestNode =0;
	int BestTimeNum = 0;
	int BestTimeNode = 0;
	float BestValue = 0;
	int BestTimeValue = 0;
	for(int p=1;p<=6;p++)//��Ϊ�ӽڵ���˿����ƶ���֮������Ӷ�������Ϊ�������������Լ�������Ӹ������Ϳ����ˡ�
	{
		if(UCTB.PieceLife[p])
		{
			for(int n=0;n<UCTB.ExistChildNum[p];n++)
			{
				if(UCTB.ChildNodes[p][n]->Times>=BestTimeNode)
				{
					BestTimeNum = p;
					BestTimeNode = n;
					BestTimeValue = UCTB.ChildNodes[p][n]->Times;
				}
			}
		}
	}
	Loc mLoc = UCTB.UCTMove[BestTimeNum][BestTimeNode].Loc;
	int mPiece = UCTB.UCTMove[BestTimeNum][BestTimeNode].Piece;
	CB.Move(mLoc,mPiece);
	Cprintf("========================Infomation==========================\n", 8);
	cout << "��ǰ�ڵ�ƽ������Ϊ" << 1 - UCTB.AvgValue << endl;
	cout << "�������ڵ����Ϊ" << UCTB.ChildNodes[BestTimeNum][BestTimeNode]->Times << endl;
	cout << "�������ڵ�����Ϊ" << UCTB.ChildNodes[BestTimeNum][BestTimeNode]->AvgValue << endl;
	cout << "����UCT�ܵ�������Ϊ" << Total << endl;
	Cprintf("============================================================\n", 8);

	for (int i = 0; i < UCTNodeNum; i++)
		delete UCTNodes[i];
}

UCTBoard *UCTNodes[UCT_TIMES] = {NULL};
int UCTNodeNum;

void DeleteUCTBoard(UCTBoard* Root)
{
	for (int n = 1; n <= 6; n++)
	{
		if (Root->ExistChildNum[n] > 0 && Root->ExistChildNum[n] < 4)
		{
			for (int i = 0; i < Root->ExistChildNum[n]; i++)
			{
				DeleteUCTBoard(Root->ChildNodes[n][i]);
				delete Root->ChildNodes[n][i];
			}
		}
	}
}
void DeleteUCTTree(UCTBoard Root)
{
	for (int n = 1; n <= 6; n++)
	{
		for (int i = 0; i < Root.ExistChildNum[n]; i++)
		{
			DeleteUCTBoard(Root.ChildNodes[n][i]);
			//delete Root.ChildNodes[n][i];
		}
	}
}
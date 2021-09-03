#pragma once
#include<QString>
class ChessPiece
{
public:
	enum ChessPieceType{JIANG,SHI,XIANG,MA,JU,PAO,ZU};
public:
	ChessPiece(int row = -1,int col = -1);
	~ChessPiece();

	QString getPieceName();		//根据棋子类型获取棋子名称

	int row;
	int col;
	int id;			//棋子的编号,
	bool isDead;	//棋子死了吗？
	bool isRed;		//是红旗还是黑棋
	ChessPiece::ChessPieceType type;	//啥棋子？
};

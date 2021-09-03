#include "ChessPiece.h"

ChessPiece::ChessPiece(int row, int col)
	:row(row),col(col),isRed(false)
{
}

ChessPiece::~ChessPiece()
{
}

QString ChessPiece::getPieceName()
{
	//黑 将,士,象,馬,車,炮,卒
	//红 帥,仕,相,馬,車,炮,兵
	switch (type)
	{
	case ChessPiece::JIANG:
		return isRed ? "帥" : "将";
	case ChessPiece::SHI:
		return isRed ? "仕" : "士";
	case ChessPiece::XIANG:
		return isRed ? "相" : "象";
	case ChessPiece::MA:
		return isRed ? "馬" : "馬";
	case ChessPiece::JU:
		return isRed ? "車" : "車";
	case ChessPiece::PAO:
		return isRed ? "炮" : "炮";
	case ChessPiece::ZU:
		return isRed ? "兵" : "兵";
	default:
		return isRed ? "Red" : "Black";
	}
}

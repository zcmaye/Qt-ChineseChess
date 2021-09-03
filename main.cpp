#include<QApplication>
#include"chessboard.h"

int main(int argc,char*argv[])
{
    QApplication a(argc,argv);

    ChessBoard chessBoard;
    chessBoard.show();

    return a.exec();
}

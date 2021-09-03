#include "chessboard.h"
#include<QPainter>
#include<QDebug>
#include<QStaticText>
ChessBoard::ChessBoard(QWidget *parent) 
    : QWidget(parent)
    ,topLeft(50,50)
    ,gridWidth(60)
    ,rows(10)
    ,cols(9)
{
    this->resize(600, 640);
    this->setPalette(QPalette(qRgb(209, 191, 153)));
    initChessPiece();
    setGamerColor(true);
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::RenderHint::Antialiasing);      //抗锯齿

    drawChessBoard(painter);
    drawChessPiece(painter);

}

void ChessBoard::initChessPiece()
{
#if 0
    int cnt = 0;
    //遍历二维数组
    for (int i = 0; i < rows; i++)
    {
        int temp = 0;
        for (int k = 0; k < cols; k++)
        {
            //黑棋初始化
            if (i <= 4)
            {
                ChessPiece piece;
                piece.type = ChessPiece::ChessPieceType(66);
                if (i == 0)//第1行
                {
                    if (k <= 4)
                    {
                        temp = 4 - k;   //4 3 2 1 0
                    }
                    else
                    {
                        temp = k - 4;//0 1 2 3 4 
                    }
                    piece.type = ChessPiece::ChessPieceType(temp);
                }
                //设置炮
                if (i == 2 && (k == 1 || k == 7))
                {
                    piece.type = ChessPiece::PAO;
                }
                //设置小兵
                if (i == 3 && k % 2 == 0)
                {
                    piece.type = ChessPiece::ZU;
                }
                piece.row = i;
                piece.col = k;
                chessPieces.push_back (piece);
            }
            else//红旗初始化
            {
                ChessPiece piece;
                piece.type = ChessPiece::ChessPieceType(66);
                if (i == 9)//最后一行
                {
                    if (k <= 4)
                    {
                        temp = 4 - k;   //4 3 2 1 0
                    }
                    else
                    {
                        temp = k - 4;//0 1 2 3 4 
                    }
                    piece.type = ChessPiece::ChessPieceType(temp);
                }
                //设置炮
                if (i == 7 && (k == 1 || k == 7))
                {
                    piece.type = ChessPiece::PAO;
                }
                //设置小兵
                if (i == 6 && k % 2 == 0)
                {
                    piece.type = ChessPiece::ZU;
                }
                piece.row = i;
                piece.col = k;
                chessPieces.push_back(piece);
            }
        }
    }
#else
    int cnt = 0;
    //遍历二维数组
    for (int i = 0; i < rows; i++)
    {
        int temp = 0;
        for (int k = 0; k < cols; k++)
        {
            ChessPiece piece(i,k);
            piece.type = ChessPiece::ChessPieceType(66);
            if (i == 0 || i == 9)//第1行 最后一行
            {
                if (k <= 4)
                {
                    temp = 4 - k;   //4 3 2 1 0
                }
                else
                {
                    temp = k - 4;//0 1 2 3 4 
                }
                piece.type = ChessPiece::ChessPieceType(temp);
                piece.id = cnt++;
                chessPieces.push_back(piece);
            }
            //设置炮
            else if ((i == 2 || i == 7) && (k == 1 || k == 7))
            {
                piece.type = ChessPiece::PAO;
                piece.id = cnt++;
                chessPieces.push_back(piece);
            }
            //设置小兵
            else if ((i == 3 || i == 6) && k % 2 == 0)
            {
                piece.type = ChessPiece::ZU;
                piece.id = cnt++;
                chessPieces.push_back(piece);
            }
           
        }
    }
#endif
}

void ChessBoard::setGamerColor(bool isRed)
{
    for (ChessPiece& piece : chessPieces)
    {
        if (piece.id >= 16)
            piece.isRed = isRed;
        else
            piece.isRed = !isRed;
    }
}


void ChessBoard::drawChessBoard(QPainter& painter)
{
    painter.save();     //保存状态
    painter.setPen(QPen(Qt::black, 2));
    //10条横线
    for (size_t i = 0; i <= 9; i++)
    {
        painter.drawLine(QPoint(topLeft.x(), topLeft.y() + i * gridWidth),QPoint(topLeft.x() + 8 * gridWidth, topLeft.y() + i * gridWidth));
    }
    //9条竖线
    for (size_t i = 0; i <= 8; i++)
    {
        if (i == 0 || i == 8)
        {
            painter.drawLine(topLeft + QPoint(i * gridWidth, 0), topLeft + QPoint(i * gridWidth, 9 * gridWidth));
        }
        else
        {
            painter.drawLine(topLeft + QPoint(i * gridWidth, 0), topLeft + QPoint(i * gridWidth, 4 * gridWidth));
            painter.drawLine(topLeft + QPoint(i * gridWidth, 5*gridWidth), topLeft + QPoint(i * gridWidth, 9 * gridWidth));
        }
    }
    //外面的粗边框
    painter.setPen(QPen(Qt::black, 5));
    painter.drawRect(topLeft.x() - 10, topLeft.y() - 10, 8 * gridWidth + 20, 9 * gridWidth + 20);

    //中间的文字 楚河 汉界
    painter.setFont(QFont("楷体", 36));
    painter.drawStaticText(topLeft + QPoint(gridWidth + 10, 4 * gridWidth + 5), QStaticText("楚河"));
    painter.drawStaticText(topLeft + QPoint(5 * gridWidth + 10, 4 * gridWidth + 5), QStaticText("汉界"));

    //绘制米字格
    painter.setPen(QPen(Qt::black, 2));
    //top
    painter.drawLine(topLeft + QPoint(3 * gridWidth, 0), topLeft + QPoint(5 * gridWidth, 2 * gridWidth));
    painter.drawLine(topLeft + QPoint(3 * gridWidth, 2 * gridWidth), topLeft + QPoint(5 * gridWidth, 0));
    //buttom
    painter.drawLine(topLeft + QPoint(3 * gridWidth, 7*gridWidth), topLeft + QPoint(5 * gridWidth, 9 * gridWidth));
    painter.drawLine(topLeft + QPoint(3 * gridWidth, 9 * gridWidth), topLeft + QPoint(5 * gridWidth, 7*gridWidth));

    //绘制炮和卒位置的小标记 十字  0 十  1 𠃊  2 𠃎
    auto drawCross = [&](int x,int y,int type = 0)
    {
        int symbol = (type == 1 ? 1 : -1);      //符号
        int cnt = (type == 0) ? 2 : 1;
        for (size_t i = 0; i < cnt; i++)
        {           
            painter.drawLine(x + 3 * symbol, y - 3, x + symbol * 13, y - 3);
            painter.drawLine(x + 3 * symbol, y - 3, x + symbol * 03, y - 13);
            painter.drawLine(x + 3 * symbol, y + 3, x + symbol * 13, y + 3);
            painter.drawLine(x + 3 * symbol, y + 3, x + symbol * 03, y + 13);
            symbol = -symbol;
        }
      /*  switch (type)
        {
        case 0:
            painter.drawLine(x + 5, y - 5, x + 15, y - 5);
            painter.drawLine(x + 5, y - 5, x + 5, y - 15);
            painter.drawLine(x + 5, y + 5, x + 15, y + 5);
            painter.drawLine(x + 5, y + 5, x + 5, y + 15);
            painter.drawLine(x - 5, y - 5, x - 15, y - 5);
            painter.drawLine(x - 5, y - 5, x - 5, y - 15);
            painter.drawLine(x - 5, y + 5, x - 15, y + 5);
            painter.drawLine(x - 5, y + 5, x - 5, y + 15);
            break;
        case 1:
            painter.drawLine(x + 5, y - 5, x + 15, y - 5);
            painter.drawLine(x + 5, y - 5, x + 5, y - 15);
            painter.drawLine(x + 5, y + 5, x + 15, y + 5);
            painter.drawLine(x + 5, y + 5, x + 5, y + 15);
            break;
        case 2:
            painter.drawLine(x - 5, y - 5, x - 15, y - 5);
            painter.drawLine(x - 5, y - 5, x - 5, y - 15);
            painter.drawLine(x - 5, y + 5, x - 15, y + 5);
            painter.drawLine(x - 5, y + 5, x - 5, y + 15);
            break;
        }
        */
    };
    for (size_t i = 0; i <= 9; i++)
    {
        for (size_t k = 0; k <= 8; k++)
        {
            if ((i > 0 && i < 9 && k>0 && k < 8) &&         //第一列和最后一列先不设置
                (i == 3 || i == 6) && k % 2 == 0 ||         //两排卒
                (i==2 || i== 7) && (k==1 ||  k== 7)         //两排炮
                )
            {
                drawCross(topLeft.x()+ k*gridWidth, topLeft.y() + i * gridWidth);
            }
            if((i == 3 || i== 6) && k == 0)
                drawCross(topLeft.x() + k * gridWidth, topLeft.y() + i * gridWidth, 1);
            if ((i == 3 || i == 6) && k == 8)
                drawCross(topLeft.x() + k * gridWidth, topLeft.y() + i * gridWidth, 2);            
        }
    } 
    painter.restore();  //恢复状态
}

void ChessBoard::drawChessPiece(QPainter& painter)
{
    qDebug()<<"size:"<<chessPieces.size();
    painter.save();
    painter.setFont(QFont("楷体", 26));
    painter.setBrush(QBrush(qRgb(252, 215, 162)));

    for (ChessPiece& piece : chessPieces)
    {
        painter.setPen(QPen(piece.isRed ? Qt::red : Qt::black,2));      //设置棋子颜色

        QRect chessRect(topLeft.x() + piece.col * gridWidth - 25, topLeft.y() + piece.row * gridWidth - 25, 50, 50);
        painter.drawEllipse(chessRect);
        painter.drawText(chessRect, piece.getPieceName(), QTextOption(Qt::AlignmentFlag::AlignCenter));
    }
    painter.restore();
}

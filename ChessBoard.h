#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPoint>
#include "ChessPiece.h"
#include <QList>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget *parent = nullptr);
public:
    void paintEvent(QPaintEvent *event) override;

    void initChessPiece();                       //初始化棋子位置
    void setGamerColor(bool isRed = true);       //设置玩家棋子的颜色
    void drawChessBoard(QPainter& painter);      //绘制棋盘
    void drawChessPiece(QPainter& painter);      //绘制棋子
signals:
private:
    QPoint topLeft;     //棋盘左上角坐标
    qint16 gridWidth;   //棋盘格子宽度
    qint16 rows;        //棋盘线条行数
    qint16 cols;        //棋盘线条列数

    QList<ChessPiece> chessPieces;
};

#endif // CHESSBOARD_H

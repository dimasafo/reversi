#ifndef DrawingCreator_H
#define DrawingCreator_H

#include <QDialog>
#include <QLineEdit>

#include "chessboard.h"

//core
#include "game.h"
#include "boarddata.h"




class GuiBase : public QDialog
{
     Q_OBJECT

public:
    GuiBase(QWidget* parent = NULL);

signals:
    void setGameStatusText(const QString &);

public slots:
    void cellClicked(int, int);
    void close();
    void ok();

private slots:
    void startGame();
    void onFinishGame();
    void giveUp();

    void addValue();
    void computerGo();

private:
    void syncDataWithBoard(const BoardData* const boardData);

    Game* curGame_;

    MyChessBoard* chessBoard_;

    QLineEdit* rowsField_;
    QLineEdit* columnsField_;
    QPushButton* computerGoButton_;
    QPushButton* giveUpButton_;
};

#endif

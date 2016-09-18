#ifndef _CELL_H_
#define _CELL_H_


#include <QWidget>

enum CellState
{
    CS_EMPTY,
    CS_FILLED
};

class MyCell : public QWidget
{
    Q_OBJECT

public:
    MyCell(size_t row, size_t column, QColor color = QColor(Qt::GlobalColor::red), size_t sizePx = 40, QWidget *parent = 0);
    virtual ~MyCell();

signals:
    void signalClicked(int, int);

public slots:
    void setFilled(int, int, int, int, int);
    void setEmpty(int row, int column);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    virtual void mouseReleaseEvent(QMouseEvent* event) override;

private:
    size_t		row_;
    size_t		column_;

    CellState	state_;
    QColor		filledColor_;
};


#endif //_CELL_H_

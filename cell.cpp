#include <QPainter>

#include "cell.h"


MyCell::MyCell(size_t row, size_t column, QColor color, size_t sizePx, QWidget *parent)
    : QWidget(parent)
    , row_(row)
    , column_(column)
    , state_(CS_EMPTY)
    , filledColor_(33, 66, 99) //default
{
    setFixedSize(sizePx, sizePx);

    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, color);
    this->setAutoFillBackground(true);
    this->setPalette(Pal);
}

MyCell::~MyCell()
{

}

void MyCell::paintEvent(QPaintEvent *)
{
    if(state_ == CS_EMPTY)
        return;

    size_t size = rect().width();

    QPainter painter(this);

    QPoint center = QPoint(size/2, size/2);
    int rad = size / 4;

    QBrush brush = painter.brush();
    brush.setStyle(Qt::SolidPattern);

    if(state_ == CS_FILLED)
        brush.setColor(filledColor_);

    painter.setBrush(brush);
    painter.drawEllipse(center, rad, rad);
}

void MyCell::mouseReleaseEvent(QMouseEvent* event)
{
    QWidget::mouseReleaseEvent(event);

    emit signalClicked(row_, column_);
}

void MyCell::setFilled(int row, int column, int r, int g, int b)
{
    if(row != row_ || column != column_)
        return;

    state_ = CS_FILLED;

    filledColor_ = QColor(r, g, b);

    update();
}

void MyCell::setEmpty(int row, int column)
{
    if(row != row_ || column != column_)
        return;

    state_ = CS_EMPTY;

    update();
}

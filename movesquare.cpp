#include <QtWidgets>
#include "movesquare.h"

MoveSquare::MoveSquare(int y, int x, std::vector<std::pair<int, int> > move, QColor color) {
    x_ = x;
    y_ = y;
    move_ = move;
    color_ = color;
}

QRectF MoveSquare::boundingRect() const {
    return QRectF(x_*100, y_*100, width_, width_);
}

QPainterPath MoveSquare::shape() const {
    QPainterPath path;
    path.addRect(x_*100, y_*100, width_, width_);
    return path;
}

void MoveSquare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_*100, this->y_*100, this->width_, this->width_));
    painter->setBrush(b);
}

void MoveSquare::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit moveSelected(this);
    }
}

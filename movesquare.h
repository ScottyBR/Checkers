#ifndef MOVESQUARE_H
#define MOVESQUARE_H

#include <QObject>
#include <QGraphicsObject>
#include <vector>

class MoveSquare : public QObject, public QGraphicsItem {
    Q_OBJECT

    public:
        MoveSquare(int x, int y, std::vector<std::pair<int,int>> move, QColor color = QColor(0, 255, 255, 63));
        int getX() { return x_; }
        int getY() { return y_; }
        std::vector<std::pair<int,int>> getMove() { return move_; }

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    private:
        int x_;
        int y_;
        QColor color_;
        static const int width_ = 100;
        std::vector<std::pair<int,int>> move_;

    signals:
        void moveSelected(MoveSquare *ms);

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // MOVESQUARE_H

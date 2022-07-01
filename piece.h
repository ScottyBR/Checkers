#ifndef PIECE_H
#define PIECE_H

#include <QObject>
#include <QGraphicsObject>
#include <vector>
#include <set>

enum pieceType {pawn, king, queen};

class Piece : public QObject, public QGraphicsItem {
    Q_OBJECT

    public:
        Piece();
        int getPlayer() { return player_; }
        int getX() { return x_; }
        int getY() { return y_; }
        int getWidth() { return width_; }
        QColor getColor() { return color_; }
        pieceType getType() { return type_; }
        void setPlayer(int p) {player_ = p; }
        void setX(int x) { x_ = x; }
        void setY(int y) { y_ = y; }
        void setColor(QColor c) { color_ = c; }
        void setType(pieceType t) {type_ = t; }
        virtual std::set<std::vector<std::pair<int,int>>> getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos) = 0;
        virtual std::set<std::vector<std::pair<int,int>>> getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build) = 0;
        virtual std::vector<std::pair<int,int>> getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x) = 0;
        std::vector<std::pair<int,int>> addVecs(std::vector<std::pair<int,int>> v1, std::vector<std::pair<int,int>> v2);
        void printMoves(std::set<std::vector<std::pair<int,int>>> moves_);
        void printMove(std::vector<std::pair<int,int>> move_);

//        virtual QRectF boundingRect() = 0;
//        virtual QPainterPath shape() = 0;
//        virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) = 0;

    protected:
        static const int width_ = 80;
        int player_;
        int x_;
        int y_;
        QColor color_;
        pieceType type_;
};

class Pawn : public Piece {
    Q_OBJECT

    public:
        Pawn(QColor color, const int y, const int x, const int player, pieceType type = pieceType::pawn);
        std::set<std::vector<std::pair<int,int>>> getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos);
        std::set<std::vector<std::pair<int,int>>> getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build);
        std::vector<std::pair<int,int>> getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void pawnSelected(Pawn *p);
};


class King : public Piece {
    Q_OBJECT

    public:
        King(QColor color, const int y, const int x, const int player, pieceType type = pieceType::king);
        std::set<std::vector<std::pair<int,int>>> getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos);
        std::set<std::vector<std::pair<int,int>>> getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build);
        std::vector<std::pair<int,int>> getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void kingSelected(King *k);
};


class Queen : public Piece {
    Q_OBJECT

    public:
        Queen(QColor color, const int y, const int x, const int player, pieceType type = pieceType::queen);
        std::set<std::vector<std::pair<int,int>>> getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos);
        std::set<std::vector<std::pair<int,int>>> getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build);
        std::vector<std::pair<int,int>> getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x);

        QRectF boundingRect() const override;
        QPainterPath shape() const override;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    signals:
        void queenSelected(Queen *q);
};

#endif // PIECE_H

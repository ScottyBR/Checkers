#ifndef CHECKERS_H
#define CHECKERS_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "piece.h"
#include "movesquare.h"
#include "introdialog.h"
#include "gameoverdialog.h"

namespace Ui {
class Checkers;
}

class Checkers : public QMainWindow {
    Q_OBJECT

    public:
        explicit Checkers(QWidget *parent = 0);
        ~Checkers();
        void printBoard();
        void clearHighlights();
        int isGameOver();
        void createStartBoard();
        void createTestBoard();
        void createPiece(pieceType t, int y, int x, int p);

    private:
        Ui::Checkers *ui;
        QGraphicsScene *scene;
        static const int width_ = 100;
        int turn_;
        Piece *current_piece;
        std::vector<std::vector<Piece*>> board_;
        std::vector<MoveSquare*> move_squares;
        IntroDialog *id;
        GameOverDialog *god;

    private slots:
        void pieceSelectedSlot(Piece *p);
        void moveSelectedSlot(MoveSquare *ms);
};

#endif // CHECKERS_H

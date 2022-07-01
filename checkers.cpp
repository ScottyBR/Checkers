#include <QDebug>
#include "checkers.h"
#include "ui_checkers.h"

Checkers::Checkers(QWidget *parent) : QMainWindow(parent), ui(new Ui::Checkers) {
    //initialize ui, view and scene
    ui->setupUi(this);
    QGraphicsView *view = ui->game_board;
    scene = new QGraphicsScene();
    view->setScene(scene);
    turn_ = 0;
    current_piece = nullptr;
    view->setSceneRect(1, 1, view->frameSize().width()-2, view->frameSize().height()-2);

    //draw board
    QPen pen_black(Qt::black);
    QBrush brush_black(Qt::black);
    QBrush brush_white(Qt::white);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i%2+j%2)%2 == 0) {
                scene->addRect(j*width_, i*width_, width_, width_, pen_black, brush_white);
            }
            else {
                scene->addRect(j*width_, i*width_, width_, width_, pen_black, brush_black);
            }
        }
    }

    //initialize board
    board_ = std::vector<std::vector<Piece*>> (8, std::vector<Piece*> (8, nullptr));

    //create pieces
    createStartBoard();
    //createTestBoard();

//    id = new IntroDialog;
//    id->setModal(true);
//    id->exec();
}

Checkers::~Checkers() {
    delete ui;
}

void Checkers::createStartBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            createPiece(pieceType::pawn, i, j*2-(i%2)+1, 0);
        }
    }
    for (int i = 5; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            createPiece(pieceType::pawn, i, j*2-(i%2)+1, 1);
        }
    }
}

void Checkers::createTestBoard() {
    //crash test
    createPiece(pieceType::queen, 2, 5, 0);
    createPiece(pieceType::king, 2, 7, 0);
    createPiece(pieceType::king, 3, 6, 1);


    //king test
//    King *k = new King(Qt::darkGray, 3, 2, 0);
//    scene->addItem(k);
//    connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
//    board_[3][2] = k;
//    k = new King(Qt::darkGray, 0, 1, 0);
//    scene->addItem(k);
//    connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
//    board_[0][1] = k;
//    k = new King(Qt::darkRed, 4, 3, 1);
//    scene->addItem(k);
//    connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
//    board_[4][3] = k;
//    k = new King(Qt::darkRed, 4, 5, 1);
//    scene->addItem(k);
//    connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
//    board_[4][5] = k;
//    k = new King(Qt::darkRed, 6, 5, 1);
//    scene->addItem(k);
//    connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
//    board_[6][5] = k;

    //pawn test + pawn to queen test
//    Pawn *p = new Pawn(Qt::darkGray, 0, 1, 0);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[0][1] = p;
//    p = new Pawn(Qt::darkRed, 1, 2, 1);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[1][2] = p;
//    p = new Pawn(Qt::darkRed, 3, 4, 1);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[3][4] = p;
//    p = new Pawn(Qt::darkRed, 3, 2, 1);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[3][2] = p;

    //pawn to king upgrade test
//    Pawn *p = new Pawn(Qt::darkGray, 6, 3, 0);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[6][3] = p;
//    p = new Pawn(Qt::darkRed, 1, 2, 1);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[1][2] = p;

    //queen test
//    Queen *q = new Queen(Qt::darkGray, 3, 2, 0);
//    scene->addItem(q);
//    connect(q, &Queen::queenSelected, this, &Checkers::pieceSelectedSlot);
//    board_[3][2] = q;
//    q = new Queen(Qt::darkGray, 0, 1, 0);
//    scene->addItem(q);
//    connect(q, &Queen::queenSelected, this, &Checkers::pieceSelectedSlot);
//    board_[0][1] = q;
//    q = new Queen(Qt::darkRed, 4, 3, 1);
//    scene->addItem(q);
//    connect(q, &Queen::queenSelected, this, &Checkers::pieceSelectedSlot);
//    board_[4][3] = q;
//    q = new Queen(Qt::darkRed, 4, 5, 1);
//    scene->addItem(q);
//    connect(q, &Queen::queenSelected, this, &Checkers::pieceSelectedSlot);
//    board_[4][5] = q;

    //Game over test
//    createPiece(pieceType::pawn, 0, 1, 0);
//    Pawn *p = new Pawn(Qt::darkRed, 1, 2, 1);
//    scene->addItem(p);
//    connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
//    board_[1][2] = p;
}

void Checkers::createPiece(pieceType t, int y, int x, int player) {
    QColor c;

    if (player == 0) {
        c = Qt::darkGray;
    }
    else {
        c = Qt::darkRed;
    }

    switch (t) {
        case pieceType::pawn: {
            Pawn *p = new Pawn(c, y, x, player);
            connect(p, &Pawn::pawnSelected, this, &Checkers::pieceSelectedSlot);
            scene->addItem(p);
            board_[y][x] = p;
            break;
        }
        case pieceType::king: {
            King *k = new King(c, y, x, player);
            connect(k, &King::kingSelected, this, &Checkers::pieceSelectedSlot);
            scene->addItem(k);
            board_[y][x] = k;
            break;
        }
        case pieceType::queen: {
            Queen *q = new Queen(c, y, x, player);
            connect(q, &Queen::queenSelected, this, &Checkers::pieceSelectedSlot);
            scene->addItem(q);
            board_[y][x] = q;
            break;
        }
    }
}

void Checkers::pieceSelectedSlot(Piece *p) {
    clearHighlights();
    //printBoard();
    current_piece = p;

    //get potential moves for current piece
    if (turn_ % 2 == p->getPlayer()) {
        std::set<std::vector<std::pair<int,int>>> all_moves = p->getAllMoves(board_, std::pair<int,int>(p->getY(), p->getX()));
        for (std::vector<std::pair<int,int>> move_ : all_moves) {
            if (move_.size() > 0) {
                MoveSquare *ms = new MoveSquare(move_.back().first, move_.back().second, move_);
                scene->addItem(ms);
                connect(ms, &MoveSquare::moveSelected, this, &Checkers::moveSelectedSlot);
                move_squares.push_back(ms);
            }
        }
    }

    update();
}

void Checkers::moveSelectedSlot(MoveSquare *ms) {
    //if pieces were jumped remove those pieces
    std::vector<std::pair<int,int>> move_ = ms->getMove();

    for (std::pair<int,int> i : move_) {
        int y = i.first, x = i.second;
        if (board_[y][x] != nullptr) {
            Piece *p = board_[y][x];
            scene->removeItem(p);
            board_[y][x] = nullptr;
        }
    }

    //update board
    board_[current_piece->getY()][current_piece->getX()] = nullptr;
    board_[ms->getY()][ms->getX()] = current_piece;

    //update piece
    current_piece->setX(ms->getX());
    current_piece->setY(ms->getY());

    //update piece location
    scene->removeItem(current_piece);
    scene->addItem(current_piece);

    clearHighlights();

    //check if double jump for queen upgrade
    if (move_.size() > 4) {
        createPiece(pieceType::queen, current_piece->getY(), current_piece->getX(), current_piece->getPlayer());
        scene->removeItem(current_piece);
    }
    //check if piece reached end of board for king upgrade
    else {
        int player = current_piece->getPlayer();
        int pY = current_piece->getY();
        if ((pY == 7 && player == 0) || (pY == 0 && player == 1)) {
            if (current_piece->getType() == pieceType::pawn) {
                createPiece(pieceType::king, current_piece->getY(), current_piece->getX(), current_piece->getPlayer());
                scene->removeItem(current_piece);
            }
        }
    }

    scene->update();
    turn_++;

    int game_over = isGameOver();
    if (game_over != -1) {
        std::string winner;
        if (game_over == 0) {
            winner = "Gray";
        }
        else {
            winner = "Red";
        }

        god = new GameOverDialog(winner);
        god->setModal(true);
        god->exec();

        this->close();
    }
}

void Checkers::printBoard() {
    for (int i = 0; i < 8; i++) {
        std::string rowString = "";
        for (int j = 0; j < 8; j++) {
            if (board_[i][j] == nullptr) {
                rowString += "- ";
            }
            else {
                if (board_[i][j]->getPlayer() == 0) {
                    rowString += "0 ";
                }
                else {
                    rowString += "1 ";
                }
            }
        }
        qDebug() << rowString.c_str();
    }
    qDebug() << "";
}

void Checkers::clearHighlights() {
    //remove previous movesquares from ui
    for (MoveSquare* i : move_squares) {
        scene->removeItem(i);
    }
    move_squares.clear();
}

int Checkers::isGameOver() {
    int sum0 = 0, sum1 = 0;

    for (std::vector<Piece*> i : board_) {
        for (Piece *p : i) {
            if (p != nullptr) {
                if (p->getPlayer() == 0) {
                    sum0++;
                }
                else {
                    sum1++;
                }
            }
        }
    }

    if (sum0 == 0) {
        return 1;
    }
    else if (sum1 == 0){
        return 0;
    }
    else {
        return -1;
    }
}

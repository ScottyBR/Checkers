#include <QtWidgets>
#include "piece.h"

Piece::Piece() { }

std::vector<std::pair<int,int>> Piece::addVecs(std::vector<std::pair<int,int>> v1, std::vector<std::pair<int,int>> v2) {
    for (std::pair<int,int> i : v2) {
        v1.push_back(i);
    }

    return v1;
}

void Piece::printMoves(std::set<std::vector<std::pair<int,int>>> moves_) {
    std::string moves_str = "Moves length: " + std::to_string(moves_.size());
    qDebug() << moves_str.c_str();
    for (std::vector<std::pair<int,int>> move_ : moves_) {
        std::string move_str = "Move length: " + std::to_string(move_.size());
        qDebug() << move_str.c_str();
        std::string string_move = "";
        for (std::pair<int,int> i : move_) {
            string_move += std::to_string(i.first) + " " + std::to_string(i.second) + ", ";
        }
        qDebug() << string_move.c_str();
    }
    qDebug() << " ";
}

void Piece::printMove(std::vector<std::pair<int,int>> move_) {
    for (std::pair<int,int> i : move_) {
        qDebug() << i.first << i.second;
    }
    qDebug();
}

Pawn::Pawn(QColor color, const int y, const int x, const int player, pieceType type) {
    color_ = color;
    x_ = x;
    y_ = y;
    player_ = player;
    type_ = type;
}

//get potential moves for a pawn
std::set<std::vector<std::pair<int,int>>> Pawn::getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos) {
    //initialize vector with starting tile
    std::vector<std::pair<int,int>> temp_vec;
    temp_vec.push_back(pos);
    std::set<std::vector<std::pair<int,int>>> all_moves = getCurrentMoves(b, temp_vec);
    std::set<std::vector<std::pair<int,int>>> final_moves;

    while (!all_moves.empty()) {
        //get move from back of all_moves
        std::vector<std::pair<int,int>> move_to_build = *std::prev(all_moves.end());
        all_moves.erase(std::prev(all_moves.end()));

        //check if move is terminal
        //if yes add to final_moves
        if (move_to_build.back() == std::pair<int,int>(-1,-1)) {
            //make final move vector
            if (move_to_build.size() > 2) {
                move_to_build.pop_back();
                final_moves.insert(move_to_build);
            }
        }
        //else check for potential jump
        else {
            std::set<std::vector<std::pair<int,int>>> current_move = getCurrentMoves(b, move_to_build);
            for (std::vector<std::pair<int,int>> i : current_move) {
                all_moves.insert(i);
            }
            final_moves.insert(move_to_build);
        }
    }

    return final_moves;
}

std::set<std::vector<std::pair<int,int>>> Pawn::getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build) {
    std::set<std::vector<std::pair<int,int>>> moves_;
    //check left and right for open tile or jump
    if (player_ == 0) {
        if (x_ > 0) {
            moves_.insert(getMove(b, move_to_build, 1, -1));
        }
        if (x_ < 7) {
            moves_.insert(getMove(b, move_to_build, 1, 1));
        }
    }
    else {
        if (x_ > 0) {
            moves_.insert(getMove(b, move_to_build, -1, -1));
        }
        if (x_ < 7) {
            moves_.insert(getMove(b, move_to_build, -1, 1));
        }
    }
    return moves_;
}

//get possible moves from pos
std::vector<std::pair<int,int>> Pawn::getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x) {
    std::pair<int,int> pos = move_to_build.back();

    //check if move tile is valid
    if (pos.first+y >= 0 && pos.first+y <= 7 && pos.second+x >= 0 && pos.second+x <= 7) {
        //tile is open
        if (b[pos.first+y][pos.second+x] == nullptr && move_to_build.size() == 1) {
            move_to_build.push_back(std::pair<int,int>(pos.first+y, pos.second+x));
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
        //tile is occupied; check if it's an opponents piece and if jump is available
        else if (b[pos.first+y][pos.second+x] != nullptr && b[pos.first+y][pos.second+x]->getPlayer() != player_) {
            if (pos.first+(y*2) >= 0 && pos.first+(y*2) <= 7 && pos.second+(x*2) >= 0 && pos.second+(x*2) <= 7) {
                if (b[pos.first+(y*2)][pos.second+(x*2)] == nullptr) {
                    move_to_build.push_back(std::pair<int,int>(pos.first+(y), pos.second+(x)));
                    move_to_build.push_back(std::pair<int,int>(pos.first+(y*2), pos.second+(x*2)));
                }
                else {
                    move_to_build.push_back(std::pair<int,int>(-1,-1));
                }
            }
            else {
                move_to_build.push_back(std::pair<int,int>(-1,-1));
            }
        }
        else {
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
    }
    else {
        move_to_build.push_back(std::pair<int,int>(-1,-1));
    }
    qDebug() << "Here";
    return move_to_build;
}

QRectF Pawn::boundingRect() const {
    return QRectF(x_*100+10, y_*100+10, width_, width_);
}

QPainterPath Pawn::shape() const {
    QPainterPath path;
    path.addEllipse(x_*100+10, y_*100+10, width_, width_);
    return path;
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    QBrush b = painter->brush();
    painter->setBrush(QBrush(color_));

    painter->drawEllipse(QRect(this->x_*100+10, this->y_*100+10, this->width_, this->width_));
    painter->setBrush(b);
}

void Pawn::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit pawnSelected(this);
    }
}



King::King(QColor color, const int y, const int x, const int player, pieceType type) {
    color_ = color;
    x_ = x;
    y_ = y;
    player_ = player;
    type_ = type;
}

//get potential moves for a king
std::set<std::vector<std::pair<int,int>>> King::getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos) {
    //initialize vector with starting tile
    std::vector<std::pair<int,int>> temp_vec;
    temp_vec.push_back(pos);
    std::set<std::vector<std::pair<int,int>>> all_moves = getCurrentMoves(b, temp_vec);
    std::set<std::vector<std::pair<int,int>>> final_moves;

    while (!all_moves.empty()) {
        //get move from back of all_moves
        std::vector<std::pair<int,int>> move_to_build = *std::prev(all_moves.end());
        all_moves.erase(std::prev(all_moves.end()));

        //check if move is terminal
        //if yes add to final_moves
        if (move_to_build.back() == std::pair<int,int>(-1,-1)) {
            //check if move has more than 1 pos
            if (move_to_build.size() > 2) {
                move_to_build.pop_back();
                final_moves.insert(move_to_build);
            }
        }
        //else check for potential jump
        else {
            std::set<std::vector<std::pair<int,int>>> current_move = getCurrentMoves(b, move_to_build);
            for (std::vector<std::pair<int,int>> i : current_move) {
                all_moves.insert(i);
            }
        }
    }

    return final_moves;
}

std::set<std::vector<std::pair<int,int>>> King::getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build) {
    std::set<std::vector<std::pair<int,int>>> moves_;

    //check left for moves
    if (x_ > 0) {
        //left+down
        moves_.insert(getMove(b, move_to_build, 1, -1));
        //left+up
        moves_.insert(getMove(b, move_to_build, -1, -1));
    }
    //check right for moves
    if (x_ < 7) {
        //right+down
        moves_.insert(getMove(b, move_to_build, 1, 1));
        //right+up
        moves_.insert(getMove(b, move_to_build, -1, 1));
    }

    return moves_;
}

//get possible moves from pos
std::vector<std::pair<int,int>> King::getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x) {
    std::pair<int,int> pos = move_to_build.back();

    //tile is valid
    if (pos.first+y >= 0 && pos.first+y <= 7 && pos.second+x >= 0 && pos.second+x <= 7) {
        //tile is open
        if (b[pos.first+y][pos.second+x] == nullptr && move_to_build.size() == 1) {
            move_to_build.push_back(std::pair<int,int>(pos.first+y, pos.second+x));
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
        //tile is occupied; check if it's an opponents piece and if jump is available
        else if (b[pos.first+y][pos.second+x] != nullptr && b[pos.first+y][pos.second+x]->getPlayer() != player_) {
            //check if jump position is on board
            if (pos.first+(y*2) >= 0 && pos.first+(y*2) <= 7 && pos.second+(x*2) >= 0 && pos.second+(x*2) <= 7) {
                //check if jump position is open
                if (b[pos.first+(y*2)][pos.second+(x*2)] == nullptr) {
                    //check if jump position is not a duplicate jump
                    std::pair<int,int> dup_jump_check(pos.first+(y*2), pos.second+(x*2));
                    if (find(move_to_build.begin(), move_to_build.end(), dup_jump_check) != move_to_build.end()) {
                        move_to_build.push_back(std::pair<int,int>(-1,-1));
                    }
                    else {
                        move_to_build.push_back(std::pair<int,int>(pos.first+(y), pos.second+(x)));
                        move_to_build.push_back(std::pair<int,int>(pos.first+(y*2), pos.second+(x*2)));
                    }
                }
                else {
                    move_to_build.push_back(std::pair<int,int>(-1,-1));
                }
            }
            else {
                move_to_build.push_back(std::pair<int,int>(-1,-1));
            }
        }
        else {
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
    }
    else {
        move_to_build.push_back(std::pair<int,int>(-1,-1));
    }

    return move_to_build;
}

QRectF King::boundingRect() const {
    return QRectF(x_*100+10, y_*100+10, width_, width_);
}

QPainterPath King::shape() const {
    QPainterPath path;
    path.addEllipse(x_*100+10, y_*100+10, width_, width_);
    return path;
}

void King::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_));
    painter->drawEllipse(QRect(this->x_*100+10, this->y_*100+10, this->width_, this->width_));

    painter->setBrush(QBrush(Qt::yellow));
    painter->drawEllipse(QRect(this->x_*100+45, this->y_*100+45, 10, 10));

    painter->setBrush(b);
}

void King::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit kingSelected(this);
    }
}



Queen::Queen(QColor color, const int y, const int x, const int player, pieceType type) {
    color_ = color;
    x_ = x;
    y_ = y;
    player_ = player;
    type_ = type;
}

//get potential moves for a queen
std::set<std::vector<std::pair<int,int>>> Queen::getAllMoves(const std::vector<std::vector<Piece*>> b, std::pair<int,int> pos) {
    //initialize vector with starting tile
    std::vector<std::pair<int,int>> temp_vec;
    temp_vec.push_back(pos);
    std::set<std::vector<std::pair<int,int>>> all_moves = getCurrentMoves(b, temp_vec);
    std::set<std::vector<std::pair<int,int>>> final_moves;

    while (!all_moves.empty()) {
        //get move from back of all_moves
        std::vector<std::pair<int,int>> move_to_build = *std::prev(all_moves.end());
        all_moves.erase(std::prev(all_moves.end()));

        //check if move is terminal
        //if yes add to final_moves
        if (move_to_build.back() == std::pair<int,int>(-1,-1)) {
            //check if move has more than 1 pos
            if (move_to_build.size() > 2) {
                move_to_build.pop_back();
                final_moves.insert(move_to_build);
            }
        }
        //else check for potential jump
        else {
            std::set<std::vector<std::pair<int,int>>> current_move = getCurrentMoves(b, move_to_build);
            for (std::vector<std::pair<int,int>> i : current_move) {
                all_moves.insert(i);
            }
        }
    }

    return final_moves;
}

std::set<std::vector<std::pair<int,int>>> Queen::getCurrentMoves(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build) {
    std::set<std::vector<std::pair<int,int>>> moves_;

    //check left for moves
    if (x_ > 0) {
        //left+down
        moves_.insert(getMove(b, move_to_build, 1, -1));
        //left+up
        moves_.insert(getMove(b, move_to_build, -1, -1));
    }
    //check right for moves
    if (x_ < 7) {
        //right+down
        moves_.insert(getMove(b, move_to_build, 1, 1));
        //right+up
        moves_.insert(getMove(b, move_to_build, -1, 1));
    }
    //check cardinal directions
    if (move_to_build.size() == 1) {
        //check up
        moves_.insert(getMove(b, move_to_build, -2, 0));
        //check right
        moves_.insert(getMove(b, move_to_build, 0, 2));
        //check down
        moves_.insert(getMove(b, move_to_build, 2, 0));
        //check left
        moves_.insert(getMove(b, move_to_build, 0, -2));
    }

    return moves_;
}

//get possible moves from pos
std::vector<std::pair<int,int>> Queen::getMove(const std::vector<std::vector<Piece*>> b, std::vector<std::pair<int,int>> move_to_build, int y, int x) {
    //position is an open tile
    std::pair<int,int> pos = move_to_build.back();

    if (pos.first+y >= 0 && pos.first+y <= 7 && pos.second+x >= 0 && pos.second+x <= 7) {
        if (b[pos.first+y][pos.second+x] == nullptr && move_to_build.size() == 1) {
            move_to_build.push_back(std::pair<int,int>(pos.first+y, pos.second+x));
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
        //tile is occupied; check if it's an opponents piece and if jump is available
        else if (b[pos.first+y][pos.second+x] != nullptr && b[pos.first+y][pos.second+x]->getPlayer() != player_ && std::abs(x) < 2 && std::abs(y) < 2) {
            //check if jump position is on board
            if (pos.first+(y*2) >= 0 && pos.first+(y*2) <= 7 && pos.second+(x*2) >= 0 && pos.second+(x*2) <= 7) {
                //check if jump position is open
                if (b[pos.first+(y*2)][pos.second+(x*2)] == nullptr) {
                    //check if jump position is not a duplicate jump
                    std::pair<int,int> dup_jump_check(pos.first+(y*2), pos.second+(x*2));
                    if (find(move_to_build.begin(), move_to_build.end(), dup_jump_check) != move_to_build.end()) {
                        move_to_build.push_back(std::pair<int,int>(-1,-1));
                    }
                    else {
                        move_to_build.push_back(std::pair<int,int>(pos.first+(y), pos.second+(x)));
                        move_to_build.push_back(std::pair<int,int>(pos.first+(y*2), pos.second+(x*2)));
                    }
                }
                else {
                    move_to_build.push_back(std::pair<int,int>(-1,-1));
                }
            }
            else {
                move_to_build.push_back(std::pair<int,int>(-1,-1));
            }
        }
        else {
            move_to_build.push_back(std::pair<int,int>(-1,-1));
        }
    }
    else {
        move_to_build.push_back(std::pair<int,int>(-1,-1));
    }

    return move_to_build;
}

QRectF Queen::boundingRect() const {
    return QRectF(x_*100+10, y_*100+10, width_, width_);
}

QPainterPath Queen::shape() const {
    QPainterPath path;
    path.addEllipse(x_*100+10, y_*100+10, width_, width_);
    return path;
}

void Queen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(widget);

    QBrush b = painter->brush();

    painter->setBrush(QBrush(color_));
    painter->drawEllipse(QRect(this->x_*100+10, this->y_*100+10, this->width_, this->width_));

    painter->setBrush(QBrush(Qt::magenta));
    painter->drawEllipse(QRect(this->x_*100+45, this->y_*100+45, 10, 10));

    painter->setBrush(b);
}

void Queen::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit queenSelected(this);
    }
}

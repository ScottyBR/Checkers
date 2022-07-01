#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"

GameOverDialog::GameOverDialog(std::string winner, QWidget *parent) : QDialog(parent), ui(new Ui::GameOverDialog) {
    ui->setupUi(this);
    ui->gameOverLabel->setAlignment(Qt::AlignCenter);
    ui->winnerLabel->setAlignment(Qt::AlignCenter);
    std::string winner_text = winner + " wins!";
    ui->winnerLabel->setText(winner_text.c_str());
}

GameOverDialog::~GameOverDialog() {
    delete ui;
}

void GameOverDialog::on_closeButton_clicked() {
    this->close();
}

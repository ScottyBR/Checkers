#ifndef GAMEOVERDIALOG_H
#define GAMEOVERDIALOG_H

#include <QDialog>

namespace Ui {
    class GameOverDialog;
}

class GameOverDialog : public QDialog {
    Q_OBJECT

    public:
        explicit GameOverDialog(std::string winner, QWidget *parent = 0);
        ~GameOverDialog();

    private slots:
        void on_closeButton_clicked();

    private:
        Ui::GameOverDialog *ui;
};

#endif // GAMEOVERDIALOG_H

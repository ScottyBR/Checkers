#ifndef INTRODIALOG_H
#define INTRODIALOG_H

#include <QDialog>

namespace Ui {
    class IntroDialog;
}

class IntroDialog : public QDialog {
    Q_OBJECT

    public:
        explicit IntroDialog(QWidget *parent = 0);
        ~IntroDialog();

    private slots:
        void on_playGameButton_clicked();

    private:
        Ui::IntroDialog *ui;
};

#endif // INTRODIALOG_H

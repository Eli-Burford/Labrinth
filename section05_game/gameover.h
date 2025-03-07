#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QDialog>

namespace Ui {
class Gameover;
}

class Gameover : public QDialog
{
    Q_OBJECT

public:
    explicit Gameover(QWidget *parent = nullptr);
    ~Gameover();

private:
    Ui::Gameover *ui;

private slots:
    void exitDialog();
};

#endif // GAMEOVER_H

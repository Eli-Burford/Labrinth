#ifndef SCORE_H
#define SCORE_H

#include <QDialog>
#include <QtSql>
#include "defs.h"

namespace Ui {
class Score;
}

class Score : public QDialog
{
    Q_OBJECT

public:
    explicit Score(QWidget *parent = nullptr);
    ~Score();
    void setPlayerScore(int score);

private slots:
    void showPlayerData();
    void updatePlayerScore(const QString &playerName, int newScore); // Update the function declaration
    void Quit();
     void postQuery();
private:
    Ui::Score *ui;
    QSqlDatabase db;
    unsigned int player_score = 0;

};

#endif // SCORE_H

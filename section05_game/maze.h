
#ifndef MAZE_H
#define MAZE_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QtGlobal>
#include <QtDebug>
#include "score.h"
#include "obstacle.h"
#include "puck.h"
#include "player.h"
#include "ghostplayer.h"
#include "speedpowerup.h"
#include "victorypickup.h"
#include "defs.h"

namespace Ui {
class maze;
}

class maze : public QDialog
{
    Q_OBJECT

public:
    explicit maze(QWidget *parent = nullptr);
    ~maze();
    // networking interactions
    void test();
    float p1x();
    float p1y();
    float p2x();
    float p2y();
    float p3x();
    float p3y();
    float p4x();
    float p4y();
    float px(char temp);
    float py();
    void setP(int player, float x, float y);
    // player identifier (default '1')
    char playerNum = '1';


protected:
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::maze *ui;

    QGraphicsScene* scene = nullptr;
    QGraphicsTextItem *header,*display;

    Obstacle* obstacle = nullptr;
    Puck* puck = nullptr;

    // local players
    Player* player1 = nullptr;
    Player* player2 = nullptr;
    Player* player3 = nullptr;
    Player* player4 = nullptr;

    Player* players[4] = {new Player, new Player, new Player, new Player};  // Array to hold different player objects for easier manipulation


    // nonlocal players
    ghostPlayer* ghostplayer1 = nullptr;
    ghostPlayer* ghostplayer2 = nullptr;
    ghostPlayer* ghostplayer3 = nullptr;
    ghostPlayer* ghostplayer4 = nullptr;

    ghostPlayer* ghosts[4] = {ghostplayer1, ghostplayer2, ghostplayer3, ghostplayer4};


    //QPointF puckSpawnPoints[5] = {QPointF()};

    SpeedPowerUp* speedpowerup = nullptr;
    QTimer* spawnSpeed;
    int PowerupGen;
    Player* speedy = nullptr;
    //unsigned int p1Score, p2Score, p3Score, p4Score;

 //   QGraphicsTextItem *header,*display;     // Score header and display object ptrs
 //   int score = 0;                          // Current score

    void drawPerimeterLines();
    void spawnMaze1();
    void spawnMaze2();
    void spawnMaze3();
    void spawnPucks(int n);
    void spawnVictoryPickup();
    unsigned int puckCount;
    void spawnPlayer(int x, int y);
    void spawnGhostPlayers(int x, int y);
    unsigned int playerCount;
    void drawScoreDisplay();

    QPointF locations[6] = {QPointF(-270, -105), // Array to contain the spawn points for pickups
                            QPointF(-25, -110),
                            QPointF(350, -270),
                            QPointF(350, 295),
                            QPointF(45, 130),
                            QPointF(-SCENE_WIDTH/3, SCENE_HEIGHT/3)};

//    void playerCheck();

private slots:
    void playerCollision(Player*);
    void spawnSpeedPowerUp();
    void speedCountDown();

    void testSlot();

// networking signals
signals:
    void endGameSignal(char m);

};


#endif // MAZE_H

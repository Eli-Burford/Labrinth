#ifndef NETWORK_H
#define NETWORK_H


#include <QDialog>
#include <QDebug>
#include <QUdpSocket>
#include <QNetworkProxy>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QNetworkDatagram>
#include <QTimer>
#include "gamestate.h"
#include "maze.h"
#include "score.h"


const char joinRequest[] = "jr";
const char startGameMessage[] = "sg";

namespace Ui {
class Network;
}

class Network : public QDialog
{
    Q_OBJECT

public:
    explicit Network(QWidget *parent = nullptr);
    ~Network();
    // function to set pointer to main game
    void setMazePtr(maze* mazePtr){
        maze_dialog = mazePtr;
       // test slot
       connect(maze_dialog,&maze::endGameSignal,this,&Network::endGameSlot);
      }
    void setScorePtr(Score* scorePtr){
        score_dialog = scorePtr;
      }

private:
    Ui::Network *ui;
    // udp Dialoging variables
    QUdpSocket* udpSocket;
    QHostAddress HOST_IP;
    quint16 HOST_PORT = 0;

    QHostAddress P1_IP;
    quint16 P1_PORT = 0;
    QHostAddress P2_IP;
    quint16 P2_PORT = 0;
    QHostAddress P3_IP;
    quint16 P3_PORT = 0;
    QHostAddress P4_IP;
    quint16 P4_PORT = 0;

    char NUM_PLAYERS = '0';
    char NUM_PLAYERS_CHAR[4] = {'1','2','3','4'};
    char test[1];
    char PLAYER_CHAR = '1';
    bool isHost = false;
    bool isClient = false;

    // timer for when to send message
    QTimer* messageTimer;
    gameState state;

    // pointers to other dialogs
    maze* maze_dialog;           // main game dialog
    Score* score_dialog;

private slots:
    // udp networking slots
    void join_game();
    void host_game();
    void readDatagrams();
    void processIncomingPlayer();
    void startGame();
    void awaitStartGame();
    void messageTimerTimeout();
    void endGameSlot();

};

#endif // NETWORK_H

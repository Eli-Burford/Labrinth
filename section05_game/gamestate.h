#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <QNetworkInterface>

class gameState
{
public:
    gameState();
    QByteArray toByteArray();
    float getX(int player);
    float getY(int player);
    bool setP(int player, float x_new, float y_new);
    bool setPfromByteArray(QByteArray incomingMessage);
    // key
    char key[2];     // first character is key
    // players x and y
    float x[4];
    float y[4];
};

#endif // GAMESTATE_H

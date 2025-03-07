#include "gamestate.h"

gameState::gameState()
{
    key[0] = '0';
    key[1] = '0';
    for(int i=0; i<4; i++){
        x[i] = 0;
        y[i] = 0;
    }
}

QByteArray gameState::toByteArray(){
    char stateString[34]; // 4 for each float and 2 for header

    // append key to start of message
    stateString[0] = key[0];
    stateString[1] = key[1];

    int stateStringIdx = 2; // where we are in string

    // loop and add float values x1 y1, x2, y2 in order
    for(int i=0; i < 4; i++){
        char* currentByte = (char*)(&x[i]); // for float to string
        for(int j = 0; j < 4; j++){
            stateString[stateStringIdx] = currentByte[j];
            stateStringIdx++;
        }
    }
    for(int i=0; i < 4; i++){
        char* currentByte = (char*)(&y[i]); // for float to string
        for(int j = 0; j < 4; j++){
            stateString[stateStringIdx] = currentByte[j];
            stateStringIdx++;
        }
    }


    return QByteArray(stateString,34);
}

bool gameState::setP(int player, float x_new, float y_new){
    // player values 1 to 4
    if(player >=1 && player <=4){
        x[player-1] = x_new;
        y[player-1] = y_new;
        return true;
    }
    // invalid player
    else return false;
}

bool gameState::setPfromByteArray(QByteArray incomingMessage){
    // length - null character is 34
    if(incomingMessage.length() == 34){
        int incomingMessageIdx = 2; // where we are in string

        // loop and add float values x1 y1, x2, y2 in order
        for(int i=0; i < 4; i++){
            char* currentByte = (char*)(&x[i]); // for float to string
            for(int j = 0; j < 4; j++){
                currentByte[j] = incomingMessage[incomingMessageIdx];
                incomingMessageIdx++;
            }
        }
        for(int i=0; i < 4; i++){
            char* currentByte = (char*)(&y[i]); // for float to string
            for(int j = 0; j < 4; j++){
                currentByte[j] = incomingMessage[incomingMessageIdx];
                incomingMessageIdx++;
            }
        }
        return true;
    }
    else return false;

}

float gameState::getX(int player){
    if(player <= 4 && player >= 1){
        return x[player-1];
    }
    else {
        return 0;
    }
}

float gameState::getY(int player){
    if(player <= 4 && player >= 1){
        return y[player-1];
    }
    else {
        return 0;
    }
}

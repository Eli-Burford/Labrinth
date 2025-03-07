
#include <QApplication>
#include "score.h"
#include "ui_score.h"
#include "network.h"
#include "maze.h"
#include "gameover.h"

#include "ui_score.h"
#include "ui_network.h"
#include "ui_maze.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // instance of each inherited dialog
    Score score_dialog;         // final display after game over with high score table
    maze maze_dialog;           // main game dialog
    Network network_dialog;     // title screen and networking configuration
    //Gameover gameover_dialog;

    // passing pointers for inter-dialog communication
    network_dialog.setMazePtr(&maze_dialog);


    // displaying
    network_dialog.show();
    //score_dialog.show();

    // passing pointers for inter-dialog communication
    network_dialog.setMazePtr(&maze_dialog);
    network_dialog.setScorePtr(&score_dialog);
    //maze_dialog.show();
    //gameover_dialog.show();

    return a.exec();
}

#include "maze.h"
#include "ui_maze.h"

#include "stdlib.h"

maze::maze(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::maze)
{
    ui->setupUi(this);

    // Allocate and configure scene
    scene = new QGraphicsScene(-SCENE_WIDTH/2, -SCENE_HEIGHT/2,
                               SCENE_WIDTH, SCENE_HEIGHT);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setBackgroundBrush(Qt::black);

    // Make scene object the data source for the view object
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    // Make scene bounds visible
    drawPerimeterLines();


//    // Create a player object and add it to the scene object
//    spawnPlayer();

    // Create an obstacle object and add it to the scene object
    srand(time(nullptr));
    int MazeGen = rand() % 3;

    switch(MazeGen){
    case 0:
        spawnMaze1();
        break;
    case 1:
        spawnMaze2();
        break;
    case 2:
        spawnMaze3();
    }

    // Spawn pucks -- derived from QGraphicsObject
    PowerupGen = rand() % 5;

    spawnPucks(3);

    spawnPlayer(0, 380);

    spawnSpeed = new QTimer;
    spawnSpeed->setInterval(10000);
    connect(spawnSpeed, &QTimer::timeout, this, &maze::spawnSpeedPowerUp);
    spawnSpeed->start();



    // Add score header and display text items
    drawScoreDisplay();


    // Configure timer object to drive animation
    QTimer* timer = new QTimer;
    timer->setInterval(24);
    connect(timer, &QTimer::timeout, scene, &QGraphicsScene::advance);
    timer->start();

    // networking signals/slots
    connect(ui->testButton,SIGNAL(clicked()),this,SLOT(testSlot()));
}

maze::~maze()
{


}

void maze::drawPerimeterLines()
{
    // Define perimeter of scene with four QGraphicsLineItem objects

    int w = SCENE_WIDTH;    // Define w,h shortcuts names
    int h = SCENE_HEIGHT;

    QGraphicsLineItem* topline = scene->addLine(-w/2, -h/2, w/2, -h/2);
    topline->setPen(QPen(Qt::white));

    QGraphicsLineItem* bottomline = scene->addLine(-w/2, h/2, w/2, h/2);
    bottomline->setPen(QPen(Qt::white));

    QGraphicsLineItem* leftline = scene->addLine(-w/2, -h/2, -w/2, h/2);
    leftline->setPen(QPen(Qt::white));

    QGraphicsLineItem* rightline = scene->addLine(w/2, -h/2, w/2, h/2);
    rightline->setPen(QPen(Qt::white));
}

void maze::spawnMaze1()
{
    int vertmove = 0;   // Offset Variable
    int hormove = 0;    // Offset Variable

    for(int i = 0; i < 10; i++)
    {
        // Top Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, -400 - (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        // Bottom Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, 400 + (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        hormove = hormove + 80;
        // Left Border
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos(-400 - (T_OBSTACLE_WIDTH/2), (-400+ T_OBSTACLE_HEIGHT/2) + vertmove);
        scene->addItem(obstacle);

        vertmove = vertmove + 80;
    }

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-80 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);


    // Right Border
        vertmove = 0;   // offset Variable
        hormove = 0;    // offset variable

        // Bottom Right Border
        for(int i = 0; i < 5; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }
        // Top Right Border
        vertmove = vertmove + 80;
        for(int i = 0; i < 4; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }

   // Top Path
        int offset = 80;
        int offset2 = 80;
        for(int i = 0; i < 8; i++)
        {
            // Top
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -320+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
           offset = offset + 80;
        }
        for(int i = 0; i < 8; i++)
        {
            // Bottom Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-320+W_OBSTACLE_WIDTH/2) + offset2, -240+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;
        }
        offset2 = 80;
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos((-400+T_OBSTACLE_WIDTH/2) + offset2, -320+ (T_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);



   // 2nd Path
        offset2 = 160;
        offset = 80;

            // Top Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;

            offset2 = 80;
            for(int i = 0;i < 6;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-320 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 5;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-240 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 8;i++)
            {
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((320 + W_OBSTACLE_WIDTH/2) - offset2, 320 + (W_OBSTACLE_HEIGHT/2) );
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }
            offset = 80;
            offset2 = 80;
            for(int i = 0; i < 7; i++)
            {
                // Bottom Border
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 240+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }


            offset = 80;
            offset2 = 80;

            // Horizontal Walls - Single pieces
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((80+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
            scene->addItem(obstacle);

            for(int i = 0; i < 3; i++)
            {
                // Horizontal Walls - Long pieces
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 80+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            // Vertical Walls - Single piece

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(-80 + (T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
            obstacle->setPos((160 + OBSTACLE_WIDTH/2),-160 + (OBSTACLE_HEIGHT/2) + 320);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((400 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) - 80);
            scene->addItem(obstacle);


            // Vertical Walls - Long pieces
            for(int i = 0;i < 2;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-160 + T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((80+ T_OBSTACLE_WIDTH/2), -80 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            for(int i = 0;i < 3;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((160 + T_OBSTACLE_WIDTH/2),-160 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((320 + T_OBSTACLE_WIDTH/2),-80 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }
}

void maze::spawnMaze2()
{
    int vertmove = 0;   // Offset Variable
    int hormove = 0;    // Offset Variable

    for(int i = 0; i < 10; i++)
    {
        // Top Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, -400 - (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        // Bottom Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, 400 + (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        hormove = hormove + 80;
        // Left Border
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos(-400 - (T_OBSTACLE_WIDTH/2), (-400+ T_OBSTACLE_HEIGHT/2) + vertmove);
        scene->addItem(obstacle);

        vertmove = vertmove + 80;
    }

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-80 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);


    // Right Border
        vertmove = 0;   // offset Variable
        hormove = 0;    // offset variable

        // Bottom Right Border
        for(int i = 0; i < 5; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }
        // Top Right Border
        vertmove = vertmove + 80;
        for(int i = 0; i < 4; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }

   // Top Path
        int offset = 80;
        int offset2 = 80;
        for(int i = 0; i < 8; i++)
        {
            // Top
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -320+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
           offset = offset + 80;
        }
        for(int i = 0; i < 9; i++)
        {
            // Bottom Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset2, -240+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;
        }
        offset2 = 80;
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos((-400+T_OBSTACLE_WIDTH/2) + offset2, -320+ (T_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);



   // 2nd Path
        offset2 = 160;
        offset = 80;

            // Top Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;

            offset2 = 80;
            for(int i = 0;i < 6;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-320 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 5;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-240 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 8;i++)
            {
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((320 + W_OBSTACLE_WIDTH/2) - offset2, 320 + (W_OBSTACLE_HEIGHT/2) );
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }
            offset = 80;
            offset2 = 80;
            for(int i = 0; i < 7; i++)
            {
                // Bottom Border
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 240+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }


            offset = 80;
            offset2 = 80;

            // Horizontal Walls - Single pieces
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((80+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
            scene->addItem(obstacle);

            for(int i = 0; i < 3; i++)
            {
                // Horizontal Walls - Long pieces
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 80+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            // Vertical Walls - Single piece

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((T_OBSTACLE_WIDTH/2), 80 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
            obstacle->setPos((160 + OBSTACLE_WIDTH/2),-160 + (OBSTACLE_HEIGHT/2) + 320);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), -160 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((400 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) - 80);
            scene->addItem(obstacle);

            // Vertical Walls - Long pieces
            for(int i = 0;i < 2;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-160 + T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((80+ T_OBSTACLE_WIDTH/2), -80 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            for(int i = 0;i < 3;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((160 + T_OBSTACLE_WIDTH/2),-160 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((320 + T_OBSTACLE_WIDTH/2),-160 +(T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }
}

void maze::spawnMaze3()
{
    int vertmove = 0;   // Offset Variable
    int hormove = 0;    // Offset Variable

    for(int i = 0; i < 10; i++)
    {
        // Top Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, -400 - (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        // Bottom Border
        obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
        obstacle->setPos((-400 +(W_OBSTACLE_WIDTH/2)) + hormove, 400 + (W_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);

        hormove = hormove + 80;
        // Left Border
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos(-400 - (T_OBSTACLE_WIDTH/2), (-400+ T_OBSTACLE_HEIGHT/2) + vertmove);
        scene->addItem(obstacle);

        vertmove = vertmove + 80;
    }

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-400 - OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(-400 - (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (400 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);

    obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
    obstacle->setPos(400 + (OBSTACLE_WIDTH/2), (-80 + OBSTACLE_HEIGHT/2));
    scene->addItem(obstacle);


    // Right Border
        vertmove = 0;   // offset Variable
        hormove = 0;    // offset variable

        // Bottom Right Border
        for(int i = 0; i < 5; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }
        // Top Right Border
        vertmove = vertmove + 80;
        for(int i = 0; i < 4; i++)
        {
            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(400 + (T_OBSTACLE_WIDTH/2), (400 - T_OBSTACLE_HEIGHT/2) - vertmove);
            scene->addItem(obstacle);
            vertmove = vertmove + 80;
        }

   // Top Path
        int offset = 80;
        int offset2 = 80;
        for(int i = 0; i < 8; i++)
        {
            // Top
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -320+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
           offset = offset + 80;
        }
        for(int i = 0; i < 8; i++)
        {
            // Bottom Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset2, -240+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;
        }
       offset2 = 80;
        obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
        obstacle->setPos((-400+T_OBSTACLE_WIDTH/2) + offset2, -320+ (T_OBSTACLE_HEIGHT/2));
        scene->addItem(obstacle);



   // 2nd Path
        offset2 = 160;
        offset = 80;

            // Top Border
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((-400+W_OBSTACLE_WIDTH/2) + offset, -160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);
            offset2 = offset2 + 80;

            offset2 = 80;
            for(int i = 0;i < 6;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-320 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 5;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-240 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }

            offset2 = 80;
            for(int i = 0;i < 8;i++)
            {
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((320 + W_OBSTACLE_WIDTH/2) - offset2, 320 + (W_OBSTACLE_HEIGHT/2) );
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }
            offset = 80;
            offset2 = 80;
            for(int i = 0; i < 7; i++)
            {
                // Bottom Border
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-320+W_OBSTACLE_WIDTH/2) + offset2, 240+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);
                offset2 = offset2 + 80;
            }


            offset = 80;
            offset2 = 80;

            // Horizontal Walls - Single pieces
            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((80+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -160);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
            obstacle->setPos((240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2));
            scene->addItem(obstacle);

            for(int i = 0; i < 3; i++)
            {
                // Horizontal Walls - Long pieces
                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 160+ (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, 80 + (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-240+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2));
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, W_OBSTACLE_WIDTH, W_OBSTACLE_HEIGHT);
                obstacle->setPos((-160+W_OBSTACLE_WIDTH/2) + offset2, (W_OBSTACLE_HEIGHT/2) -80);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            // Vertical Walls - Single piece

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(80 + (T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(320 - (T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos(-80 + (T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, OBSTACLE_WIDTH, OBSTACLE_HEIGHT);
            obstacle->setPos((160 + OBSTACLE_WIDTH/2),-160 + (OBSTACLE_HEIGHT/2) + 320);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), -80 + (T_OBSTACLE_HEIGHT/2) + offset2);
            scene->addItem(obstacle);

            obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
            obstacle->setPos((400 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) - 80);
            scene->addItem(obstacle);

            // Vertical Walls - Long pieces
            for(int i = 0;i < 2;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((-160 + T_OBSTACLE_WIDTH/2), -320 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), -240 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((80+ T_OBSTACLE_WIDTH/2), -80 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((240 + T_OBSTACLE_WIDTH/2), (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }

            offset = 80;
            offset2 = 80;
            for(int i = 0;i < 3;i++)
            {
                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((160 + T_OBSTACLE_WIDTH/2),-160 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                obstacle = new Obstacle(nullptr, T_OBSTACLE_WIDTH, T_OBSTACLE_HEIGHT);
                obstacle->setPos((320 - T_OBSTACLE_WIDTH/2),-80 + (T_OBSTACLE_HEIGHT/2) + offset2);
                scene->addItem(obstacle);

                offset2 = offset2 + 80;
            }
}

void maze::spawnPucks(int n)
{
    int PowerupGen = rand();


    for (unsigned int i = n; i > 0; i--)
    {
        puck = new Puck; // Create new puck in latest position in puck array

        // QUESTION: How do we ensure multiple pucks don't spawn in the same location?

        puck->setPos(locations[(++PowerupGen %= 6)]); // Set position of new puck object

        scene->addItem(puck);             // Once position determined, add item to scene


        // Below is a solution to avoid overlapping pucks, but it's very slow sometimes
        QList<QGraphicsItem*> list = puck->collidingItems();
        if (!list.isEmpty())
        {
            this->scene->removeItem(puck);  // remove puck from scene
            puck->deleteLater();
            spawnPucks(1);                  // Create another puck elsewhere
        }

    }

}

void maze::spawnPlayer(int x, int y)
{
    // Spawn custom Player object
    player1 = new Player;
    player1->setPos(x, y);
    player1->pScore = 0;
    scene->addItem(player1);
}

void maze::spawnGhostPlayers(int x, int y){
    qDebug() << playerNum;

//    int playerInt = playerNum - 48 - 1;                     // Get index for client player by converting from ASCII and subtracting 1 since indexes start at 0

//    qDebug() << playerInt;

//    for (int i = 0; i <= 3; i++){

//        if (playerInt == i){
//            players[i] = new Player;
//            players[i]->ghost = false;      // Set client player to not be a ghost
//        }
//        else players[i] = new ghostPlayer;
//        (players[i])->setPos(x + (i * 30), y);  // Set client player's position based on playerNum
//        scene->addItem(players[i]);

//    }



    // spawn local player as player1
    switch(playerNum){
    case '1':
        // Spawn custom Player object in center of scene
        player1->setPos(x, y);
        //player1->pScore = 0;
        break;
    case '2':
        // Spawn custom Player object in center of scene
        player1->setPos(x+30, y);
        //player1->pScore = 0;
        break;
    case '3':
        // Spawn custom Player object in center of scene
        player1->setPos(x+60, y);
        //player1->pScore = 0;
        break;
    case '4':
        // Spawn custom Player object in center of scene
        player1->setPos(x+90, y);
        //player1->pScore = 0;
        break;
    }



    if(playerNum != '1'){
        // spawn ghost player
        ghostplayer1 = new ghostPlayer;
        ghostplayer1->setPos(x,y);
        ghostplayer1->pScore = 0;
        scene->addItem(ghostplayer1);
    }
    if(playerNum != '2'){
        // spawn ghost player
        ghostplayer2 = new ghostPlayer;
        ghostplayer2->setPos(x+30,y);
        ghostplayer2->pScore = 0;
        scene->addItem(ghostplayer2);
    }
    if(playerNum != '3'){
        // spawn ghost player
        ghostplayer3 = new ghostPlayer;
        ghostplayer3->setPos(x+60,y);
        ghostplayer3->pScore = 0;
        scene->addItem(ghostplayer3);
    }
    if(playerNum != '4'){
        // spawn ghost player
        ghostplayer4 = new ghostPlayer;
        ghostplayer4->setPos(x+90,y);
        ghostplayer4->pScore = 0;
        scene->addItem(ghostplayer4);
    }
}

void maze::keyPressEvent(QKeyEvent *e)
{
    if (e)
    {
        switch (e->key())
        {
            case Qt::Key_A:
            case Qt::Key_J:
            case Qt::Key_Left:      player1->goLeft();
                                    break;

            case Qt::Key_D:
            case Qt::Key_L:
            case Qt::Key_Right:     player1->goRight();
                                    break;

            case Qt::Key_W:
            case Qt::Key_I:
            case Qt::Key_Up:        player1->goUp();
                                    break;

            case Qt::Key_S:
            case Qt::Key_K:
            case Qt::Key_Down:      player1->goDown();
                                    break;


            default:                player1->stop();
                                    break;
        }

        playerCollision(player1);

    }

    QDialog::keyPressEvent(e);
}

void maze::drawScoreDisplay()
{
    // Adds SCORE header and display in top right corner
    // outside scene perimeter

    // Show score header
    header = new QGraphicsTextItem("SCORE");
    header->setDefaultTextColor(Qt::yellow);
    header->setPos(SCENE_WIDTH/2 + 25, -SCENE_HEIGHT/2);
    scene->addItem(header);

    // Show score display
    display = new QGraphicsTextItem(QString::number(0));
    display->setDefaultTextColor(Qt::yellow);
    display->setPos(SCENE_WIDTH/2 + 25, -SCENE_HEIGHT/2 + 25);
    display->setPlainText(QString::number(player1->pScore));
    scene->addItem(display);
}

void maze::playerCollision(Player* collider)    // Check for player collisions during movement and respond accordingly
{
    QList<QGraphicsItem*> list = collider->collidingItems();    // Create list of items colliding with player
    if (!list.isEmpty())
    {
        Puck * testPuck = dynamic_cast<Puck *>(list[0]);        // Create test pointer and cast collided item to a puck

        if (testPuck){      // If Player collides with a pickup of some sort

            SpeedPowerUp * testSPU = dynamic_cast<SpeedPowerUp *>(list[0]);
            victoryPickup * testVic = dynamic_cast<victoryPickup *>(list[0]);
            if (testSPU){   // Should execute only when Powerup hit
                qDebug() << "Powerup Collided with Player";
                collider->setSpeed(2);                                      // Increase player speed
                collider->speedTime = 10;                                   // Set active time for SPU
                spawnSpeed->start();

                collider->displaySpeed = new QTimer;                        // Create timer to display speed seconds remaining
                collider->displaySpeed->setInterval(1000);                  // Interval of 1 second
                connect(collider->displaySpeed, &QTimer::timeout, this, &maze::speedCountDown); // Every second, execute countdown function
                collider->displaySpeed->start();                                                // Start timer
                speedy = collider;
            }

            else if (testVic) testSlot(); // This line ends the game once victory powerup is collected

            else{           // Should execute only when puck hit
                qDebug() << "Puck Collided with Player";
                if (++(collider->pScore) == 3){    // Increment Score, check if player score is at 20 points yet
                    spawnVictoryPickup();
                }
                display->setPlainText(QString::number(collider->pScore));   // Display score
                spawnPucks(1);                                              // Spawn new puck elsewhere
            }

            this->scene->removeItem(testPuck);  // Remove pickup from scene
            testPuck->deleteLater();
        }
    }
}

void maze::spawnVictoryPickup(){

    int PowerupGen = rand();

    victoryPickup* victory = new victoryPickup;

    victory->setPos(locations[++PowerupGen %= 6]);
    scene->addItem(victory);

     QList<QGraphicsItem*> List = victory->collidingItems();
     if (!List.isEmpty()){

         this->scene->removeItem(victory);  // remove puck from scene
         victory->deleteLater();
         spawnVictoryPickup();              // Create another puck elsewhere
     }

}

void maze::spawnSpeedPowerUp()
{

    int PowerupGen = rand();

    speedpowerup = new SpeedPowerUp; // Create new pickup

    speedpowerup->setPos(locations[++PowerupGen%=6]);   // Increment PowerupGen so that spawning will function correctly, mod 6 to stay within spawnpoint array

    scene->addItem(speedpowerup);                       // Once position determined, add item to scene

    QList<QGraphicsItem*> List = speedpowerup->collidingItems();
    if (!List.isEmpty())
    {
        SpeedPowerUp * testPower = dynamic_cast<SpeedPowerUp *>(List[0]);   // Test if collider is a SPU
        Puck * testPuck = dynamic_cast<Puck *>(List[0]);
        if (testPuck){                              // Test if collider is puck

            this->scene->removeItem(speedpowerup);  // remove SPU from scene
            testPower->deleteLater();

            if (!testPower) spawnSpeedPowerUp(); // If collided item was NOT an SPU (i.e. was a Puck), spawn SPU elsewhere
        }
    }
    spawnSpeed->stop(); // This will stop the timer so new SPUs will not be created
}

void maze::speedCountDown()
{
    speedy->speedTime--;
    qDebug() << speedy->speedTime;
    if(speedy->speedTime == 0)
    {
        speedy->setSpeed(0.5);
        speedy->displaySpeed->stop();
        return;
    }
}


void maze::test(){
    maze::spawnGhostPlayers(0,380);
    ui->label->setText(QString(playerNum));
}

void maze::testSlot(){
    qDebug() << "slot entered";
    emit(endGameSignal(playerNum));
}

void maze::setP(int player, float x, float y){

    int test = (int)playerNum;

    switch(player){
    case 1:
        if(playerNum != '1'){
            ghostplayer1->setPos(x,y);
        }
        break;
    case 2:
        if(playerNum != '2'){
            ghostplayer2->setPos(x,y);
        }
        break;
    case 3:
        if(playerNum != '3'){
            ghostplayer3->setPos(x,y);
        }
        break;
    case 4:
        if(playerNum != '4'){
            ghostplayer4->setPos(x,y);
        }
        break;
    }
}

// Idea for optimizing players - flag in each player object that specifies whether it's a ghost or not. Use flag in checks

float maze::px(char temp){


}

float maze::py(){


}


float maze::p1x(){
    if(playerNum != '1'){
        return ghostplayer1->pos().rx();
    }
    else{
        return player1->pos().rx();
    }
}
float maze::p1y(){
    if(playerNum != '1'){
        return ghostplayer1->pos().ry();
    }
    else{
        return player1->pos().ry();
    }
}
float maze::p2x(){
    if(playerNum != '2'){
        return ghostplayer2->pos().rx();
    }
    else{
        return player1->pos().rx();
    }
}
float maze::p2y(){
    if(playerNum != '2'){
        return ghostplayer2->pos().ry();
    }
    else{
        return player1->pos().ry();
    }
}
float maze::p3x(){
    if(playerNum != '3'){
        return ghostplayer3->pos().rx();
    }
    else{
        return player1->pos().rx();
    }
}
float maze::p3y(){
    if(playerNum != '3'){
        return ghostplayer3->pos().ry();
    }
    else{
        return player1->pos().ry();
    }
}
float maze::p4x(){
    if(playerNum != '4'){
        return ghostplayer4->pos().rx();
    }
    else{
        return player1->pos().rx();
    }
}
float maze::p4y(){
    if(playerNum != '4'){
        return ghostplayer4->pos().ry();
    }
    else{
        return player1->pos().ry();
    }
}

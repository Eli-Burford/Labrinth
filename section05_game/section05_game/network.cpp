
#include "network.h"
#include "ui_network.h"


Network::Network(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Network)
{
    ui->setupUi(this);

    // connect buttons on dialog to self-defined slots
    connect(ui->join_button,SIGNAL(clicked()),this,SLOT(join_game()));

    connect(ui->host_button,SIGNAL(clicked()),this,SLOT(host_game()));

    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startGame()));

}

Network::~Network()
{
    delete ui;
}

void Network::join_game(){
    // clear text box
    ui->join_browser->clear();
    // setep udp socket
    udpSocket = new QUdpSocket(this);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Network::processIncomingPlayer);
    udpSocket->setProxy(QNetworkProxy::NoProxy);
    HOST_IP.setAddress(ui->joinIPEdit->text());         // connect to host with port and ip in text box
    if(HOST_IP.isNull() || !(HOST_IP.protocol() == QAbstractSocket::IPv4Protocol)){
        ui->join_browser->append("ERROR: Please enter a valid Host IP.\n");
    }
    HOST_PORT = ui->joinPortEdit->text().toUShort();    // connect at port in line edit
    if(!HOST_PORT || HOST_PORT > 9999){
        ui->join_browser->append("ERROR: Please enter a valid port number.\n");
    }
    // send a join request
    char test[] = "jr";
    udpSocket->writeDatagram(QNetworkDatagram(QByteArray(test),HOST_IP,HOST_PORT));
}

void Network::host_game(){
    // clear browser
    ui->host_browser->clear();
    // setup socket
    udpSocket = new QUdpSocket(this);
    udpSocket->setProxy(QNetworkProxy::NoProxy);
    // find ipv4 address
    HOST_PORT = (ui->hostPortEdit->text()).toUShort();
    // make sure host_port was entered
    if(!HOST_PORT || HOST_PORT > 9999){
        ui->host_browser->append("ERROR: Please enter a valid port number.\n");
        return;
    }
    // find host ip
    const QHostAddress &local_ip = QHostAddress(QHostAddress::LocalHost);
    bool successfulBind = false;
    for (const QHostAddress &ip: QNetworkInterface::allAddresses()) {
        if (ip.protocol() == QAbstractSocket::IPv4Protocol && ip != local_ip){
            HOST_IP = ip;
            successfulBind = udpSocket->bind(HOST_IP,HOST_PORT);
            if(successfulBind) break;
        }
    }
    // iff successful become host
    if(successfulBind){
        // append message saying joined game
        ui->host_browser->append("Successfully opened on port:");
        ui->host_browser->append(QString::number(HOST_PORT));
        ui->host_browser->append("and ip:");
        ui->host_browser->append(HOST_IP.toString());
        // connect incoming message signal to slot
        connect(udpSocket, &QUdpSocket::readyRead, this, &Network::readDatagrams);
        // player tracking
        isHost = true;
        NUM_PLAYERS++;
        // disable join and host button
        ui->join_button->setDisabled(true);
        ui->host_button->setDisabled(true);
    }
    else{
        ui->host_browser->append("ERROR: Please try another port or check your internet connection.");
    }
}

void Network::readDatagrams(){
    // to grab datagram data
    QByteArray      datagram;
    QHostAddress*   incomingAddress = new QHostAddress;
    quint16*        incomingPort = new quint16;
    // resize to size of incominng data
    datagram.resize(int(udpSocket->pendingDatagramSize()));
    // two arguments where to put data, and how muchb data
    udpSocket->readDatagram(datagram.data(), datagram.size(),incomingAddress, incomingPort);
    if(isHost){
        // handle join request
        if(datagram.data()[0] == 'j' && datagram.data()[1] == 'r'){
            qDebug() << "join request";
            if(NUM_PLAYERS < '4'){
                NUM_PLAYERS++;
                udpSocket->writeDatagram(QNetworkDatagram(QByteArray(1,NUM_PLAYERS),*incomingAddress,*incomingPort));
            }
            // append which player has joined
            ui->join_browser->append("Player ");
            ui->join_browser->append(QByteArray(1,NUM_PLAYERS));
            ui->join_browser->append("has joined\n");
            // assign client ports and addresses
            switch(NUM_PLAYERS){
            case '2':
                P2_PORT = *incomingPort;
                P2_IP = *incomingAddress;
                break;
            case '3':
                P3_PORT = *incomingPort;
                P3_IP = *incomingAddress;
                break;
            case '4':
                P4_PORT = *incomingPort;
                P4_IP = *incomingAddress;
                break;
            }
        }
    }
    // player gamestate during game
    if(datagram.data()[0] == 'p' && datagram.length() == 34){
        qDebug() << "valid message";
        gameState tempstate;
        bool validMessage = tempstate.setPfromByteArray(datagram);
        if(validMessage){
//            state.x[(PLAYER_CHAR - 48 - 1)] = tempstate.x[(PLAYER_CHAR - 48 - 1)];
//            state.y[(PLAYER_CHAR - 48 - 1)] = tempstate.y[(PLAYER_CHAR - 48 - 1)];
//            maze_dialog->setP((PLAYER_CHAR - 48), state.x[PLAYER_CHAR - 49], state.y[PLAYER_CHAR - 49]);// update host position
            switch(datagram.data()[1]){
                case '1': // message from host
                    state.x[0] = tempstate.x[0]; // update host position
                    state.y[0] = tempstate.y[0];
                    maze_dialog->setP(1,state.x[0],state.y[0]);// update host position
                    if(PLAYER_CHAR != '2'){ // update ghost player 2
                        state.x[1] = tempstate.x[1];
                        state.y[1] = tempstate.y[1];
                    } else { // else send back own position
                        state.x[1] = maze_dialog->p2x();
                        state.y[1] = maze_dialog->p2y();
                        state.key[1] = '2';
                        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P1_IP,P1_PORT));
                    }
                    if(PLAYER_CHAR != '3'){ // update ghost player 3
                        state.x[2] = tempstate.x[2];
                        state.y[2] = tempstate.y[2];
                    } else {// else send back own position
                        state.x[2] = maze_dialog->p3x();
                        state.y[2] = maze_dialog->p3y();
                        state.key[1] = '3';
                        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P1_IP,P1_PORT));
                    }
                    if(PLAYER_CHAR != '4'){ // update ghost player 4
                        state.x[3] = tempstate.x[3];
                        state.y[3] = tempstate.y[3];
                    } else { // else send back own position
                        state.x[3] = maze_dialog->p4x();
                        state.y[3] = maze_dialog->p4y();
                        state.key[1] = '4';
                        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P1_IP,P1_PORT));
                    }
                    break;
                case '2': // message from client player 2
                    state.x[1] = tempstate.x[1];    // grab position of player from message
                    state.y[1] = tempstate.y[1];
                    maze_dialog->setP(2,state.x[1],state.y[1]);// update position in game
                    break;
                case '3':// message from client player 3
                    state.x[2] = tempstate.x[2];   // grab position of player from message
                    state.y[2] = tempstate.y[2];
                    maze_dialog->setP(3,state.x[2],state.y[2]);// update position in game
                    break;
                case '4':// message from client player 4
                    state.x[3] = tempstate.x[3];   // grab position of player from message
                    state.y[3] = tempstate.y[3];
                    maze_dialog->setP(4,state.x[3],state.y[3]); // update position in game
                    break;
            }

        }
    }
    else if(datagram.data()[0] == 'e' && datagram.data()[1] == 'g'){
        qDebug() << "endgame executed";
    }
    // incoming user request
    QString incomingMessage = datagram.data();
    std::string incomingString = incomingMessage.toStdString();
    if(incomingString[0] == '0' && incomingString[1] == '0'){
        gameState stateTest;
        stateTest.setPfromByteArray(datagram);
    }
}

void Network::processIncomingPlayer(){
    qDebug() << "player connected\n";
    // to grab datagram data
    QByteArray      datagram;
    QHostAddress*   incomingAddress = new QHostAddress;
    quint16*        incomingPort = new quint16;
    // resize to size of incominng data
    datagram.resize(int(udpSocket->pendingDatagramSize()));
    // two arguments where to put data, and how muchb data
    udpSocket->readDatagram(datagram.data(), datagram.size(),incomingAddress, incomingPort);
    // set host ip and port
    P1_PORT = *incomingPort;
    P1_IP = *incomingAddress;
    // received return message
    isClient = true;
    // change data read mode
    disconnect(udpSocket, &QUdpSocket::readyRead, this, &Network::processIncomingPlayer);
    connect(udpSocket, &QUdpSocket::readyRead, this, &Network::awaitStartGame);
    // append browser
    ui->join_browser->append("Successfully joined as player:");
    ui->join_browser->append(datagram.data());
    maze_dialog->playerNum = datagram.data()[0];
    PLAYER_CHAR = datagram.data()[0];
    ui->join_browser->append("Waiting for Host to start game. . .");
    // disable buttons
    ui->host_button->setDisabled(true);connect(maze_dialog,&maze::endGameSignal,this,&Network::endGameSlot);
    ui->join_button->setDisabled(true);
    ui->startButton->setDisabled(true);
}

void Network::awaitStartGame(){
    // to grab datagram data
    QByteArray      datagram;udpSocket->writeDatagram(QNetworkDatagram(QByteArray(startGameMessage),P2_IP,P2_PORT));
    QHostAddress*   incomingAddress = new QHostAddress;
    quint16*        incomingPort = new quint16;
    // resize to size of incominng data
    datagram.resize(int(udpSocket->pendingDatagramSize()));
    // two arguments where to put data, and how muchb data
    udpSocket->readDatagram(datagram.data(), datagram.size(),incomingAddress, incomingPort);
    if(datagram.data()[0] == 's' && datagram.data()[1] == 'g'){
        qDebug() << "start game reached";
        // change data read mode
        disconnect(udpSocket, &QUdpSocket::readyRead, this, &Network::awaitStartGame);
        connect(udpSocket, &QUdpSocket::readyRead, this, &Network::readDatagrams);
        // call startGame function
        Network::startGame();
    }

}

void Network::startGame(){
    if(isHost){
        // send out start game messages
        switch(NUM_PLAYERS){
            case '4':
                udpSocket->writeDatagram(QNetworkDatagram(QByteArray(startGameMessage),P4_IP,P4_PORT));
            case '3':
                udpSocket->writeDatagram(QNetworkDatagram(QByteArray(startGameMessage),P3_IP,P3_PORT));
            case '2':
                udpSocket->writeDatagram(QNetworkDatagram(QByteArray(startGameMessage),P2_IP,P2_PORT));
        }
        // start sending message timer
        messageTimer = new QTimer;
        messageTimer->setInterval(24);
        connect(messageTimer, &QTimer::timeout, this, &Network::messageTimerTimeout);
        messageTimer->start();
        // gamestate set key
        state.key[0] = 'p';
        state.key[1] = '1';
    }
    else{
        state.key[0] = 'p';
        state.key[1] = PLAYER_CHAR;
    }
    maze_dialog->test();
    if(isHost){
        // get state from maze dialog
        switch(NUM_PLAYERS){
        case '4':
            state.setP(4,maze_dialog->p4x(),maze_dialog->p4y());
        case '3':
            state.setP(3,maze_dialog->p3x(),maze_dialog->p3y());
        case '2':
            state.setP(2,maze_dialog->p2x(),maze_dialog->p2y());
        default:
            state.setP(1,maze_dialog->p1x(),maze_dialog->p1y());
        }
    }
    maze_dialog->show();
    this->hide();
    //game state key
}

void Network::endGameSlot(){
    disconnect(maze_dialog,&maze::endGameSignal,this,&Network::endGameSlot);
    //this->show();
    score_dialog->show();
    maze_dialog->hide();
    qDebug() << "signal received 2";
}

void Network::messageTimerTimeout(){
    state.setP(1,maze_dialog->p1x(),maze_dialog->p1y());
    // send game state to all players
    switch(NUM_PLAYERS){
    case '4':
        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P4_IP,P4_PORT));
    case '3':
        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P3_IP,P3_PORT));
    case '2':
        udpSocket->writeDatagram(QNetworkDatagram(QByteArray(state.toByteArray()),P2_IP,P2_PORT));
    }
    qDebug() << "timer";
}

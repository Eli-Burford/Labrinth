#include "gameover.h"
#include "ui_gameover.h"

Gameover::Gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gameover)
{
    ui->setupUi(this);

    connect(ui->pushButton,&QPushButton::clicked,this,&Gameover::exitDialog);
}

Gameover::~Gameover()
{
    delete ui;
}

void Gameover::exitDialog(){
    this->hide();
}

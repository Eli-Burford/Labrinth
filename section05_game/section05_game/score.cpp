#include "score.h"
#include "ui_score.h"
#include "network.h"
#include "ui_maze.h"
#include "player.h"


Score::Score(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Score)
{
    ui->setupUi(this);
    connect (ui->addButton, SIGNAL(clicked(bool)), this, SLOT(postQuery()));
   connect(ui->ShowButton, SIGNAL(clicked()), this, SLOT(showPlayerData()));
    connect(ui->QButton, SIGNAL(clicked()), this, SLOT(Quit()));

    // Connect clicking of showButton to showPlayerData()
    db = QSqlDatabase::addDatabase("QSQLITE");                                  // Create SQL database using SQLITE
    db.setDatabaseName("Score.db");                                             // assign name to database
    if (!db.open())                                                             // If failed to open database, exit code with error message
    {
        qDebug() << "Error Opening Database" << db.lastError();
        exit(1);
    }

    QSqlQuery qprep;                                                            // Create query preparation variable

    if (!qprep.exec("CREATE TABLE IF NOT EXISTS Score(PlayerName TEXT, Rank INT, Score INT)"))  // If table not created, exit with error message
    {
        qDebug() << "Error creating table " << db.lastError();
        return;
    }

    QSqlQuery q;                                                                // Create another query variable
    q.exec("SELECT * from Score");                                              // Select all values from Score table we created with qprep

    QSqlQueryModel *model = new QSqlQueryModel;                                 // Dynamically allocate memory for new queryModel
    model->setQuery(q);                                                         // Set query Model to track our query q

    ui->tableView->setModel(model);                                             // Display our model in the UI's tableView



}


void Score::showPlayerData()
{
    if (db.isValid() && db.isOpen())
    {
        QSqlQuery q;                                                            // Create query variable

       // q.exec("SELECT PlayerName, Score FROM Score");
       // q.exec(" SELECT PlayerName, MAX(Score) FROM Score ");                   // Get Playernme and Maximum score from Score database


        q.exec("SELECT PlayerName, Score FROM Score ORDER BY Score DESC");


        QSqlQueryModel *model = new QSqlQueryModel;                             // Create new model
        model->setQuery(q);                                                     // Set model to track our created query

        ui->tableView->setModel(model);                                         // Display model in UI's tableView
    }
    else
    {
        qDebug() << "Database connection is not valid or open.";                // If database invalid or unopened, throw an error message
    }

}

void Score::updatePlayerScore(const QString &PlayerName, int newScore) {

    QSqlQuery query;                                                            // Create query variable
    query.prepare("UPDATE Score SET Score = :score WHERE PlayerName = :name");  // Prepare a command with placeholders ":score" and ":name"
                                                                                // Prepped command will update score database by updating a score corresponding to the given name

    query.bindValue(":score", newScore);                                        // Bind ":score" to newScore int value that was passed into function
    query.bindValue(":name", PlayerName);                                       // Bind ":name" to playerName QString value that was passed into function

    if (query.exec()) {                                                         // Execute prepped command and check for proper completion
        qDebug() << "Score updated successfully for player: " << PlayerName;    // If properly completed, output statement stating such, along with name of score updated
        showPlayerData(); // Refresh the data
    }
    else {
        qDebug() << "Error updating score: " << query.lastError();              // If command doesn't properly execute, output error statement
    }
}



void Score::Quit()
{
    this ->close();
}


void Score::setPlayerScore(int score){
    player_score = score;
}

void Score::postQuery()
{
    QString PlayerName = ui->lineEdit->text();

    if (PlayerName.isEmpty()) {
        qDebug() << "Player name is empty. Please enter a valid name.";
        return;
    }

    // Insert the player name into the "Score" table with an initial score of 0
    QSqlQuery query;
    query.prepare("INSERT INTO Score (PlayerName, Score) VALUES (:name, 10)");
    query.bindValue(":name", PlayerName);

    if (query.exec()) {
        qDebug() << "Player added successfully: " << PlayerName;

        // Clear the line edit after adding the player
        ui->lineEdit->clear();

        // Refresh the data in the table view after adding the player
        //showPlayerData();
    } else {
        qDebug() << "Error adding player: " << query.lastError();
    }
}




Score::~Score()
{
    delete ui;
    db.close();                                                                 // Close database after Score UI closed
}

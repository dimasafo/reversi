#include "guibase.h"

#include "idcell.h"

#include <QtGui>
#include <QIntValidator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <string>
#include <sstream>

//НУЖНО ИСПОЛЬЗОВАТЬ UTF8 WITHOUT BOM !!!!!

template<typename T>
std::string toString(T t)
{
    std::stringstream ss;
    ss << t;
    return ss.str();
}

GuiBase::GuiBase( QWidget* parent )
    : QDialog(parent)
    , chessBoard_(nullptr)
    , curGame_(nullptr)
    , computerGoButton_(nullptr)
    , giveUpButton_(nullptr)
{

    setWindowTitle(tr("Реверси"));
    resize(500, 500);
    this -> setFixedSize(500, 500);

    QIntValidator* inputRange = new QIntValidator(this);
    inputRange->setRange(4, 40);

    rowsField_ = new QLineEdit();
    rowsField_->setValidator(inputRange);
    rowsField_->setText("8");

    QLabel* rowsFieldLabel = new QLabel("Строк:");

    columnsField_ = new QLineEdit();
    columnsField_->setValidator(inputRange);
    columnsField_->setText("8");

    QLabel* columnsFieldLabel = new QLabel("Столбцов:");

    QPushButton* startGameButton = new QPushButton(tr("Начать игру"));

    connect(startGameButton, SIGNAL(clicked()),
        this, SLOT(startGame()));

    giveUpButton_ = new QPushButton(tr("Досрочно закончить"));

    connect(giveUpButton_, SIGNAL(clicked()),
        this, SLOT(giveUp()));

    giveUpButton_->setEnabled(false);

    QPushButton* cancelButton = new QPushButton(tr("Close"));
    QPushButton* okButton = new QPushButton(tr("OK"));

    computerGoButton_ = new QPushButton(tr("Computer GO!"));

    computerGoButton_->setEnabled(false);

    connect(computerGoButton_, SIGNAL(clicked()),
        this, SLOT(computerGo()));

    QLabel* gameStatusLabel = new QLabel();

    connect(this, SIGNAL(setGameStatusText(const QString &)),
        gameStatusLabel, SLOT(setText(const QString &)));

    connect(cancelButton, SIGNAL(clicked()),
        this, SLOT(close()));

    connect(okButton, SIGNAL(clicked()),
        this, SLOT(ok()));

    QHBoxLayout* addIntervalLayout = new QHBoxLayout;
    addIntervalLayout -> addStretch(1);
    addIntervalLayout -> addWidget(rowsFieldLabel);
    addIntervalLayout -> addWidget(rowsField_);
    addIntervalLayout -> addWidget(columnsFieldLabel);
    addIntervalLayout -> addWidget(columnsField_);
    addIntervalLayout -> addWidget(startGameButton);
    addIntervalLayout -> addWidget(giveUpButton_);

    QHBoxLayout* computerGoLayout = new QHBoxLayout;
    computerGoLayout->addWidget(gameStatusLabel);
    computerGoLayout->addStretch(1);
    computerGoLayout->addWidget(computerGoButton_);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(okButton);
    buttonsLayout->addWidget(cancelButton);

    chessBoard_ = new MyChessBoard(250, 250);

    connect(chessBoard_, SIGNAL(signalCellClicked(int, int)), this, SLOT(cellClicked(int, int)));
    chessBoard_->update();

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setMargin(5);
    mainLayout->setSpacing(5);
    mainLayout->addLayout( addIntervalLayout );
    mainLayout->addWidget( chessBoard_ );
    mainLayout->addLayout( computerGoLayout );
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);

    //QIcon mainIcon(":Icons/Resources/advancedOpt.png");
    //setWindowIcon(mainIcon);

    emit setGameStatusText("no game!");

    setWindowFlags( windowFlags() & (~Qt::WindowContextHelpButtonHint) );
}

void GuiBase::ok()
{
    done(1);
    return;
}

void GuiBase::close()
{
    done(0);
    return;
}

void GuiBase::addValue()
{
}



///////////////////////////////////////////////////////////
//
///////////////////////////////////////////////////////////

void GuiBase::startGame()
{
    if(curGame_)
    {
        if(!curGame_->isGameFinished())
        {
            QMessageBox msgBox;
            msgBox.setText("Партия уже идет.");
            msgBox.setInformativeText("Вы хотите удалить текущую партию?");
            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
            msgBox.setDefaultButton(QMessageBox::Yes);
            int ret = msgBox.exec();

            if(ret == QMessageBox::No)
                return;
        }

        delete curGame_;
    }

    int rows = rowsField_->text().toInt();
    int cols = columnsField_->text().toInt();

    curGame_ = new Game(rows, cols);

    chessBoard_->createCells(curGame_->boardData()->getRows(), curGame_->boardData()->getColumns());

    syncDataWithBoard(curGame_->boardData());

    computerGoButton_->setEnabled(curGame_->currentMustGoComp());

    giveUpButton_->setEnabled(true);

    emit setGameStatusText("");

    update();
}

void GuiBase::giveUp()
{
    if(curGame_ && !curGame_->isGameFinished())
    {
        QMessageBox msgBox;
        msgBox.setText("досрочно закончить.");
        msgBox.setInformativeText("Вы хотите досрочно закончить текущую партию?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        if(ret == QMessageBox::No)
            return;

        curGame_->finishGame();
        onFinishGame();
    }
}

void GuiBase::onFinishGame()
{
    std::string res;

    computerGoButton_->setEnabled(false);
    giveUpButton_->setEnabled(false);

    if(curGame_)
    {
        res += "Игра окончена.\n";

        const std::vector<PlayerId*>* const pls = curGame_->players();
        const BoardData* const data = curGame_->boardData();

        int allCells = data->allCells();

        res += "Всего ячеек: " + toString(allCells) + " \n";

        int playerNum = 0;
        for(auto it = pls->cbegin(); it != pls->cend(); ++it)
        {
            playerNum++;
            int plCells = data->playerCells(*it);

            res += "Игрок №" + toString(playerNum) + ": "+ toString(plCells) +" фишек\n";
        }
    }

    emit setGameStatusText(QString(res.c_str()));

    update();
}

void GuiBase::computerGo()
{
    if(!curGame_)
        return;

    if(!curGame_->currentMustGoComp())
        return; //todo warning (current must not go comp)

    if(curGame_->isGameFinished())
        return onFinishGame();

    const PlayerId* const player = curGame_->getCurrentPlayer();

    curGame_->processComputerGo(player);

    syncDataWithBoard(curGame_->boardData());

    computerGoButton_->setEnabled(curGame_->currentMustGoComp());

    if(curGame_->isGameFinished())
        return onFinishGame();

    update();
}

void GuiBase::syncDataWithBoard(const BoardData* const boardData)
{

    for(int row = 0; row < boardData->getRows(); row++)
    {
        for(int column = 0; column  < boardData->getColumns(); column ++)
        {
            const PlayerId* const player = boardData->getPlayer(IdCell(row, column));

            chessBoard_->setState(boardData->getRows() - row - 1, column, player);
        }
    }

}

void GuiBase::cellClicked(int row, int column)
{
    if(!curGame_)
        return;

    if(curGame_->currentMustGoComp())
        return; //todo warning (current must go comp)

    if(curGame_->isGameFinished())
        return onFinishGame();

    const PlayerId* const player = curGame_->getCurrentPlayer();

    const BoardData* const data = curGame_->boardData();
    row = data->getRows() - row - 1;

    if(!(curGame_->canGo(IdCell(row, column), player)))
        return; //todo warning (user can not go there)

    curGame_->Go(IdCell(row, column), player);

    syncDataWithBoard(data);

    computerGoButton_->setEnabled(curGame_->currentMustGoComp());

    if(curGame_->isGameFinished())
        return onFinishGame();

    update();
}

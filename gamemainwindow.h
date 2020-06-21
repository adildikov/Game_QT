#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include "game.h"

#include <QDialog>

namespace Ui {
class GameMainWindow;
}

class GameMainWindow : public QDialog
{
    Q_OBJECT

public:
    Game* _game;
    explicit GameMainWindow(QWidget *parent = nullptr);
    ~GameMainWindow();

private slots:
    void on_quit_clicked();
    void enterRoom(int room);


    void on_Room1_clicked();

    void on_Room2_clicked();

    void on_Room3_clicked();

    void on_Room4_clicked();

private:
    Ui::GameMainWindow *ui;
};

#endif // GAMEMAINWINDOW_H

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

    void show_inventory(QList<std::shared_ptr<Item>> items);

    void show_money(int money);

    void show_rage(int rage);

    void on_Shop_clicked();

    void on_useItem_clicked();

    void on_PeekButton_clicked();

    void on_getDocument_clicked();

private:
    Ui::GameMainWindow *ui;
};

#endif // GAMEMAINWINDOW_H

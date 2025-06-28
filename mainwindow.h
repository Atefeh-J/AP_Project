#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPalette>
#include <QResizeEvent>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QMessageBox>
#include <QTcpSocket>
#include <QGraphicsView>
#include <cardscene.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setupCardScene(CardScene* sceneObject);
    void startMainGame();

protected:
    void resizeEvent(QResizeEvent* event) override;
private slots:
    void showMainContent();

private:
    Ui::MainWindow *ui;
    // QTcpSocket* client_socket;
    void updateBackground();
    QGraphicsView* view=nullptr;
    CardScene* scene1=nullptr;
    std::vector<CardItem*>selectedCards;
};
#endif // MAINWINDOW_H

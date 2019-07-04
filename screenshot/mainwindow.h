#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <screen.h>
#include <QPixmap>
#include <QScreen>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QPixmap editPixmap;
private:
    Ui::MainWindow *ui;
    Screen * screen;

public slots:
    void on_screenbtn_clicked();
    void on_drawImg(QPixmap *p);
    void on_btn_save_clicked();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    screen = new Screen(this);

    connect(ui->pushButton_shot,SIGNAL(clicked()),this,SLOT(on_screenbtn_clicked()));
    connect(ui->pushButton_sava,SIGNAL(clicked()),this,SLOT(on_btn_save_clicked()));
    connect(screen,SIGNAL(sendpic(QPixmap *)),this,SLOT(on_drawImg(QPixmap *)));
    screen->hide();
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_screenbtn_clicked()
{
    if(ui->checkBox->isChecked()){
        this->showMinimized();
    }
    QScreen *scrPix = QGuiApplication::primaryScreen();
    QPixmap pixmap = scrPix->grabWindow(0);
    //截屏
    delete screen;
    screen = new Screen(this);
    //screen->stack.push(pixmap);
    connect(screen,SIGNAL(sendpic(QPixmap *)),this,SLOT(on_drawImg(QPixmap *)));
    /*每次按下截图按钮都要重新生成一次截屏对象，便于更改
     * 信号槽机制好像还是绑定了对象的，我以为只要是一种类就可以只声明一次就够了，后来发现不继续绑定信号槽就会失效，因为原对象消失了
    */
    screen->setPixmap(pixmap);
    screen->setWindowFlags (Qt::Window);
    //使Screen对象全屏显示
    screen->showFullScreen ();
    screen->show();

}
void MainWindow::on_drawImg(QPixmap *p)
{
    editPixmap=*p;
    ui->label_pic->setPixmap(editPixmap);
    //qDebug()<<"p_size:"<<sizeof(*p)<<endl;
    //qDebug()<<"editPixmap_size:"<<sizeof(editPixmap)<<endl;


}

void MainWindow::on_btn_save_clicked()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,"Save Image","","(*.jpg *.bmp *.png)");
    if(fileName == "")
    {
        return;
    }
    editPixmap.save(fileName,"JPG");
    QMessageBox::warning(this,"tip","Save File Success!");

}


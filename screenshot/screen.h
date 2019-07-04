#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QToolButton>
#include <QSpinBox>
#include <QColorDialog>
#include <QFontDialog>
#include <QPen>
#include <QLineEdit>
#include <QFontComboBox>
#include <QFont>
#include <qmath.h>
#include <QStack>
#include <QScreen>
class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = nullptr);
    //重写鼠标移动函数
    virtual void mouseMoveEvent(QMouseEvent *ev);
    //重写鼠标点击函数
    virtual void mousePressEvent(QMouseEvent *ev);
    //重写鼠标释放函数
    virtual void mouseReleaseEvent(QMouseEvent *ev);
    //重写绘制函数
    virtual void paintEvent(QPaintEvent *ev);
    //绘制截图边框的边框
    void paintBorder(QPoint ltPoint, QPoint rbPoint, QPainter &painter);
    //绘制截图边框的四个角
    void paintStretchRect(QPoint ltPoint, QPoint rbPoint, QPainter &painter);
    //传入刚截下的全屏图像
    void setPixmap(QPixmap map);
    //根据传过来坐标得到线性渐变对象，并设置颜色
    QLinearGradient getLinearGadient(int x, int y, int width, int height);
    //根据坐标绘制渐变
    void paintGradient(int x1, int y1, int width, int height, QPainter &painter);
    //构造界面按钮
    void creatButtons();
    //槽函数
    void on_slots();
    //设置颜色
    void setColor(QColor c);
    //设置样式
    void setStyle(int s);
    //保存当前图片入栈
    void savedCurPix();
    //检查是否需要保存图片入栈
    void checkFlag();
    //判断左上角和右下角之间的坐标是否能够用来选取
    bool isGrab(QPoint &p1, QPoint &p2);
    //绘图函数
    void paint(QPixmap & );
    //判断左下角与右上角之间的坐标
    bool isGrabLeftBottom(QPoint &p, QPoint &p2);
    //判断点是否在矩形里面
    bool pointInRect(const QPoint &, const QRectF &);
    //判断是否可以移动选取
    bool isMove(QPoint &ltPoint, QPoint &rbPoint, int moveX, int moveY);
    //鼠标移动类型
    enum MoveType {
        AREAGRAB, AREAMOVE, AREALEFTTOP, AREALEFTBOTTOM,
        AREARIGHTTOP, AREARIGHTBOTTOM,DRAWLINE,DRAWTEXT,DRAWARROW
    };
    QPixmap   savedPixmap;            //待保存的图片
    //图形栈
    QStack<QPixmap> stack;
private:
    QPixmap   pixmap;                 //画布
    //文字标签
    QLabel    * styleLabel;           //线的样式
    QLabel    * widthLabel;           //线的宽度
    QLabel    * fontLabel;            //文字字体
    QLabel    * sizeLabel;            //文字大小
    //下滑组
    QComboBox * styleComboBox;        //线的样式
    QFontComboBox * fontComboBox;     //文字字体
    QSpinBox  * sizeSpinBox;          //文字大小
    QSpinBox  * widthSpinBox;         //线的宽度
    QLineEdit * textEdit;             //文本内容
    //颜色按钮
    QToolButton *colorBtn;
    QPoint    ltPoint;                //左上角的坐标
    QPoint    rbPoint;                //右下角坐标
    QPoint    tempPoint;              //临时右下角坐标
    QPoint    begin,end;              //涂鸦的过程点
    //选区的边框的上面的四个小矩形
    QRectF    ltRect;                 //左上角矩形
    QRectF    lbRect;                 //左下角矩形
    QRectF    rtRect;                 //右上角矩形
    QRectF    rbRect;                 //右下角矩形
    //整个选取
    QRectF    pixmapRect;             //整个待截图的矩形
    MoveType  moveType;               //鼠标移动的类型
    bool      grab;                   //判断当前的点击是不是第一次截图时候的点击，后面的都是修改时候的点击
    //这里记录的是选取移动的时候的坐标
    QPoint    clickPoint;             //记录每个点击的click坐标
    QPoint    oldPoint;               //上一个移动的点的坐标
    QColor    color;                  //画笔颜色
    int       lineStyle;              //线条样式
    int       width;                  //线条粗细
    int       fontsize;               //文字字号
    QString   fontFamily;             //文字字体
    int       desktopWidth;           //桌面的宽度
    int       desktopHeight;          //桌面的高度
    bool      status;                 //判断是否可以开始涂鸦，初始为false表示不能
    bool      flag;                   //判断是否已经构成可撤销操作，如果是true则入栈，否则不截图入栈
    //Buttons
    QPushButton * btn_ok;
    QPushButton * btn_cancel;
    QPushButton * btn_save;
    QPushButton * btn_line;
    QPushButton * btn_text;
    QPushButton * btn_arrow;
    QPushButton * btn_return;




signals:
    void sendpic(QPixmap *p);
public slots:
    void on_btn_ok_clicked();         //截图完毕确认按钮
    void on_btn_cancel_clicked();     //截图取消按钮
    void on_btn_save_clicked();       //保存按钮
    void on_btn_line_clicked();       //画线按钮
    void on_btn_text_clicked();       //文本绘制按钮
    void on_btn_return_clicked();
    void on_btn_arrow_clicked();
    void showColor();
    void showStyle();
    void setWidth(int w);
    void setSize(int s);


};

#endif // SCREEN_H

#include "screen.h"
#include <QGuiApplication>
Screen::Screen(QWidget *parent) : QWidget(parent)
{
    creatButtons();
    on_slots();
    //状态初始化
    setMouseTracking(true);         //设置鼠标移动监测

    grab=true;//设置抓取状态，true表示正在抓图
    width=1;
    fontsize=1;
    status=false;//设置编辑状态，true表示可以编辑
    flag=false;//初始化设定为还未产生绘图命令,栈此时只有一张图
    stack.clear();
}
void Screen::on_slots()
{
    connect(btn_ok,SIGNAL(clicked()),this,SLOT(on_btn_ok_clicked()));
    connect(btn_cancel,SIGNAL(clicked()),this,SLOT(on_btn_cancel_clicked()));
    connect(btn_save,SIGNAL(clicked()),this,SLOT(on_btn_save_clicked()));
    connect(btn_line,SIGNAL(clicked()),this,SLOT(on_btn_line_clicked()));
    connect(btn_text,SIGNAL(clicked()),this,SLOT(on_btn_text_clicked()));
    connect(btn_arrow,SIGNAL(clicked()),this,SLOT(on_btn_arrow_clicked()));
    connect(btn_return,SIGNAL(clicked()),this,SLOT(on_btn_return_clicked()));
}
void Screen::creatButtons()
{
    //绘制文本框
    textEdit = new QLineEdit("水印",this);
    textEdit->setGeometry(1000,400,200,50);
    //绘制按钮
    btn_ok=new QPushButton("截图确认",this);
    btn_ok->setGeometry(1000,100,100,25);
    btn_cancel=new QPushButton("取消截图",this);
    btn_cancel->setGeometry(1000,150,100,25);
    btn_line=new QPushButton("line",this);
    btn_line->setGeometry(1000,200,100,25);
    btn_text=new QPushButton("text",this);
    btn_text->setGeometry(1000,250,100,25);
    btn_arrow = new QPushButton("arrow",this);
    btn_arrow->setGeometry(1000,300,100,25);
    btn_save=new QPushButton("save",this);
    btn_save->setGeometry(1150,300,100,25);
    btn_return = new QPushButton("撤销",this);
    btn_return->setGeometry(1000,350,100,25);
    //Label
    styleLabel = new QLabel(tr("线型： "),this);
    styleLabel->setGeometry(1125,200,50,25);
    widthLabel = new QLabel(tr("线宽： "),this);
    widthLabel->setGeometry(1125,225,50,25);
    fontLabel = new QLabel (tr("字体： "),this);
    fontLabel->setGeometry(1125,250,50,25);
    sizeLabel = new QLabel(tr("字号： "),this);
    sizeLabel->setGeometry(1125,275,50,25);
    //ComboBox
    styleComboBox = new QComboBox(this);
    styleComboBox->setGeometry(1175,200,100,25);
    styleComboBox->addItem(tr("SolodLine") , static_cast<int>(Qt::SolidLine));
    styleComboBox->addItem(tr("DashLine") , static_cast<int>(Qt::DashLine));
    styleComboBox->addItem(tr("DotLine") , static_cast<int>(Qt::DotLine));
    styleComboBox->addItem(tr("DashDotLine") , static_cast<int>(Qt::DashDotLine));
    styleComboBox->addItem(tr("DashDotDotLine") , static_cast<int>(Qt::DashDotDotLine));
    connect(styleComboBox,SIGNAL(activated(int)),this,SLOT(showStyle()));
    fontComboBox = new QFontComboBox(this);
    fontComboBox->setGeometry(1175,250,100,25);
    //SpinBox
    widthSpinBox = new QSpinBox(this);
    widthSpinBox->setGeometry(1175,225,100,25);
    connect(widthSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setWidth(int)));
    sizeSpinBox = new QSpinBox(this);
    sizeSpinBox->setGeometry(1175,275,100,25);
    connect(sizeSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setSize(int)));
    //toolbtn
    colorBtn = new QToolButton(this); //设置按钮的格式
    colorBtn->setGeometry(1275,200,50,50);
    QPixmap pixmap(30,30);
    pixmap.fill(Qt::black);
    colorBtn->setIcon(QIcon(pixmap));
    connect(colorBtn,SIGNAL(clicked(bool)),this,SLOT(showColor()));
    setStyle(styleComboBox->itemData(styleComboBox->currentIndex(),Qt::UserRole).toInt());
}
void Screen::showColor()
{
    QColor c = QColorDialog::getColor(Qt::black ,this);
    if(c.isValid())
    {   //qDebug()<<"validColor"<<endl;
        setColor(c);
        QPixmap p(30,30);
        p.fill(color);
        colorBtn->setIcon(QIcon(p));
    }
}

void Screen::showStyle()
{
   setStyle(styleComboBox->itemData(styleComboBox->currentIndex(),Qt::UserRole).toInt());
}
void Screen::setStyle(int s)
{
    lineStyle = s;
}
void Screen::setWidth(int w)
{
    width = w;
}
void Screen::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
    if(!grab){
      return;
    }
    if( ltPoint == tempPoint || tempPoint == rbPoint && rbPoint == QPoint(0, 0)) {
           paintGradient(0, 0, rect().width(), rect().height(), painter);
            return;
    }
    //矩形上方的渐变
    paintGradient(0, 0, rect().width(), ltPoint.y(), painter);
    //矩形左边的渐变
    paintGradient(0, ltPoint.y(), ltPoint.x(), rect().height(), painter);
    //矩形正下方的渐变
    paintGradient(ltPoint.x(), tempPoint.y(), tempPoint.x() - ltPoint.x(), rect().height(), painter);
    //矩形右边的渐变
    paintGradient(tempPoint.x(), ltPoint.y(), rect().width(), rect().height(), painter);
    //保存画笔的状态
    painter.save();
    //绘制矩形边界
    paintBorder(ltPoint, tempPoint, painter);
    painter.restore();
    //画四个顶点的矩形
    paintStretchRect(ltPoint, tempPoint, painter);


}
void Screen::setPixmap(QPixmap map)
{
    this->pixmap=map;
}

QLinearGradient Screen::getLinearGadient(int x, int y, int width, int height) {
    QLinearGradient grad(x, y, width, height);
    grad.setColorAt(0.0, QColor(0, 0, 0, 100));
    return grad;
}

void Screen::paintGradient(int x1, int y1, int width, int height, QPainter &painter) {
    QLinearGradient grad(x1, y1, width, height);
    grad.setColorAt(0.0, QColor(0, 0, 0, 100));
    painter.fillRect(x1, y1, width, height, grad);
}
void Screen::paintBorder(QPoint ltPoint, QPoint rbPoint, QPainter &painter) {
    QPen pen;
    //设置画笔颜色
    pen.setColor(Qt::blue);
    //设置画笔宽度
    pen.setWidth(1);
    painter.setPen(pen);
    //画左边界
    painter.drawLine(ltPoint.x(), ltPoint.y(), ltPoint.x(), rbPoint.y());
    //画上边界
    painter.drawLine(ltPoint.x(), ltPoint.y(), rbPoint.x(), ltPoint.y());
    //画右边界
    painter.drawLine(rbPoint.x(), ltPoint.y(), rbPoint.x(), rbPoint.y());
    //画下边界
    painter.drawLine(ltPoint.x(), rbPoint.y(), rbPoint.x(), rbPoint.y());
}
void Screen::paintStretchRect(QPoint ltPoint, QPoint rbPoint, QPainter &painter) {
    //每个矩形算6的长度
    //左上角
    ltRect.setX(ltPoint.x() - 3);
    ltRect.setY(ltPoint.y() - 3);
    ltRect.setWidth(6);
    ltRect.setHeight(6);
    //右上角
    rtRect.setX(rbPoint.x() - 3);
    rtRect.setY(ltPoint.y() - 3);
    rtRect.setWidth(6);
    rtRect.setHeight(6);
    //左下角
    lbRect.setX(ltPoint.x() - 3);
    lbRect.setY(rbPoint.y() - 3);
    lbRect.setWidth(6);
    lbRect.setHeight(6);
    //右下角
    rbRect.setX(rbPoint.x() - 3);
    rbRect.setY(rbPoint.y() - 3);
    rbRect.setWidth(6);
    rbRect.setHeight(6);
    //绘制用于拉伸的矩形
    QBrush brush(Qt::blue);
    painter.fillRect(ltRect, brush);
    painter.fillRect(lbRect, brush);
    painter.fillRect(rtRect, brush);
    painter.fillRect(rbRect, brush);
}
void Screen::mousePressEvent(QMouseEvent *e) {
    //判断左键点击事件

   if(!status) {
        if( e->button() & Qt::LeftButton && !pointInRect(e->pos(),pixmapRect)) {
        ltPoint = e->pos();
        repaint();
        qDebug() << "ltPoint:" << ltPoint;
        }
        //记录此时点击的坐标，主要用作移动选区
        clickPoint = e->pos();
        oldPoint   = clickPoint;
   }
   else
   {
       if(moveType==DRAWLINE)
           {
           flag=true;
           checkFlag();
       }
       if(pointInRect(e->pos(),pixmapRect))
       begin=e->pos();

   }
}
void Screen::mouseMoveEvent(QMouseEvent *e) {

    QPoint p = e->pos();
    //临时的point
    QPoint m_tempPoint;
    //左键点击移动事件
    if(!status){//如果图片还没有确定
     if( e->buttons() & Qt::LeftButton) {
        switch(moveType) {
        case AREAGRAB:
            //如果移动后的坐标大于矩形左上角的坐标
            if(isGrab(ltPoint, p)) {
                tempPoint = p;
                repaint();
            }
           //qDebug() << "截图";
            break;
        case AREALEFTBOTTOM:
            //qDebug() << "左下角";
            //封装右上角的坐标
            m_tempPoint.setX(tempPoint.x());
            m_tempPoint.setY(ltPoint.y());
            if(isGrabLeftBottom(p, m_tempPoint)) {
                ltPoint.setX(p.x());
                tempPoint.setY(p.y());
            }
            break;
        case AREALEFTTOP:
           // qDebug() << "左上角";
            if( isGrab(p, tempPoint)) {
                ltPoint = p;
            }
            break;
        case AREARIGHTBOTTOM:
          //  qDebug() << "右下角";
            if(isGrab(ltPoint, p)) {
                tempPoint = p;
            }
            break;
        case AREARIGHTTOP:
           //qDebug() << "右上角";
            //封装左下角的坐标
            m_tempPoint.setX(ltPoint.x());
            m_tempPoint.setY(tempPoint.y());
            if(isGrabLeftBottom(m_tempPoint, p)) {
                ltPoint.setY(p.y());
                tempPoint.setX(p.x());
            }
            break;
        case AREAMOVE: {
          qDebug() << "区域中间";
            //记录此时移动的距离
            int moveX = p.x() - oldPoint.x();
            int moveY = p.y() - oldPoint.y();
            //整个选取移动的时候两个点的坐标都要移动
            if(isMove(ltPoint, tempPoint, moveX, moveY)) {
                ltPoint.setX(ltPoint.x() + moveX);     //左上角的x坐标
                ltPoint.setY(ltPoint.y() + moveY);     //左上角的y坐标
                tempPoint.setX(tempPoint.x() + moveX); //右下角的x坐标
                tempPoint.setY(tempPoint.y() + moveY); //右下角的y坐标
                //将此时的移动坐标记录
                oldPoint = p;
            }
        }
            break;
        }
     } else {
         //根据鼠标移动的位置该表鼠标的样式
        if(pointInRect(p, ltRect)) {
           setCursor(Qt::SizeFDiagCursor);
           moveType = AREALEFTTOP;
        } else if(pointInRect(p, rtRect)) {
            setCursor(Qt::SizeBDiagCursor);
             moveType = AREARIGHTTOP;
        } else if(pointInRect(p, lbRect)) {
            setCursor(Qt::SizeBDiagCursor);
             moveType = AREALEFTBOTTOM;
        } else if(pointInRect(p, rbRect)) {
            setCursor(Qt::SizeFDiagCursor);
             moveType = AREARIGHTBOTTOM;
        } else if(pointInRect(p, pixmapRect)) {
            setCursor(Qt::SizeAllCursor);
             moveType = AREAMOVE;
        } else {
            setCursor(Qt::ArrowCursor);
            moveType = AREAGRAB;
        }
     }
    //移动之后重绘
     repaint();
    }
    else{   if(e->buttons() & Qt::LeftButton&&pointInRect(p,pixmapRect)&&moveType!=DRAWARROW){
            end=p;
            paint(pixmap);
        }

    }
}

bool Screen::isMove(QPoint &ltPoint, QPoint &rbPoint, int moveX, int moveY) //判断是不是可以移动
{
    if( (ltPoint.x() + moveX) < 0 || (ltPoint.y() + moveY) < 0
            || (rbPoint.x() + moveX) >= desktopWidth || (rbPoint.y() + moveY)
            >= desktopHeight) {
        return false;
    }
    return true;
}
void Screen::mouseReleaseEvent(QMouseEvent *e) {
    //左键释放事件
    if(!status)
    {
        if( e->button() & Qt::LeftButton) {
        //  rbPoint = e->pos();
        rbPoint = tempPoint;
        //        QPixmap pix = pixmap.copy(ltPoint.x(), ltPoint.y(), rbPoint.x() - ltPoint.x(), rbPoint.y() - ltPoint.y());
        //        savedPixmap = pix;
        //        //保存图片
        //savePixmap();
        pixmapRect.setX(ltPoint.x());
        pixmapRect.setY(ltPoint.y());
        pixmapRect.setWidth(rbPoint.x() - ltPoint.x());
        pixmapRect.setHeight(rbPoint.y() - ltPoint.y());
        desktopWidth = pixmap.width();
        desktopHeight = pixmap.height();
        //grab = false;
        }
    }
    else{
        switch(moveType)
        {
            case DRAWARROW:
            if(pointInRect(e->pos(),pixmapRect)){
                flag=true;
                checkFlag();
            }
            break;
            case DRAWLINE:
//            flag=true;
//             checkFlag();
            break;
            case DRAWTEXT:
            if(pointInRect(e->pos(),pixmapRect))
            flag=true;
             checkFlag();
            break;
        }
        if(pointInRect(e->pos(),pixmapRect)){
            end=e->pos();
            paint(pixmap);
        }
    }
}

/*
当作p的x坐标小于p2的x坐标切p的y坐标大于p2的y坐标
 */
bool Screen::isGrabLeftBottom(QPoint &p, QPoint &p2) {
    if( p.x() < p2.x() && p.y() > p2.y())
        return true;
    return false;
}

/*
当p2的坐标大于p1是返回true,否则返回false
 */
bool Screen::isGrab(QPoint &p1, QPoint &p2) {
    if( p2.x() > p1.x() && p2.y() > p1.y())
        return true;
    return false;
}

bool Screen::pointInRect(const QPoint &p1, const QRectF &r)
{
    if(r.contains(p1))return true;
    return false;
}

void Screen::on_btn_ok_clicked(){

    //保存图片
    //savePixmap();
    status = true;
    grab=false;//抓图结束
    QScreen *scrPix = QGuiApplication::primaryScreen();
    QPixmap tempPix= scrPix->grabWindow(0);
    pixmap=tempPix;


}
void Screen::on_btn_cancel_clicked(){
    this->close();
}
void Screen::on_btn_line_clicked()
{
    if(status)
    {
        moveType=DRAWLINE;
    }
}
void Screen::on_btn_text_clicked()
{
    if(status)
    {
        moveType=DRAWTEXT;
    }
}
void Screen::on_btn_arrow_clicked()
{
    if(status)
    {
        moveType=DRAWARROW;
    }
}
void Screen::on_btn_return_clicked()
{
    qDebug()<<"准备出栈"<<endl;
    if(status&&!stack.empty())
    {
        QPixmap temp=stack.pop();
        if(sizeof(temp)){
            qDebug()<<"出栈成功"<<"size : "<<stack.size()<<endl;
        }
        pixmap=temp;

        update();
    }
}
void Screen::on_btn_save_clicked()
{
    QPixmap pix = pixmap.copy(ltPoint.x(), ltPoint.y(), rbPoint.x() - ltPoint.x(), rbPoint.y() - ltPoint.y());
    savedPixmap = pix;
    emit sendpic(&savedPixmap);
    close();
}

void Screen::paint(QPixmap &pix)        //绘图函数，先画到画布上
{

    QPainter pp(&pix);
    QPen pen;
    pen.setStyle((Qt::PenStyle)lineStyle);
    pen.setWidth(widthSpinBox->value());
    pen.setColor(color);
    pp.setPen(pen);
    QFont font;
    font.setFamily(this->fontComboBox->currentFont().toString());
    //qDebug()<<"fontFamily:"<<fontComboBox->font().toString()<<endl;
    font.setPointSize(this->sizeSpinBox->value());
    //qDebug()<<"width"<<this->sizeSpinBox->value()<<endl;
    pp.setFont(font);
    if(moveType==DRAWLINE)//线
    {
        pp.drawLine(begin,end);
        begin=end;
    }

    if(moveType==DRAWTEXT)//文本
    {
        pp.drawText(begin.x(),begin.y(),this->textEdit->text());
    }
    if(moveType==DRAWARROW)//箭头
    {
        float x1 = begin.x();                                     //取points[0]起点的x
        float y1 = begin.y();                                     //取points[0]起点的y
        float x2 = end.x();                                       //取points[count-1]终点的x
        float y2 = end.y();                                       //取points[count-1]终点的y
        float l = 10.0;                                           //箭头的长度
        float a = 0.5;                                            //箭头与线段角度
        float x3 = x2 - l * cos(atan2((y2 - y1) , (x2 - x1)) - a);//计算箭头的终点（x3,y3）
        float y3 = y2 - l * sin(atan2((y2 - y1) , (x2 - x1)) - a);
        float x4 = x2 - l * sin(atan2((x2 - x1) , (y2 - y1)) - a);//计算箭头的终点（x4,y4）
        float y4 = y2 - l * cos(atan2((x2 - x1) , (y2 - y1)) - a);
        pp.drawLine(x2,y2,x3,y3);                                 //绘制箭头(x2,y2,x3,y3)
        pp.drawLine(x2,y2,x4,y4);                                 //绘制箭头(x2,y2,x4,y4)
        pp.drawLine(begin,end);                                   //绘制主干箭头(begin,end)
    }
    update();
}
void Screen::setColor(QColor c)         //设置颜色
{
    color=c;
}
void Screen::setSize(int s)             //设置大小
{
    fontsize=s;
}
void Screen::savedCurPix()              //保存当前图像
{
    qDebug()<<"开始截图"<<endl;
    QScreen *scrPix = QGuiApplication::primaryScreen();
    QPixmap tempPix= scrPix->grabWindow(0);
    if(sizeof(tempPix)){
        qDebug()<<"截到图了"<<endl;
    }
    stack.push(tempPix);
    qDebug()<<"推进栈了"<<"size："<<stack.size()<<endl;
}
void Screen::checkFlag()                //检查图像是否发声变化，是否需要截图
{
    if(flag){
        qDebug()<<"快截图"<<endl;
        savedCurPix();//要求截下图片 并入栈
        flag=false;
    }
}
//void Screen::savePixmap() {
//    //生成图片名称
//    QString picName = "截图";
//    QTime time;
//    //获取当前系统时间，用做伪随机数的种子
//    time = QTime::currentTime();
//    qsrand(time.msec() + time.second() * 1000);
//    //随机字符串
//    QString randStr;
//    randStr.setNum(qrand());
//    picName.append(randStr);
//    picName.append(".jpg");
//    qDebug() << "picName:" << picName << "qrand:" << qrand();
//    savedPixmap.save(picName, "JPG");
//}

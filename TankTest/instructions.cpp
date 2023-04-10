#include "instructions.h"
#include <QPainter>
#include <QTextEdit>
Instructions::Instructions()
{
    setFixedSize(320, 380);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    QPalette pal = QPalette();
    //sets the palette color to black
    pal.setColor(QPalette::Window, Qt::black);
    //Allows window to be set to a color
    setAutoFillBackground(true);
    //sets the color of the window
    setPalette(pal);

    QPushButton *close = new QPushButton("Close", this);
    //Adjusting style for the close button
    close->setStyleSheet("QPushButton {color: blqack; background-color: lightGreen; border-style: outset; border-width: 1px; border-color: darkGreen;} } QPushButton:pressed { background-color: darkGreen;}");
    //Setting size and location of the close button
    close->setGeometry(width() / 2 - 70, height() - 70, 140, 60);
    close->show();


    connect(close, SIGNAL(clicked()), this, SLOT(closeClicked()));
}
void Instructions::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::green);
    painter.setPen(pen);
    //Draws border lines
    painter.drawRect(0, 0, width() - 1, height() - 1);
    painter.drawLine(0, 50, 320, 50);
    pen.setColor(Qt::darkGreen);
    painter.setPen(pen);
    //Draws instructions
    painter.setFont(QFont("Times", 30));
    painter.drawText(70, 40, "Instructions");

    painter.setFont(QFont("Times", 20));
    painter.drawText(7, 100, "W: Move Forward");
    painter.drawText(7, 130, "S: Move Backward");
    painter.drawText(7, 160, "A: Rotate Left");
    painter.drawText(7, 190, "D: Rotate Right");
    painter.drawText(7, 220, "Space: Shoot");
    painter.drawText(7, 250, "Mouse: Aim");

    QWidget::paintEvent(e);
}

void Instructions::closeClicked(){
    delete this;
}

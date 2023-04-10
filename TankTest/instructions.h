#pragma once

#include <QObject>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QPalette>
#include <QPaintEvent>

class Instructions : public QWidget
{
    Q_OBJECT
public:
    Instructions();

    void paintEvent(QPaintEvent* e);
private slots:
    void closeClicked();
};



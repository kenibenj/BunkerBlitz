#pragma once
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include <QPalette>
#include <QPaintEvent>

class PauseMenu :
    public QWidget
{
    Q_OBJECT
public: 
    PauseMenu();

    void keyPressEvent(QKeyEvent* event);

    void paintEvent(QPaintEvent* e);


    
private slots:
    void resumeButtonClicked();
    void returnButtonClicked();
};


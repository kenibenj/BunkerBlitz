#pragma once
#include <QWidget>

class PauseMenu :
    public QWidget
{
    Q_OBJECT
public: 
    PauseMenu();
    
private slots:
    void resumeButtonClicked();
};


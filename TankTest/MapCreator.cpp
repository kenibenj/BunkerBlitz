#include "map_creator.h"
#include <QScreen>
#include <QApplication>
#include <QDebug>

MapCreator::MapCreator(const std::string& name_of_file) : file_name(name_of_file) {}

void MapCreator::setFile(const std::string& name_of_file) {
    file_name = name_of_file;
}

void MapCreator::CreateMap(QGraphicsScene* scene) {
    std::ifstream file(file_name);

    //tried different values for this, looks like dividing by 100 is good, we can reset it as our needs.
    int w = QGuiApplication::screens().at(0)->availableGeometry().width() / 1000;
    int h = QGuiApplication::screens().at(0)->availableGeometry().height() / 1000;

    //updates the wall size in the map
    qreal wall_size = 92;

    if (file.is_open())
    {

        int row = 0; // rows
        int col = 0; //columns
        int ch;

        //while not end of textfile
        while ((ch = file.get()) != EOF)
        {
        //check the characters in the textfile.
            //If the character is nextline, then increment the row
            if ((char)ch == '\n') {
                ++row;
                col = 0;
            }
            //If the character is space, then increment the column 
            else if ((char)ch != ' ') {
                ++col;
            }
            //If the character is 1, then we make the wall objects
            if (ch == '1') {

                //Make a new wall object and add it to the scene
                Wall* wall = new Wall(scene);
                scene->addItem(wall);

                //make walls based on the columns and the rows
                wall->setPos((col - 1) * wall_size - w, row * wall_size - h + 75 + 1);

            }

        }

        file.close(); //Close the textFile
    }

}
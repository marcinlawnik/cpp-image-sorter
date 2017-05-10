#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QString>
#include <QDir>
#include <QImage>

class ImageController
{
public:
    ImageController();
    void loadDir(QString dir);
    QString getCurrentDir();
    QString getCurrentImagePath();
    QString getCurrentImagePathFull();
    QStringList getImageList();
    void nextImage();
    void previousImage();
    int getCurrentImageNumber();
    int getImageListSize();
    void toggleBad();
    void toggleGood();
    bool isCurrentImageBad();
    bool isCurrentImageGood();
    QStringList getGoodImageList();
    QStringList getBadImageList();


private:
    QDir *currentDir;
    QStringList imageList;
    QString currentImagePath;
    int currentImageKey;
    int imageListSize;
    QStringList goodImageList;
    QStringList badImageList;
};

#endif // IMAGECONTROLLER_H

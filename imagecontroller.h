#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <QString>
#include <QDir>
#include <QImage>
#include <QSettings>
#include <Magick++.h>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QImage>

class ImageController : public QObject
{
    Q_OBJECT
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
    QString getCurrentImageName();
    //Copying functions
    int doCopyGoodImages();
    int doCopyBadImages();
    void doMakeThumbs();
    void doGenerateAlbum();
    void doMakeThumbsAsync();
    void doGenerateImagesWithWatermark();
    void doGenerateImagesWithWatermarkAsync();
    QImage* toQImage(Magick::Image *image);
    Magick::Image* toImage(QImage* qimage);

signals:
    void thumbsCountUpdated(int count, QString file);

private:
    QString currentDirAbsolutePath;
    QDir *currentDir;
    QStringList imageList;
    QString currentImagePath;
    int currentImageKey;
    int imageListSize;
    QStringList goodImageList;
    QStringList badImageList;
    QSettings *settings;
};

#endif // IMAGECONTROLLER_H

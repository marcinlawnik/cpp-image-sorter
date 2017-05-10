#include "imagecontroller.h"
ImageController::ImageController()
{
//    QStringList goodImageList = new QStringList();
//    QStringList badImageList = new QStringList();
}

void ImageController::loadDir(QString dir)
{
    this->currentDir = new QDir();
    this->currentDir->cd(dir);
    this->getImageList();
    //Set first image
    this->currentImagePath = this->imageList.first();
}

QString ImageController::getCurrentDir()
{
    return this->currentDir->absolutePath();
}

QStringList ImageController::getImageList()
{
    QStringList imageFilters;
    //filter out images only
    imageFilters << "*.png" << "*.jpg" << "*.jpeg" << "*.bmp";
    this->imageList = this->currentDir->entryList(imageFilters, QDir::Files|QDir::Readable,QDir::Name);
    //TODO Something if folder has no images
    this->currentImageKey = 0;
    this->imageListSize = this->imageList.size();
    return this->imageList;
}

QString ImageController::getCurrentImagePath()
{
   return this->currentDir->absolutePath() + QDir::separator() + this->currentImagePath;
}

void ImageController::nextImage()
{
    if((this->currentImageKey+1) == this->imageListSize)
    {
        //do nothing if its the last image
    } else {
        this->currentImageKey++;
        this->currentImagePath = this->imageList.at(this->currentImageKey);
    }
}

void ImageController::previousImage()
{
    if(this->currentImageKey == 0)
    {
        //do nothing if its the first image
    } else {
        this->currentImageKey--;
        this->currentImagePath = this->imageList.at(this->currentImageKey);
    }
}

int ImageController::getCurrentImageNumber()
{
    return this->currentImageKey;
}

int ImageController::getImageListSize()
{
    return this->imageListSize;
}

void ImageController::toggleBad()
{
    if (!this->badImageList.contains(this->currentImagePath))
    {
        this->badImageList.append(this->currentImagePath);
    } else {
        //remove
        this->badImageList.removeAll(this->currentImagePath);
    }
}

void ImageController::toggleGood()
{
    if (!this->goodImageList.contains(this->currentImagePath))
    {
        this->goodImageList.append(this->currentImagePath);
    } else {
        //remove
        this->goodImageList.removeAll(this->currentImagePath);
    }
}

QStringList ImageController::getGoodImageList()
{
    return this->goodImageList;
}

QStringList ImageController::getBadImageList()
{
    return this->badImageList;
}

bool ImageController::isCurrentImageBad()
{
    if(this->badImageList.contains(this->currentImagePath))
    {
        return true;
    }
    return false;
}

bool ImageController::isCurrentImageGood()
{
    if(this->goodImageList.contains(this->currentImagePath))
    {
        return true;
    }
    return false;
}

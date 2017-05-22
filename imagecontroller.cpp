#include "imagecontroller.h"

ImageController::ImageController()
{
//    QStringList goodImageList = new QStringList();
//    QStringList badImageList = new QStringList();
    this->settings = new QSettings();
}

void ImageController::loadDir(QString dir)
{
    this->currentDir = new QDir();
    this->currentDir->cd(dir);
    this->getImageList();
    //Clear good and bad image lists
    this->goodImageList.clear();
    this->badImageList.clear();
    //Set first image
    this->currentImagePath = this->imageList.first();
    this->currentDirAbsolutePath =  this->currentDir->absolutePath() + "\\";

}

QString ImageController::getCurrentDir()
{
    return this->currentDir->absolutePath();
}

Magick::Image* ImageController::toImage(QImage* qimage)
{
    qDebug() << "toImage:" << qimage->width() << qimage->height();

    Magick::Image *newImage = new Magick::Image(Magick::Geometry(qimage->width(), qimage->height()), Magick::ColorRGB(0.5, 0.2, 0.3));

    double scale = 1 / 256.0;
    newImage->modifyImage();
    Magick::PixelPacket *pixels;
    Magick::ColorRGB mgc;
    for (int y = 0; y < qimage->height(); y++) {
        pixels = newImage->setPixels(0, y, newImage->columns(), 1);
        for (int x = 0; x < qimage->width(); x++) {
            QColor pix = qimage->pixel(x, y);
            //      *pixels++ = Magick::ColorRGB(256 * pix.red(), 256 * pix.green(), 256 * pix.blue());
            mgc.red(scale *pix.red());
            mgc.green(scale *pix.green());
            mgc.blue(scale *pix.blue());
            //      *pixels++ = Magick::ColorRGB(scale *pix.red(), scale * pix.green(), scale * pix.blue());
            *pixels++ = mgc;
        }
        newImage->syncPixels();
    }

    return newImage;
}


QImage* ImageController::toQImage(Magick::Image *image)
{
    qDebug() << "toQImage:" << image->columns() << image->rows();

    QImage *newQImage = new QImage(image->columns(), image->rows(), QImage::Format_RGB32);
    const Magick::PixelPacket *pixels;
    Magick::ColorRGB rgb;
    for (int y = 0; y < newQImage->height(); y++) {
        pixels = image->getConstPixels(0, y, newQImage->width(), 1);
        for (int x = 0; x < newQImage->width(); x++) {
            rgb = (*(pixels + x));
            newQImage->setPixel(x, y, QColor((int) (255 * rgb.red())
                                             , (int) (255 * rgb.green())
                                             , (int) (255 * rgb.blue())).rgb());
        }
    }
    return newQImage;
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

QString ImageController::getCurrentImageName()
{
    return this->imageList.at(this->currentImageKey);
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

int ImageController::doCopyGoodImages()
{
    if(this->goodImageList.size() != 0)
    {
        //create directory (make sure it exists)
        QString goodDirName = this->settings->value("dir/nameGood", "good").toString();
        this->currentDir->mkdir(goodDirName);
        QString sourcepath = this->currentDirAbsolutePath;
        int i=0;
        for(i=0;i<this->goodImageList.size();i++)
        {
            QFile::copy(sourcepath + this->goodImageList.at(i), sourcepath + goodDirName + "/"+this->goodImageList.at(i));
        }
        return i;
    } else {
        return 0;
    }

}

int ImageController::doCopyBadImages()
{
    if(this->badImageList.size() != 0)
    {
        //create directory (make sure it exists)
        QString badDirName = this->settings->value("dir/nameBad", "bad").toString();
        this->currentDir->mkdir(badDirName);
        QString sourcepath = this->currentDirAbsolutePath;
        int j=0;
        for(j=0;j<this->badImageList.size();j++)
        {
            QFile::copy(sourcepath + this->badImageList.at(j), sourcepath + badDirName + "/"+this->badImageList.at(j));
        }
        return j;
    } else {
        return 0;
    }

}

void ImageController::doMakeThumbs()
{
    if(this->goodImageList.size() != 0)
    {

        using namespace Magick;
        Image source;
        Image thumb;
        QString thumbsDirName = this->settings->value("dir/nameThumbs", "thumbs").toString();
        //Make the directory

        this->currentDir->mkdir(thumbsDirName);
        QString sourcepath = this->currentDirAbsolutePath;
        //TODO Refactor into separate function
        int k=0;
        int j=0;
        for(k=0;k<this->goodImageList.size();k++)
        {
            try {
                // Read a file into image object
                source.read(sourcepath.toStdString() + this->goodImageList.at(k).toStdString());

                //Split filename
                QString inFile = this->goodImageList.at(k);
                //TODO fix this for files with multiple dots
                QString outFilename = inFile.split(".").at(0) + "_thumb_";
                QString outExtension = inFile.split(".").last();
                //Generate thumbs in different sizes
                //List of sizes
                QStringList thumbSizes;
                thumbSizes << "320x240" << "640x480" << "800x600" << "1280x720";
                //Create folders
                QString thumbsDirName = this->settings->value("dir/nameThumbs", "thumbs").toString();
                this->currentDir->cd(thumbsDirName);
                foreach (QString size, thumbSizes) {
                    this->currentDir->mkdir(size);
                }
                this->currentDir->cdUp();
                //Generate thumbs
                foreach (QString size, thumbSizes) {
                    thumb = source;
                    // Resize image to specified size
                    thumb.thumbnail( Geometry(size.split("x").first().toInt(),size.split("x").last().toInt()) );
                    QString outFilename2 = outFilename+ size +"."+outExtension;
                    QString outPath = sourcepath + thumbsDirName + "/"+size+"/"+outFilename2;
                    // Write the image to a file
                    thumb.write( outPath.toStdString());
                    //update window
                    j++;
                    emit this->thumbsCountUpdated(j, outFilename2);
                }
            }
            catch( Exception &error_ )
            {
                qDebug() << "Caught exception: " << error_.what();
            }
        }
    } else {
        //do nothing, no files to generate thumbs for
    }
}

void ImageController::doGenerateAlbum()
{
    /*
    if(this->goodImageList.size() != 0)
    {

        using namespace Magick;
        Image source;
        Image thumb;
        QString sourcepath = this->currentDirAbsolutePath;
        //TODO Refactor into separate function
        for(k=0;k<this->goodImageList.size();k++)
        {
            try {
                // Read a file into image object
                source.read(sourcepath.toStdString() + this->goodImageList.at(k).toStdString());

                //Split filename
                QString inFile = this->goodImageList.at(k);
                //TODO fix this for files with multiple dots
                QString outFilename = inFile.split(".").at(0) + "_thumb_";
                QString outExtension = inFile.split(".").last();
                //Generate thumbs in different sizes
                //List of sizes
                QStringList thumbSizes;
                thumbSizes << "320x240" << "640x480" << "800x600" << "1280x720";
                //Create folders
                QString thumbsDirName = this->settings->value("dir/nameThumbs", "thumbs").toString();
                this->currentDir->cd(thumbsDirName);
                foreach (QString size, thumbSizes) {
                    this->currentDir->mkdir(size);
                }
                this->currentDir->cdUp();
                //Generate thumbs
                foreach (QString size, thumbSizes) {
                    thumb = source;
                    // Resize image to specified size
                    thumb.thumbnail( Geometry(size.split("x").first().toInt(),size.split("x").last().toInt()) );
                    QString outFilename2 = outFilename+ size +"."+outExtension;
                    QString outPath = sourcepath + thumbsDirName + "/"+size+"/"+outFilename2;
                    // Write the image to a file
                    thumb.write( outPath.toStdString());
                    //update window
                    j++;
                    emit this->thumbsCountUpdated(j, outFilename2);
                }
            }
            catch( Exception &error_ )
            {
                qDebug() << "Caught exception: " << error_.what();
            }
        }
    } else {
        //do nothing, no files to generate thumbs for
    }
    */
}

void ImageController::doMakeThumbsAsync()
{
    QtConcurrent::run(this, &ImageController::doMakeThumbs);
}

void ImageController::doGenerateImagesWithWatermark()
{
    if(this->goodImageList.size() != 0)
    {

        using namespace Magick;
        Image source;
        QString watermarkDirName = this->settings->value("dir/nameWatermark", "watermarked").toString();
        //Make the directory

        this->currentDir->mkdir(watermarkDirName);
        QString sourcepath = this->currentDirAbsolutePath;
        //Load watermark image
        //QImage qimage(":/images/watermark.png");
        //Generate watermarks
        Image watermark;
        watermark.read(sourcepath.toStdString() + "watermark.png");
        //watermark= this->toImage(&qimage);
        //TODO Refactor into separate function
        int k=0;
        for(k=0;k<this->goodImageList.size();k++)
        {
            try {
                // Read a file into image object
                source.read(sourcepath.toStdString() + this->goodImageList.at(k).toStdString());

                //Split filename
                QString inFile = this->goodImageList.at(k);
                //TODO fix this for files with multiple dots
                QString outFilename = inFile.split(".").at(0) + "_watermark";
                QString outExtension = inFile.split(".").last();

                //source.artifact("compose:args", "25%");
                source.composite(watermark, GravityType::SouthEastGravity, CompositeOperator::DissolveCompositeOp);
                //source.gaussianBlur(5,10);

                QString outFilename2 = outFilename +"."+outExtension;
                QString outPath = sourcepath + watermarkDirName + "/" + outFilename2;
                // Write the image to a file
                source.write(outPath.toStdString());
                //update window
                //TODO Add signal
                //emit this->thumbsCountUpdated(k, outFilename2);
            }
            catch( Exception &error_ )
            {
                qDebug() << "Caught exception: " << error_.what();
            }
        }
    } else {
        //do nothing, no files to generate thumbs for
    }
}

void ImageController::doGenerateImagesWithWatermarkAsync()
{
    QtConcurrent::run(this, &ImageController::doGenerateImagesWithWatermark);
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setup ImageController
    setupImageController();
    setupProgressBar();
    imagecopier = new ImageCopier();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionInformacje_o_cpp_image_sorter_triggered()
{
    helpdialog = new HelpDialog(this);
    helpdialog->show();
}

void MainWindow::setupImageController()
{
    //Construct new instance of ImageController
    imagecontroller = new ImageController();
    this->loadNewFolder("");
}

void MainWindow::setupProgressBar()
{
    ui->progressBar->setMaximum(this->imagecontroller->getImageListSize());
    this->updateProgressBar();
}

void MainWindow::updateCheckboxes()
{
    //update good checkbox
    if (this->imagecontroller->isCurrentImageGood())
    {
        ui->checkBox_good->setCheckState(Qt::Checked);
    } else {
        ui->checkBox_good->setCheckState(Qt::Unchecked);
    }
    //update bad checkbox
    if (this->imagecontroller->isCurrentImageBad())
    {
        ui->checkBox_bad->setCheckState(Qt::Checked);
    } else {
        ui->checkBox_bad->setCheckState(Qt::Unchecked);
    }
}

void MainWindow::updateProgressBar()
{
    ui->progressBar->setValue(this->imagecontroller->getCurrentImageNumber()+1);
    QString progressBarText = " Obrazek: " + QString::number(this->imagecontroller->getCurrentImageNumber()+1) + "/" + QString::number(this->imagecontroller->getImageListSize());
    ui->progressBar->setFormat( progressBarText );
}


void MainWindow::on_button_listaobrazow_clicked()
{
    //get list of all image files in working directory
    //Convert QStringList to string
    QStringList list = imagecontroller->getImageList();
    //open new text dialog with image list
    imagelistdialog = new ImageListDialog();
    imagelistdialog->setFileList(list.join("\r\n"));
    imagelistdialog->show();
}

void MainWindow::on_nastepny_clicked()
{
    //load next image
    imagecontroller->nextImage();
    this->loadImage();
}

void MainWindow::on_poprzedni_clicked()
{
    //load previous image
    imagecontroller->previousImage();
    this->loadImage();
}

void MainWindow::loadImage()
{
    imageObject->load(imagecontroller->getCurrentImagePath());
    image = QPixmap::fromImage(*imageObject);
    //clear scene
    scene->clear();
    //add image to scene
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    this->updateProgressBar();

    //Update checkboxes
    this->updateCheckboxes();

    //Display image path
    //ui->directory_label->setText(this->imagecontroller->getCurrentImagePath());

}



void MainWindow::showEvent(QShowEvent *)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::loadNewFolder(QString dir)
{
    //Load current directory
    this->imagecontroller->loadDir(dir);
    //Display working directory in main window
    ui->directory_label->setText(this->imagecontroller->getCurrentDir());
    //Load first image
    imageObject = new QImage();
    imageObject->load(this->imagecontroller->getCurrentImagePath());

    image = QPixmap::fromImage(*imageObject);

    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());
    ui->graphicsView->setScene(scene);

    this->setupProgressBar();
    this->updateCheckboxes();
}


void MainWindow::on_actionOtw_rz_filder_triggered()
{
    //Load selected folder
    QString dir = QFileDialog::getExistingDirectory();
    this->loadNewFolder(dir);
}

void MainWindow::on_good_clicked()
{
    this->imagecontroller->toggleGood();
    //Update checkbox
    this->updateCheckboxes();
}

void MainWindow::on_bad_clicked()
{
    this->imagecontroller->toggleBad();
    //Update checkbox
    this->updateCheckboxes();
}

void MainWindow::on_goodimagelist_clicked()
{
    //get list of all image files in working directory
    //Convert QStringList to string
    QStringList list = imagecontroller->getGoodImageList();
    //open new text dialog with image list
    imagelistdialog = new ImageListDialog(this);
    imagelistdialog->setFileList(list.join("\r\n"));
    imagelistdialog->show();
}

void MainWindow::on_badimagelist_clicked()
{
    //get list of all image files in working directory
    //Convert QStringList to string
    QStringList list = imagecontroller->getBadImageList();
    //open new text dialog with image list
    imagelistdialog = new ImageListDialog(this);
    imagelistdialog->setFileList(list.join("\r\n"));
    imagelistdialog->show();
}

void MainWindow::on_doSortButton_clicked()
{
    //TODO ask for confirmation?
    //COPY good images to "good directory"
    QDir *dir = new QDir("");
    dir->mkdir("good");
    QStringList goodimglist = this->imagecontroller->getGoodImageList();
    QString sourcepath = dir->absolutePath() + "\\";
    int i=0;
    for(i=0;i<goodimglist.size();i++)
    {
        QFile::copy(sourcepath + goodimglist.at(i), sourcepath + "good/"+goodimglist.at(i));
    }
    //COPY bad images to "bad directory"
    dir->mkdir("bad");
    QStringList badimglist = this->imagecontroller->getBadImageList();
    int j=0;
    for(j=0;j<badimglist.size();j++)
    {
        QFile::copy(sourcepath + badimglist.at(j), sourcepath + "bad/"+badimglist.at(j));
    }

    //notify user of progress
    ReportDialog *report = new ReportDialog(this);
    QString text = "Skopiowano ";
    text.append(QString::number(i));
    text.append(" dobrych obrazków i ");
    text.append(QString::number(j));
    text.append(" złych obrazków.");
    report->setLabel(text);
    report->show();
}

void MainWindow::on_checkBox_bad_clicked()
{
    this->imagecontroller->toggleBad();
}

void MainWindow::on_checkBox_good_clicked()
{
    this->imagecontroller->toggleGood();
}


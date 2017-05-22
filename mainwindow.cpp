#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Setup GraphicsMagick
    //Setup settings
    setupSettings();
    //Setup ImageController
    setupImageController();
    setupProgressBar();
    imagecopier = new ImageCopier();
    Magick::InitializeMagick(NULL);
    this->thumbsProgressDialog = new ThumbsProgressDialog(this);
    connect(this->imagecontroller,
            SIGNAL(thumbsCountUpdated(int, QString)),
            this->thumbsProgressDialog,
            SLOT(on_imagecontroller_thumbsCountUpdated(int, QString))
            );
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

    //Display file name

    ui->filenameLabel->setText(imagecontroller->getCurrentImageName());

    //Display image path
    //ui->directory_label->setText(this->imagecontroller->getCurrentImagePath());

}

void MainWindow::loadNewFolder(QString dir)
{
    //Load current directory
    this->imagecontroller->loadDir(dir);
    //Display working directory in main window
    ui->directory_label->setText(this->imagecontroller->getCurrentDir());
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->setupProgressBar();
    //Create image object
    imageObject = new QImage();
    this->loadImage();
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
    //COPY good images to "good directory", if any are chosen
    int goodCount = this->imagecontroller->doCopyGoodImages();


    //COPY bad images to "bad directory", if any are chosen
    int badCount = this->imagecontroller->doCopyBadImages();


    //TODO refactor into separate function
    //notify user of progress
    ReportDialog *report = new ReportDialog(this);
    QString text = "Skopiowano ";
    text.append(QString::number(goodCount));
    text.append(" dobrych obrazków i ");
    text.append(QString::number(badCount));
    text.append(" złych obrazków.");
    report->setLabel(text);
    report->show();

    //Generate thumbnails
    //notify user of progress
    //Create a dialog to show progress
    //Take into account amount of thumb sizes (*4)
    this->thumbsProgressDialog->setMaximum(this->imagecontroller->getGoodImageList().size()*4);
    this->thumbsProgressDialog->show();
    this->imagecontroller->doMakeThumbsAsync();
    this->imagecontroller->doGenerateImagesWithWatermarkAsync();


}

void MainWindow::on_checkBox_bad_clicked()
{
    this->imagecontroller->toggleBad();
}

void MainWindow::on_checkBox_good_clicked()
{
    this->imagecontroller->toggleGood();
}

void MainWindow::setupSettings()
{
    //Set those values so that settings can be read from the system
    QCoreApplication::setOrganizationName("marcinlawnik");
    QCoreApplication::setOrganizationDomain("lawniczak.me");
    QCoreApplication::setApplicationName("cpp-image-sorter");
    //List of all settings?
    this->settings = new QSettings;
    //Set different values than default for testing
    //this->settings->setValue("dir/nameGood", "yologood");
    //this->settings->setValue("dir/nameBad", "yolobad");
    //this->settings->setValue("dir/nameThumbs", "thumbs");
    //this->settings->setValue("dir/nameWatermark", "watermarked");
    //Set sane default values
    //Rewrite this to a loop TODO
    if(!this->settings->contains("dir/nameGood")) {
        this->settings->setValue("dir/nameGood", "good");
    }
    if(!this->settings->contains("dir/nameBad")) {
        this->settings->setValue("dir/nameBad", "bad");
    }
    if(!this->settings->contains("dir/nameThumbs")) {
        this->settings->setValue("dir/nameThumbs", "thumbs");
    }
    if(!this->settings->contains("dir/nameWatermark")) {
        this->settings->setValue("dir/nameWatermark", "watermarked");
    }

    this->settings->sync();
}


//TODO implement this
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (userReallyWantsToQuit()) {
        this->settings->sync();
        event->accept();
    } else {
        event->ignore();
    }
}

int MainWindow::userReallyWantsToQuit()
{
    const QMessageBox::StandardButton ret =
            QMessageBox::warning(this, QCoreApplication::applicationName(),
                                 tr("Czy na pewno chcesz wyjść?"),
                                 QMessageBox::Close | QMessageBox::Cancel);
    if(ret==QMessageBox::Cancel)
    {
        return false;
    }
    return true;
}



void MainWindow::on_actionZako_cz_triggered()
{
    MainWindow::close();
}

void MainWindow::on_actionUstawienia_triggered()
{
    //Otwórz okno z ustawieniami

    SettingsDialog *settings = new SettingsDialog(this);
    settings->show();
}

void MainWindow::showEvent(QShowEvent *)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

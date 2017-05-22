#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "helpdialog.h"
#include "imagecontroller.h"
#include "imagelistdialog.h"
#include "goodimagelistdialog.h"
#include "imagecopier.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QFileDialog>
#include <QSettings>
#include <QString>
#include <reportdialog.h>
#include <settingsdialog.h>
#include <thumbsprogressdialog.h>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QCloseEvent>
//This below is a clusterfuck to get it to work, should be better
//Paths taken form Magick++.h
//#include <Magick++/lib/Magick++.h>
//#include <Magick++/lib/Magick++/Include.h>
//#include <Magick++/lib/Magick++/Image.h>
//#include <Magick++/lib/Magick++/Pixels.h>
//#include <Magick++/lib/Magick++/STL.h>
#include <Magick++.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionInformacje_o_cpp_image_sorter_triggered();

    void on_button_listaobrazow_clicked();

    void on_nastepny_clicked();

    void on_poprzedni_clicked();

    void on_actionOtw_rz_filder_triggered();

    void on_good_clicked();

    void on_bad_clicked();

    void on_goodimagelist_clicked();

    void on_badimagelist_clicked();

    void on_doSortButton_clicked();

    void on_checkBox_good_clicked();

    void on_checkBox_bad_clicked();

    void on_actionZako_cz_triggered();

    void on_actionUstawienia_triggered();

private:
    Ui::MainWindow *ui;
    HelpDialog *helpdialog;
    ImageController *imagecontroller;
    ImageListDialog *imagelistdialog;
    ImageCopier *imagecopier;
    void setupImageController();
    QPixmap image;
    QImage  *imageObject;
    QGraphicsScene *scene;
    QSettings *settings;
    Magick::Image magickImage;
    void loadImage();
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);
    void setupProgressBar();
    void updateProgressBar();
    void setupSettings();
    void loadNewFolder(QString dir);
    void updateCheckboxes();
    ThumbsProgressDialog *thumbsProgressDialog;
    int userReallyWantsToQuit();
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

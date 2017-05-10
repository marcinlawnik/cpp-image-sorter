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
#include <reportdialog.h>


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
    void loadImage();
    void showEvent(QShowEvent *);
    void resizeEvent(QResizeEvent *);
    void setupProgressBar();
    void updateProgressBar();
    void loadNewFolder(QString dir);
    void updateCheckboxes();
};

#endif // MAINWINDOW_H

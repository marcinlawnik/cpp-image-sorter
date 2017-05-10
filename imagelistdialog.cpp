#include "imagelistdialog.h"
#include "ui_imagelistdialog.h"

ImageListDialog::ImageListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageListDialog)
{
    ui->setupUi(this);
}

ImageListDialog::~ImageListDialog()
{
    delete ui;
}

void ImageListDialog::on_buttonBox_accepted()
{
    ImageListDialog::close();
}

void ImageListDialog::setFileList(QString list)
{
    ui->filelist->setText(list);
}

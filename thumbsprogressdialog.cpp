#include "thumbsprogressdialog.h"
#include "ui_thumbsprogressdialog.h"

ThumbsProgressDialog::ThumbsProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ThumbsProgressDialog)
{
    ui->setupUi(this);
    //The ok button starts locked, waiting for thumbs to generate
    ui->buttonBox->setEnabled(false);

}

ThumbsProgressDialog::~ThumbsProgressDialog()
{
    delete ui;
}

void ThumbsProgressDialog::setMaximum(int size)
{
    ui->progressBar->setMaximum(size);
}

void ThumbsProgressDialog::setProgress(int item, QString file)
{
    ui->progressBar->setValue(item);
    ui->nazwa_pliku->setText(file);
    if (ui->progressBar->value() == ui->progressBar->maximum())
    {
        ui->buttonBox->setEnabled(true);
    }
}

void ThumbsProgressDialog::on_buttonBox_accepted()
{
    this->close();
}

void ThumbsProgressDialog::on_imagecontroller_thumbsCountUpdated(int count, QString file)
{
    this->setProgress(count, file);
}

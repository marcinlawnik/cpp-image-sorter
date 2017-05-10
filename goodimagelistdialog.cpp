#include "goodimagelistdialog.h"
#include "ui_goodimagelistdialog.h"

GoodImageListDialog::GoodImageListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GoodImageListDialog)
{
    ui->setupUi(this);
}

GoodImageListDialog::~GoodImageListDialog()
{
    delete ui;
}

void GoodImageListDialog::on_buttonBox_accepted()
{
    this->close();
}

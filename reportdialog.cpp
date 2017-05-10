#include "reportdialog.h"
#include "ui_reportdialog.h"

ReportDialog::ReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReportDialog)
{
    ui->setupUi(this);
}

ReportDialog::~ReportDialog()
{
    delete ui;
}

void ReportDialog::on_buttonBox_accepted()
{
    this->close();
}

void ReportDialog::setLabel(QString label)
{
    ui->label->setText(label);
}


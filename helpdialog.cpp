#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <sstream>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    fillInformation();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_buttonBox_accepted()
{
    HelpDialog::close();
}

void HelpDialog::fillInformation()
{
    QString version_text = "Wersja Qt użyta do kompilacji: ";
    version_text.append(QT_VERSION_STR);
    ui->qt_version_label->setText(version_text);
}

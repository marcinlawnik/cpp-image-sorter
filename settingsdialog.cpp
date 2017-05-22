#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->settings = new QSettings;
}

void SettingsDialog::loadSettings()
{
    ui->goodNameTextEdit->document()->setPlainText(this->settings->value("dir/nameGood", "yoloo").toString());
    ui->badNameTextEdit->document()->setPlainText(this->settings->value("dir/nameGood", "tollodasdsa").toString());
    ui->watermarkTextEdit->document()->setPlainText("watermark.png");
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{

}

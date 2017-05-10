#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class HelpDialog;
}

class HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = 0);
    ~HelpDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::HelpDialog *ui;
    void fillInformation();
};

#endif // HELPDIALOG_H

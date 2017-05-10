#ifndef REPORTDIALOG_H
#define REPORTDIALOG_H

#include <QDialog>

namespace Ui {
class ReportDialog;
}

class ReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReportDialog(QWidget *parent = 0);
    ~ReportDialog();
    void setLabel(QString label);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ReportDialog *ui;
};

#endif // REPORTDIALOG_H

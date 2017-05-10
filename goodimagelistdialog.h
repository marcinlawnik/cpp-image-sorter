#ifndef GOODIMAGELISTDIALOG_H
#define GOODIMAGELISTDIALOG_H

#include <QDialog>

namespace Ui {
class GoodImageListDialog;
}

class GoodImageListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoodImageListDialog(QWidget *parent = 0);
    ~GoodImageListDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::GoodImageListDialog *ui;
};

#endif // GOODIMAGELISTDIALOG_H

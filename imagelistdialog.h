#ifndef IMAGELISTDIALOG_H
#define IMAGELISTDIALOG_H

#include <QDialog>

namespace Ui {
class ImageListDialog;
}

class ImageListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageListDialog(QWidget *parent = 0);
    void setFileList(QString list);
    ~ImageListDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ImageListDialog *ui;
};

#endif // IMAGELISTDIALOG_H

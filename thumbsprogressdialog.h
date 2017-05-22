#ifndef THUMBSPROGRESSDIALOG_H
#define THUMBSPROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ThumbsProgressDialog;
}

class ThumbsProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ThumbsProgressDialog(QWidget *parent = 0);
    ~ThumbsProgressDialog();
    void setMaximum(int size);
    void setProgress(int item, QString file);

private slots:
    void on_buttonBox_accepted();
public slots:
    void on_imagecontroller_thumbsCountUpdated(int count, QString file);

private:
    Ui::ThumbsProgressDialog *ui;
};

#endif // THUMBSPROGRESSDIALOG_H

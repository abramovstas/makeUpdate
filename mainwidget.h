#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPointer>

#include "job.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(Job &job, QWidget *parent = nullptr);
    ~MainWidget();

private slots:

    void on_btn_setDir_clicked();

    void on_btn_setFile_clicked();

private:
    Ui::MainWidget *ui;
    QPointer<Job> m_job;
    QString m_directory = "";
    QString m_file = "";
};

#endif // MAINWIDGET_H

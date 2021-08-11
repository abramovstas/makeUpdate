#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QFileDialog>
#include <QStandardPaths>

MainWidget::MainWidget(Job &job, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
  , m_job(&job)
{
    ui->setupUi(this);

    ui->le_inputDirectory->setText(job.directory());
    ui->le_outputFile->setText(job.file());

    connect(ui->btn_exit, &QPushButton::clicked, this, &MainWidget::close);
    connect(m_job.data(), &Job::finished, this, &MainWidget::close, Qt::QueuedConnection);
    connect(ui->btn_make, &QPushButton::clicked, m_job.data(), &Job::start);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_btn_setDir_clicked()
{
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QString(),
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    if (!directory.isEmpty())
    {
        m_job->setDirectory(directory);
        ui->le_inputDirectory->setText(directory);
    }
}

void MainWidget::on_btn_setFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("XML files (*.xml)"));
    if (!fileName.isEmpty())
    {
        m_job->setFile(fileName);
        ui->le_outputFile->setText(fileName);
    }
}

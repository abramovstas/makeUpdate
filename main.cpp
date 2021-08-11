#include <QApplication>
#include <QCommandLineParser>
#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QDir>
#include <job.h>

#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QCommandLineParser parser;
    parser.setApplicationDescription(
                QObject::tr(
                    "Tool used to generate xml file listing files from specified directory with checksums"));
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOption({{"c", "cli"}, QObject::tr("Use CLI only")});
    parser.addOption({{"d", "directory"}, QObject::tr("Input directory"), QObject::tr("path")});
    parser.addOption({{"f", "file"}, QObject::tr("Output filename"), QObject::tr("name")});

    QStringList opts;
    for (int i = 0; i < argc; ++i)
        opts << QString(argv[i]);
    parser.parse(opts);

    Job m_job;

    if(parser.isSet("directory"))
        m_job.setDirectory(QDir(parser.value("directory")).absolutePath());
    if(parser.isSet("file"))
        m_job.setFile(parser.value("file"));

    if (parser.isSet("cli") or parser.isSet("help"))
    {
        QCoreApplication app(argc, argv);
        parser.process(app);
        qDebug() << "directory is " << m_job.directory() << " file is " << m_job.file();
        m_job.start();
        QObject::connect(&m_job, &Job::finished, &app, &QCoreApplication::quit, Qt::QueuedConnection);
        exit(app.exec());
    }
    else
    {
        QApplication app(argc, argv);
        MainWidget w(m_job);
        w.show();
        parser.process(app);
        exit(app.exec());
    }

}

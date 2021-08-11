#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QString>
#include <QList>
#include <QDir>

struct FileInformation
{
    QString fileName;
    QString fileSize;
    QString fileMd5;
};

class Job : public QObject
{
    Q_OBJECT
public:
    explicit Job(QObject *parent = nullptr);

    void start();

    QString directory() const;
    void setDirectory(const QString &directory);

    QString file() const;
    void setFile(const QString &file);

signals:
    void finished(int code = 0);

private:
    void fillFileList();
    void writeFilesToXml();
    QString sumFileMd5(const QString &fileName);

    QString m_directory = QDir::currentPath();
    QString m_file = "update.xml";
    QList<FileInformation> m_informationList;
};

#endif // JOB_H

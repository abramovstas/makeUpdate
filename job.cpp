#include "job.h"

#include <QCryptographicHash>
#include <QXmlStreamWriter>
#include <QDirIterator>
#include <QDebug>

Job::Job(QObject *parent)
    :QObject(parent)
{
}

void Job::start()
{
    fillFileList();
    writeFilesToXml();
}

void Job::fillFileList()
{
    m_informationList.clear();
    QDirIterator it(m_directory, QStringList() << "*.*", QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        FileInformation fileInformation;
        fileInformation.fileName = it.next();
        fileInformation.fileSize = QString::number(it.fileInfo().size());
        fileInformation.fileMd5 = sumFileMd5(fileInformation.fileName);
        m_informationList.append(fileInformation);
        qDebug() <<"file : " << fileInformation.fileName;
    }
}

void Job::writeFilesToXml()
{
    QFile file(m_file);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
    {
        qDebug() << "Error open file " + m_file;
        return;
    }

    if (!m_informationList.isEmpty())
    {
        QXmlStreamWriter writer;
        writer.setDevice(&file);
        writer.setAutoFormatting(true);

        writer.writeStartDocument();
        writer.writeStartElement("update");
        writer.writeTextElement("path", "files");
        writer.writeStartElement("files");
        foreach (auto info, m_informationList)
            if (QFileInfo(info.fileName).path() != m_directory)
                writer.writeTextElement("filename", QFileInfo(info.fileName).path().remove(m_directory).remove(0,1) + "/" + QFileInfo(info.fileName).fileName());
            else writer.writeTextElement("filename", QFileInfo(info.fileName).fileName());
        writer.writeEndElement();
        writer.writeStartElement("items");
        foreach (auto info, m_informationList)
        {
            writer.writeStartElement("item");
            if (QFileInfo(info.fileName).path() != m_directory)
                writer.writeTextElement("filename", QFileInfo(info.fileName).path().remove(m_directory).remove(0,1) + "/" + QFileInfo(info.fileName).fileName());
            else writer.writeTextElement("filename", QFileInfo(info.fileName).fileName());
            writer.writeTextElement("size", info.fileSize);
            writer.writeTextElement("md5", info.fileMd5);
            writer.writeEndElement();
        }
        writer.writeEndElement();
        writer.writeStartElement("undels");
        writer.writeTextElement("undel", "unins000.exe");
        writer.writeEndElement();
        writer.writeEndElement();
        writer.writeEndDocument();
    }
    file.close();
    emit finished();
}

QString Job::directory() const
{
    return m_directory;
}

void Job::setDirectory(const QString &directory)
{
    m_directory = directory;
}

QString Job::sumFileMd5(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "read file failed!";
        return QString();
    }

    QByteArray b = file.readAll();
    file.close();
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(b);
    QByteArray result = hash.result();
    return QString(result.toHex());
}

QString Job::file() const
{
    return m_file;
}

void Job::setFile(const QString &file)
{
    m_file = file;
}

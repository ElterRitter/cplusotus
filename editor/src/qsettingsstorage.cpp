#include "qsettingsstorage.h"


#include <QString>
#include <QSettings>
#include <QDebug>

namespace otuseditor {

QSettingsStorage::QSettingsStorage(const std::string &filePathName)
{
    QString fileName = QString::fromStdString(filePathName);
    m_settings = std::make_shared<QSettings>(fileName, QSettings::IniFormat, nullptr);

    auto keys = m_settings->allKeys();
    qDebug() << keys;
}

int QSettingsStorage::value(const std::string &key, const int &defaultValue)
{
    if(m_settings->status() != QSettings::NoError)
        return defaultValue;

    return m_settings->value(QString::fromStdString(key), defaultValue).toInt();
}

double QSettingsStorage::value(const std::string &key, const double &defaultValue)
{
    if(m_settings->status() != QSettings::NoError)
        return defaultValue;

    return m_settings->value(QString::fromStdString(key), defaultValue).toDouble();
}

std::string QSettingsStorage::value(const std::string &key, std::string &defaultValue)
{
    if(m_settings->status() != QSettings::NoError)
        return defaultValue;

    auto val = m_settings->value(QString::fromStdString(key), QString::fromStdString(defaultValue)).toString();
    return val.toStdString();
}

void QSettingsStorage::setValue(const std::string &key, const int &value)
{
    if(m_settings->status() != QSettings::NoError)
        return;

    m_settings->setValue(QString::fromStdString(key), value);
}

void QSettingsStorage::setValue(const std::string &key, const double &value)
{
    if(m_settings->status() != QSettings::NoError)
        return;

    m_settings->setValue(QString::fromStdString(key), value);
}

void QSettingsStorage::setValue(const std::string &key, const std::string &value)
{
    if(m_settings->status() != QSettings::NoError)
        return;

    m_settings->setValue(QString::fromStdString(key), QString::fromStdString(value));
}

void QSettingsStorage::beginGroup(const std::string &groupName)
{
    if(m_settings->status() == QSettings::NoError)
        m_settings->beginGroup(QString::fromStdString(groupName));
}

void QSettingsStorage::endGroup()
{
    if(m_settings->status() == QSettings::NoError)
        m_settings->endGroup();
}

ISettingsStorage::stringlist QSettingsStorage::values()
{
    ISettingsStorage::stringlist ret;
    auto keys = m_settings->childKeys();
    if(keys.empty())
        keys = m_settings->childGroups();

    for(const auto &key : qAsConst(keys))
    {
        ret.emplace_back(key.toStdString());
    }

    return ret;
}

std::string QSettingsStorage::rawStoragePath() const
{
    auto ret = m_settings->fileName();
    return ret.toStdString();
}

}

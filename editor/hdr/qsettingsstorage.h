#pragma once

#include "isettingsstorage.h"

#include <string>

class QSettings;

namespace otuseditor {

/*!
 * \brief Класс QSettingsStorage является реализацией интерфейса ISettingsStorage через QSettings
 */
class QSettingsStorage : public ISettingsStorage
{
public:
    QSettingsStorage(const std::string &filePathName);

    // ISettingsStorage members
    int value(const std::string & key, const int &defaultValue) override final;
    double value(const std::string & key, const double &defaultValue) override final;
    std::string value(const std::string & key, std::string &defaultValue) override final;

    void setValue(const std::string & key, const int &value) override final;
    void setValue(const std::string & key, const double &value) override final;
    void setValue(const std::string & key, const std::string &value) override final;

    void beginGroup(const std::string &groupName) override final;
    void endGroup() override final;
    ISettingsStorage::stringlist keys() override final;
    std::string rawStoragePath() const override final;

private:
    std::shared_ptr<QSettings> m_settings;
};

};

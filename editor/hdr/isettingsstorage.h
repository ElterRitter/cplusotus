#pragma once

#include <memory>
#include <string>
#include <list>

class ISettingsStorage
{
public:
    using Ptr = std::unique_ptr<ISettingsStorage>;
    using SPtr = std::shared_ptr<ISettingsStorage>;
    using WPtr = std::weak_ptr<ISettingsStorage>;
    using stringlist = std::list<std::string>;

    ISettingsStorage() = default;
    virtual ~ISettingsStorage() = default;

    virtual int value(const std::string & key, const int &defaultValue) = 0;
    virtual double value(const std::string & key, const double &defaultValue) = 0;
    virtual std::string value(const std::string & key, std::string &defaultValue) = 0;

    virtual void setValue(const std::string & key, const int &value) = 0;
    virtual void setValue(const std::string & key, const double &value) = 0;
    virtual void setValue(const std::string & key, const std::string &value) = 0;

    virtual void beginGroup(const std::string &groupName) = 0;
    virtual void endGroup() = 0;
    virtual stringlist values() = 0;
    virtual std::string rawStoragePath() const = 0;
};

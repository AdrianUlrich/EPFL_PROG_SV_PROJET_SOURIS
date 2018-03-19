
/*
 * prjsv 2018
 * 2014-2018
 * Marco Antognini, Antoine Madrona
 */

#include <Application.hpp>
#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
#include <Utility/Constants.hpp>

#include <algorithm>
#include <cassert>

namespace // anonymous
{

Application* currentApp = nullptr; ///< Current application

std::string applicationDirectory(int argc, char const** argv)
{
    assert(argc >= 1);

    auto dir = std::string(argv[0]);

    auto lastSlashPos = dir.rfind('/');
    if (lastSlashPos == std::string::npos) {
        dir = "./";
    } else {
        dir = dir.substr(0, lastSlashPos + 1);
    }

    return dir;
}

std::string configFileRelativePath(int argc, char const** argv)
{
    if (argc >= 2) {
        return RES_LOCATION + argv[1];
    } else {
			return RES_LOCATION + DEFAULT_CFG;
    }
}

} // anonymous

Application::Application(int argc, char const** argv)
: mAppDirectory(applicationDirectory(argc, argv))
, mCfgFile(configFileRelativePath(argc, argv))
//, mJSONRead(mAppDirectory + mCfgFile)
, mConfig(new Config(mAppDirectory + mCfgFile))
{
    // Set global singleton
    assert(currentApp == nullptr);
    currentApp = this;

    std::cerr << "Using " << (mAppDirectory + mCfgFile) << " for configuration.\n";
}

Application::~Application()
{
	delete mConfig;

    // Reset the global pointer
    currentApp = nullptr;
}

Config& Application::getConfig()
{
    return *mConfig;
}

Config const& Application::getConfig() const
{
    return *mConfig;
}

std::string Application::getResPath() const
{
    return mAppDirectory + RES_LOCATION;
}

Application& getApp()
{
    assert(currentApp != nullptr);

    return *currentApp;
}

Config& getAppConfig()
{
    return getApp().getConfig();
}

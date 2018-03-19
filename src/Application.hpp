/*
 * prjsv 2018
 * 2014-2018
 * Marco Antognini, Antoine Madrona
 */

#ifndef INFOSV_APPLICATION_HPP
#define INFOSV_APPLICATION_HPP

#include <JSON/JSON.hpp>
#include "Config.hpp"
#include "Types.hpp"
#include <Utility/Vec2d.hpp>

#include <SFML/Graphics.hpp>

#include <iostream>
#include <list>
#include <map>
#include <stdexcept>
#include <string>

/*!
 * @class Application
 *
 * @brief Abstract class managing the core of the program
 *
 * Subclass can optionally re-implement onEvent(), onUpdate() and onDraw().
 *
 *
 * Note that `simulation` and `world` usually mean the same thing here.
 */
class Application
{
public:
    /*!
     * @brief Constructor
     *
     * @param argc argument count
     * @param argv launch arguments
     */
    Application(int argc, char const** argv);

    /// Forbid copy
    Application(Application const&) = delete;
    Application& operator=(Application const&) = delete;

    /*!
     * @brief Destructor
     */
    virtual ~Application();

    /*!
     * @brief Get access to the application's configuration
     *
     * @return the app's config
     */
    Config& getConfig();
    Config const& getConfig() const;

    /*!
     * @brief Get the path to the resource folder
     */
    std::string getResPath() const;
	
protected:
    // The order is important since some fields need other to be initialised
    std::string const mAppDirectory; ///< Path to the executable's directory
    std::string const mCfgFile;      ///< Relative path to the CFG
//    j::Value          mJSONRead;       ///< Application configuration
    Config*          mConfig;       ///< Application configuration
};

/*!
 * @brief Get the current instance of Application
 *
 * @return a reference to the current instance of Application
 */
Application& getApp();

/*!
 * @brief Get the config of the current application
 *
 * Shorthand for getApp().getConfig()
 *
 * @return the app's config
 */
Config& getAppConfig();

/// Define a few macros

/*!
 * @brief Implement the main() function with a given subclass of Application
 *
 * @param APPLICATION_CLASS a class name (it must be a subclass of Application)
 */
#define IMPLEMENT_MAIN(APPLICATION_CLASS)                   \
    int main(int argc, char const** argv)                   \
    try {                                                   \
        APPLICATION_CLASS app(argc, argv);                  \
        app.run();                                          \
        return 0;                                           \
    } catch (std::exception const& e) {                     \
        std::cerr << "FATAL ERROR: " << e.what() << "\n";   \
        return 1;                                           \
    }

#define INIT_DEFAULT_APP(argc, argv) Application app((argc), (argv));


#endif // INFOSV_APPLICATION_HPP

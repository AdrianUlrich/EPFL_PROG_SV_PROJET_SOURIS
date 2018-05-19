/*
 * prjsv 2016
 * 2013, 2014, 2016
 * Marco Antognini
 */

#ifndef INFOSV_APPLICATION_HPP
#define INFOSV_APPLICATION_HPP

#include <Env/Lab.hpp>
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
#include <vector>

/*!
 * @class Application
 *
 * @brief Abstract class managing the core of the program
 *
 * Subclass can optionally re-implement onEvent(), onUpdate() and onDraw().
 *
 * The Lab class handles the drawing and update of the system.
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
     * @brief Run the application
     *
     * This function is the main loop.
     *
     * @note Don't forget to call init() before run() !
     */
    void run();

    /*!
     * @brief Get access to the execution environment of the application (the env)
     *
     * @note This breaks the encapsulation but simplify everything!
     *
     * @return the app's env
     */
    Lab& getLab();
    Lab const& getLab() const;
	View getCurrentView() const;

    /*!
     * @brief Get the animal tracker helper
     *
     * @return the app's animal tracker
     */
    // AnimalTracker& getAnimalTracker();
    // AnimalTracker const& getAnimalTracker() const;

    /*!
     * @brief Get access to the application's configuration
     *
     * @return the app's config
     */
    Config& getConfig();
    Config const& getConfig() const;

    /*!
     * @brief Get the app's font
     *
     * @return a font
     */
    sf::Font const& getFont() const;

    /*!
     * @brief Get a texture
     *
     * The texture is loaded on the fly from the 'res' folder and is owned
     * by this application.
     *
     * The returned texture is read-write capable but in most case a read-only
     * access should be enough.
     *
     * The application guarantees that the texture is not moved in memory and
     * is not destroyed until the destruction of the application. This ensures
     * that the returned reference will be valid until the end of the application
     * and therefore can be given to a sprite.
     *
     * If the corresponding texture couldn't be loaded a default white texture is
     * returned and an error message is displayed on sf::Err by SFML.
     *
     * @param name name of the texture
     * @return a reference to the corresponding texture
     */
    sf::Texture& getTexture(std::string const& name);

    /*!
     * @brief Get the path to the resource folder
     */
    std::string getResPath() const;

    /**
     *  @brief Read the lab size from the config manager
     *
     *  @return the world size
     */
    Vec2d getLabSize() const;

/**
     *  @brief Read the size of the simulated organ
	 * from the config manager
     *
     *  @return the world size
     */
    Vec2d getOrganSize() const;
	
    /**
     *  @brief Compute the centre of the world area (in local coordinates)
     *
     *  @return the centre of the app
     */
    Vec2d getCentre() const;

    /*!
     * @brief Get the cursor position in the view coordinates (i.e. pixel coordinates)
     *
     * @return The cursor position converted in the view coordinates
     */
    Vec2d getCursorPositionInView() const;

	
	void switchToView(View);

	bool isConcentrationOn() const
		{
			return mCurrentView == CONCENTRATION;
		}
	
	
protected:
    /*!
     *  @brief Called once before starting the main loop
     *
     *  By default nothing is done.
     */
    virtual void onRun();

    /**
     *  @brief Called when the simulation is (re)started, but not when importing data
     *
     *  By default nothing is done.
     */
    virtual void onSimulationStart();

    /*!
     * @brief Subclass can override this method to handle events
     *
     * The default implementation does nothing.
     *
     * @param event an event
     * @param window the window that emitted the event
     */
    virtual void onEvent(sf::Event event, sf::RenderWindow& window);

    /*!
     * @brief Subclass can override this method to update their data
     *
     * The default implementation does nothing. However, the env is always updated first.
     *
     * @param dt elapsed time
     */
    virtual void onUpdate(sf::Time dt);

    /*!
     * @brief Subclass can override this method to draw their data
     *
     * The default implementation does nothing. However, the env is always displayed first.
     *
     * @param target a render target
     */
    virtual void onDraw(sf::RenderTarget& target);
/*!
     * @brief Subclass can override this method to change the policy for
	 * background handling
	 */
	void chooseBackground();


protected:
    /*!
     * @brief Create the window
     */
    void createWindow(Vec2d const& size);

    /*!
     *  @brief Create the simulation and stats views
     */
    void createViews();

    /*!
     * @brief Do the logic for a given event
     *
     * @param event Event to handle
     * @param window the window that emitted the event
     */
    void handleEvent(sf::Event event, sf::RenderWindow& window);

    /*!
     *  @brief Render the GUI, Simulation and Stats
     *
     *  @param simulationBackground Background of the simulation frame
     *  @param statsBackground      Background of the stats frame
     */
    void render(sf::Drawable const& simulationBackground, sf::Drawable const& statsBackground);

    /*!
     * @brief Toggle pause
     */
    void togglePause();

    /*!
     * @brief Save the current configuration
     */
    void saveConfig() const;

    /*!
     * @brief Zoom the simulation view on the given pixel
     *
     * @note the view is centered on the selected entity if on is
     * selected, or on the cursor if none is currently selected.
     */
    void zoomViewAt(sf::Vector2i const& /*pixel*/, float zoomFactor);

    /*!
     * @brief Drag the view by the given offset (i.e. src to dest)
     */
    void dragView(sf::Vector2i const& srcPixel, sf::Vector2i const& destPixel);

    /*!
     * @brief Center the simulation view on the tracked bee,
     * if selection is active.
     */
    void updateSimulationView();

   /*!
     * @brief toggle debug mode
     */
	void switchDebug();

    void drawOnHelp(sf::RenderWindow& window, bool micro) const;

    
	
protected:
 /*!
     * @brief toggle concentration view mode
     */
	void toggleConcentrationView();
	
    // The order is important since some fields need other to be initialised
    std::string const mAppDirectory; ///< Path to the executable's directory
    std::string const mCfgFile;      ///< Relative path to the CFG
//    j::Value          mJSONRead;       ///< Application configuration
    Config*          mConfig;       ///< Application configuration

    sf::View mStatsView;             ///< View for the stats area
    int      mCurrentGraphId;        ///< Current graph ID


    sf::View mHelpView;         ///< View for commands help

    Lab* mLab;                       ///< Simulated environment

    sf::Font mFont;                  ///< A font

    sf::RenderWindow mRenderWindow;  ///< SFML window / render target
    sf::View mSimulationView;        ///< View for simulation area
	sf::View mLabView;        ///< View for simulation area
	sf::View mOrganView;        ///< View for simulation area

    using TexturePool = std::map<std::string, sf::Texture*>;
    TexturePool mTextures;           ///< Pool of textures
    sf::Texture mDefaultTexture;     ///< Default, white texture
    // mDefaultTexture is used when a texture in the pool is not available

    bool         mPaused;            ///< Tells if the application is in pause or not
    bool         mIsResetting;       ///< Is true for one main loop iteration when resetting.
	bool         mIsSwitchingView;
                                     ///  This is useful to pause the clock while generating
                                     ///  a new world. Without this, a huge dt would result from
                                     ///  rebuilding the world.
    bool         mIsDragging;        ///< Tells whether or not the user is dragging the view
    sf::Vector2i mLastCursorPosition;///< For handling dragging logic
//    AnimalTracker   mAnimalTracker;        ///< Helper to keep track of an animal (optional)

	sf::RectangleShape mSimulationBackground;
	sf::RectangleShape mLabBackground;
	sf::RectangleShape mOrganBackground;

	// Views

	View mCurrentView;
};

/*!
 * @brief Get the current instance of Application
 *
 * @return a reference to the current instance of Application
 */
Application& getApp();

/*!
 * @brief Get the environment (the env) of the current application
 *
 * Shorthand for getApp().getLab()
 *
 * @see Application::getLab() comment about encapsulation
 *
 * @return the app's env.
 */
Lab& getAppEnv();

/*!
 * @brief Get the bee tracker helper for the current application
 *
 * @return the app's bee tracker
 */
//AnimalTracker& getAppAnimalTracker();

/*!
 * @brief Get the config of the current application
 *
 * Shorthand for getApp().getConfig()
 *
 * @return the app's config
 */
Config& getAppConfig();

/*!
 * @brief Get the app's font
 *
 * Shorthand for getApp().getFont()
 *
 * @return a font
 */
sf::Font const& getAppFont();

/*!
 * @brief Get a texture
 *
 * Shorthand for getApp().getTexture(name)
 *
 * @param name name of the texture
 * @return a reference to the texture
 *
 * @see Application::getTexture
 */
sf::Texture& getAppTexture(std::string const& name);

/*!
 * @brief Determine if debug mode is active or not
 *
 * Shorthand for getAppConfig().getBool(DEBUG_MODE)
 *
 * @return true if cfg specify DEBUG=TRUE
 */
bool isDebugOn();
bool isOrganViewOn();

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

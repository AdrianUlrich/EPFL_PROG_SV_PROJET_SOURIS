
/*
 * prjsv 2016
 * 2013, 2014, 2016
 * Marco Antognini
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

/*
 * get*Size and get*Position: see createViews for graphical layout
 */

Vec2d getWindowSize()
{
    auto width = getAppConfig().window_simulation_width + getAppConfig().window_stats_width;
    auto height = getAppConfig().window_simulation_height;
    return { width, height };
}

Vec2d getSimulationSize()
{
    auto width = getAppConfig().window_simulation_width;
	auto height = getAppConfig().window_simulation_height;
    return { width, height };
}

Vec2d getSimulationPosition()
{
    return { 0, 0 };
}

Vec2d getStatsSize()
{
    auto width = getAppConfig().window_stats_width;
	auto height = getAppConfig().window_simulation_height/2;
    return { width, height };
}

Vec2d getStatsPosition()
{
    return { getAppConfig().window_simulation_width, 0 };
}

Vec2d getHelpSize()
{
    auto width = getAppConfig().window_stats_width;
    auto height = getAppConfig().window_simulation_height/2;
    return { width, height };
}

Vec2d getHelpPosition()
{
    return { getAppConfig().window_simulation_width, getAppConfig().window_simulation_height/2 };
}
/*!
 * @brief Create a view with the given properties
 *
 * @param viewSize size of the OpenGL rendering space (might be bigger/smaller than allocation)
 * @param position top-left corner of the view in window coordinates
 * @param allocation size of the view in window
 * @param windowSize size of the window
 */
sf::View setupView(Vec2d const& viewSize,
                   Vec2d const& position, Vec2d const& allocation,
                   sf::Vector2u const& windowSize)
{
    sf::View view;
    view.reset({ { 0, 0 }, viewSize });
    view.setViewport({ static_cast<float>(position.x / windowSize.x),
                       static_cast<float>(position.y / windowSize.y),
                       static_cast<float>(allocation.x / windowSize.x),
                       static_cast<float>(allocation.y / windowSize.y) });

    return view;
}

} // anonymous

Application::Application(int argc, char const** argv)
: mAppDirectory(applicationDirectory(argc, argv))
, mCfgFile(configFileRelativePath(argc, argv))
//, mJSONRead(mAppDirectory + mCfgFile)
, mConfig(new Config(mAppDirectory + mCfgFile))
, mLab(nullptr)
, mPaused(false)
, mIsResetting(false)
, mIsSwitchingView(false)
, mIsDragging(false)
, mCurrentView(LAB)
{
    // Set global singleton
    assert(currentApp == nullptr);
    currentApp = this;

    std::cerr << "Using " << (mAppDirectory + mCfgFile) << " for configuration.\n";

    // Load the font
    if (!mFont.loadFromFile(mAppDirectory + FONT_LOCATION)) {
        std::cerr << "Couldn't load " << FONT_LOCATION << std::endl;
    }
	// prepare simulation background
	mLabBackground = sf::RectangleShape();
    mLabBackground.setSize(getLabSize());
    //simulationBackground.setFillColor(sf::Color::Black);
	mLabBackground.setOutlineColor(sf::Color::Black);
    mLabBackground.setOutlineThickness(5);
    mLabBackground.setTexture(&getAppTexture(getAppConfig().simulation_lab_texture));


	mOrganBackground = sf::RectangleShape();
    mOrganBackground.setSize(getOrganSize());
    //simulationBackground.setFillColor(sf::Color::Black);
	//mOrganBackground.setOutlineColor(sf::Color::Black);
    mOrganBackground.setOutlineThickness(5);
    mOrganBackground.setTexture(&getAppTexture(getAppConfig().simulation_lab_texture));
	mOrganBackground.setFillColor(sf::Color::Black);
	
	mSimulationBackground = mLabBackground;
}

Application::~Application()
{
    // Destroy lab and stats, in reverse order
    delete mLab;
	delete mConfig;

    // Release textures
    for (auto& kv : mTextures) {
        delete kv.second;
        kv.second = nullptr;
    }
    mTextures.clear();

    // Reset the global pointer
    currentApp = nullptr;
}

void Application::run()
{
    // Load lab and stats
    mLab   = new Lab;

    // Set up subclasses
    onRun();
    onSimulationStart();

    // Create the SFML window
    createWindow(getWindowSize());

    // Views for rendering regions
    createViews();

    // Create the Stats background (grey board)
    auto statsBackground = sf::RectangleShape();
    statsBackground.setSize(getStatsSize());
    statsBackground.setFillColor(sf::Color(128, 128, 128));

    // Use a clock to track time
    sf::Clock clk;

    // FPS counter
    sf::Clock fpsClk;
    int frameCount = 0;
	int nbCycles = 10;
    // Main loop
    while (mRenderWindow.isOpen()) {
        // Handle events
        sf::Event event;
        while (mRenderWindow.pollEvent(event)) {
            handleEvent(event, mRenderWindow);
        }

        // Update logics
		
        float timeFactor = getAppConfig().simulation_time_factor;
        auto elapsedTime = clk.restart() * timeFactor; // Always reset the clock!

        if (!mPaused && !mIsResetting) {
            // Update simulation with the elapsed time, possibly
            // by calling update(dt) several time to avoid update
            // with high delta time.
            //
            // An alternative implementation could be based on fixed
            // timesteps.
            sf::Time maxDt = getAppConfig().simulation_time_max_dt;
            while (elapsedTime > sf::Time::Zero) {
                auto dt = std::min(elapsedTime, maxDt);
                elapsedTime -= dt;
				getLab().update(dt);
                onUpdate(dt);
				--nbCycles;

            }
        }

		// fixed step simulation for the organ
		// no need to refresh the view after each update
		if (isOrganViewOn()){
			if (nbCycles < 0 || mIsSwitchingView){
				getLab().updateTrackedAnimal();
				render(mSimulationBackground, statsBackground);
				nbCycles=10;
				mIsSwitchingView = false;
				 ++frameCount;
			}
		}
		
		
		else
		{
			
				// Render everything
			render(mSimulationBackground, statsBackground);
			 ++frameCount;
		}
		
        // In case we were resetting the simulation
        mIsResetting = false;

        // FPS computation
        //++frameCount;
        if (fpsClk.getElapsedTime() > sf::seconds(2)) {
            auto dt = fpsClk.restart().asSeconds();

            auto fps = frameCount / dt;
            std::cout << "FPS: " << fps << "\r" << std::flush;

            frameCount = 0;
        }
    }
}

Lab& Application::getLab()
{
    return *mLab;
}

Lab const& Application::getLab() const
{
    return *mLab;
}

// AnimalTracker& Application::getAnimalTracker()
// {
//     return mAnimalTracker;
// }

// AnimalTracker const& Application::getAnimalTracker() const
// {
//     return mAnimalTracker;
// }

Config& Application::getConfig()
{
    return *mConfig;
}

Config const& Application::getConfig() const
{
    return *mConfig;
}

sf::Font const& Application::getFont() const
{
    return mFont;
}

sf::Texture& Application::getTexture(std::string const& name)
{
    auto const it = mTextures.find(name);
    if (it != mTextures.end())
        return *it->second;
    else {
        // The texture is not yet in memory so we load it now
        sf::Texture* newTexture = new sf::Texture;
        if (newTexture->loadFromFile(getResPath() + name)) {
            // The texture was correctly loaded so we save it
			newTexture->setRepeated(true); 
            mTextures[name] = newTexture;
            // And return the texture
            return *newTexture;
        } else {
            // The file was not loaded correctly so we clean up the mess
            delete newTexture;
            newTexture = nullptr;
            // And return the default texture
            return mDefaultTexture;
        }
    }
}


std::string Application::getResPath() const
{
    return mAppDirectory + RES_LOCATION;
}

Vec2d Application::getLabSize() const
{
    // Not the same as getSimulationSize!
	// TODO: improve
	double size(getAppConfig().simulation_lab_size);
	return { size, size };
}

Vec2d Application::getOrganSize() const
{
    // Not the same as getSimulationSize!
	// TODO: improve
	double size(getAppConfig().simulation_organ_size);
	return { size, size };
}

Vec2d Application::getCentre() const
{
	// TODO : add organ
    return getLabSize() / 2.0;
}

void Application::onRun()
{
    // By default nothing is done here
	chooseBackground();
}

void Application::chooseBackground()
{

	if (mCurrentView == LAB){
		mSimulationBackground = mLabBackground;
		mSimulationBackground.setTexture(&getAppTexture(isDebugOn() ?
														getAppConfig().simulation_lab_debug_texture :
														getAppConfig().simulation_lab_texture)
										 , true);
	}
	
	else
		mSimulationBackground = mOrganBackground;
}

void Application::onEvent(sf::Event, sf::RenderWindow&)
{
    // By default nothing is done here
}

void Application::onSimulationStart()
{
    // By default nothing is done here
}

void Application::onUpdate(sf::Time)
{
    // By default nothing is done here
}

void Application::onDraw(sf::RenderTarget&)
{
    // By default nothing is done here

}

Vec2d Application::getCursorPositionInView() const
{
    return mRenderWindow.mapPixelToCoords(sf::Mouse::getPosition(mRenderWindow), mSimulationView);
}

void Application::createWindow(Vec2d const& size)
{
    sf::VideoMode vm(size.x, size.y);

    auto title = getAppConfig().window_title;

    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = getAppConfig().window_antialiasing_level;

    // Create the window
    mRenderWindow.create(vm, title, sf::Style::Close, contextSettings);
    mRenderWindow.setKeyRepeatEnabled(true);
    mRenderWindow.setFramerateLimit(60);
}

void Application::createViews()
{
    //   WINDOW STRUCTURE
    //
    //   ----------------------------
    //   |                      |   | <- mStatsFrame
    //   |                      |   |
    //   |   mSimulationFrame   |   |
    //   |                      |   |
    //   |                      |---|
    //   |                      |   | <- mCommandsHelpFrame
    //   |                      |   |
    //   ----------------------------

	/*
    mSimulationView = setupView(getWorldSize(),
                                getSimulationPosition(), getSimulationSize(),
                                mRenderWindow.getSize());
	*/
	mLabView = setupView(getLabSize(),
                                getSimulationPosition(), getSimulationSize(),
                                mRenderWindow.getSize());
	mOrganView = setupView(getOrganSize(),
						   getSimulationPosition(), getSimulationSize(),
						   mRenderWindow.getSize());
	
    mStatsView = setupView(getStatsSize(),
                           getStatsPosition(), getStatsSize(),
                           mRenderWindow.getSize());

    mHelpView = setupView(getHelpSize(),
                        getHelpPosition(), getHelpSize(),
                        mRenderWindow.getSize());

	mSimulationView = mLabView;
}

void Application::handleEvent(sf::Event event, sf::RenderWindow& window)
{
    // zoom factor
    auto const ZOOM = 1.1f;

    switch (event.type) {
    case sf::Event::Closed:
        window.close();
        break;

    case sf::Event::KeyPressed:
        switch (event.key.code) {

			// Switch to Mice (Lab) View
        case sf::Keyboard::L:
			mCurrentView=LAB;
			mSimulationView = mLabView;
			chooseBackground();
            break;
			
        // Toggle debug mode
        case sf::Keyboard::D:
			switchDebug();
            break;

        // Exit simulation
        case sf::Keyboard::Escape:
            window.close();
            break;

        case sf::Keyboard::C:
			delete mConfig;
            mConfig = new Config(mAppDirectory + mCfgFile); // reconstruct
            break;

        // Toggle pause for simulation
        case sf::Keyboard::Space:
            mPaused = !mPaused;
            break;

        // Reset the simulation
        case sf::Keyboard::R:
			if (mCurrentView == LAB){
				
				mIsResetting = true;
				getLab().reset();
				onSimulationStart();
				createViews();
				mCurrentView = LAB;
				mSimulationBackground= mLabBackground;
				mSimulationView = mLabView;
				chooseBackground();
			}
			
            break;

        case sf::Keyboard::Tab:
            // TODO add TAB binding for switching from graphs
            break;

        // Reset the simulation
        case sf::Keyboard::Right:
            if (mCurrentView == LAB)
            mSimulationView.move(100, 0);
            break;
        case sf::Keyboard::Left:
        if (mCurrentView == LAB)
            mSimulationView.move(-100, 0);
            break;
        case sf::Keyboard::Up:
        if (mCurrentView == LAB)
            mSimulationView.move(0, -100);
            break;
        case sf::Keyboard::Down:
        if (mCurrentView == LAB)
            mSimulationView.move(0, 100);
            break;

        default:
            onEvent(event, window);
            break;
        } // event.key.code switch for sf::Event::KeyReleased
        break;


    // Handle zoom for SFML 2.3+ and older versions as well
#if SFML_VERSION_MAJOR >= 2 && (SFML_VERSION_MINOR > 3 || (SFML_VERSION_MINOR == 3 && SFML_VERSION_PATCH >= 2))
    case sf::Event::MouseWheelScrolled:
        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
            sf::Vector2i pos = { event.mouseWheelScroll.x, event.mouseWheelScroll.y };

            if (event.mouseWheelScroll.delta > 0)
                zoomViewAt(pos, (1.f / ZOOM));
            else if (event.mouseWheelScroll.delta < 0)
                zoomViewAt(pos, ZOOM);
        }
        break;
#else
    // MouseWheelMoved is deprecated. If possible, use MouseWheelScrolled as replacement
    case sf::Event::MouseWheelMoved: {
        sf::Vector2i pos = { event.mouseWheel.x, event.mouseWheel.y };

        if (event.mouseWheel.delta > 0)
            zoomViewAt(pos, (1.f / ZOOM));
        else if (event.mouseWheel.delta < 0)
            zoomViewAt(pos, ZOOM);

        break;
    }
#endif

    // Drag view: initiate drag
    //  - or -
    // Select a bee to follow
    // case sf::Event::MouseButtonPressed:
    //     if (event.mouseButton.button == sf::Mouse::Left) {
    //         mIsDragging = true;
    //         mLastCursorPosition = { event.mouseButton.x, event.mouseButton.y };
    //     } else if (event.mouseButton.button == sf::Mouse::Right) {
    //         auto pos = getCursorPositionInView();
    //         auto* bee = getLab().getAnimalAt(pos);
    //         if (bee == nullptr) {
    //             // Stop tracking animal
    //             getAnimalTracker().stopTrackingAnimal();
    //         } else {
    //             // Track the animal
    //             getAnimalTracker().startTrackingAnimal(bee);
    //         }
    //     }
    //     break;

    // Drag view: end drag
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left)
            mIsDragging = false;
        break;

    // Drag view: move view
    case sf::Event::MouseMoved:
        if (mIsDragging) {
            sf::Vector2i newCurosrPosition = { event.mouseMove.x, event.mouseMove.y };

            dragView(mLastCursorPosition, newCurosrPosition);

            mLastCursorPosition = newCurosrPosition;

            // Stop tracking bee
            //getBeeTracker().stopTrackingBee();
        }
        break;

    default:
        onEvent(event, window);
        break;
    } // event.type switch
}

void Application::render(sf::Drawable const& simulationBackground, sf::Drawable const& statsBackground)
{
    mRenderWindow.clear();

    // Render the simulation
    updateSimulationView();
    mRenderWindow.setView(mSimulationView);
    mRenderWindow.draw(simulationBackground);

	if (mCurrentView == LAB){
		getLab().drawOn(mRenderWindow);

        // Render the command help for MACRO
        mRenderWindow.setView(mHelpView);
        mRenderWindow.draw(statsBackground);
        drawOnHelp(mRenderWindow, false);
	}
	
	else
	{
		getLab().drawCurrentOrgan(mRenderWindow);

        // Render the stats
        mRenderWindow.setView(mStatsView);
        mRenderWindow.draw(statsBackground);

        // Render the command help for MICRO
        mRenderWindow.setView(mHelpView);
        mRenderWindow.draw(statsBackground);
        drawOnHelp(mRenderWindow, true);
	}

    // Finally, publish everything onto the screen
    mRenderWindow.display();

    // Reconfigure the window to use the simulation view
    // so that handling event (zoom + move) is easier
    mRenderWindow.setView(mSimulationView);
}


void Application::togglePause()
{
    mPaused = !mPaused;
}

//void Application::saveConfig() const
//{
//    j::writeToFile(getConfig().getJsonRead(), mAppDirectory + mCfgFile);
//}

void Application::zoomViewAt(sf::Vector2i const& /*pixel*/, float zoomFactor)
{
    // Note: we know that the simulation view is active
    sf::View& view = mSimulationView;

    //auto beforeCoord = mRenderWindow.mapPixelToCoords(pixel);

    view.zoom(zoomFactor);
    mRenderWindow.setView(view);

    // if (!getAnimalTracker().isTrackingAnimal()) {
    //     // If no animal  is selected, center on the cursor position
    //     auto afterCoord = mRenderWindow.mapPixelToCoords(pixel);
    //     auto offsetCoords = beforeCoord - afterCoord;

    //     view.move(offsetCoords);
    //     mRenderWindow.setView(view);
    // }
}

void Application::dragView(sf::Vector2i const& srcPixel, sf::Vector2i const& destPixel)
{
    // Note: we know that the simulation view is active
    sf::View& view = mSimulationView;

    auto src = mRenderWindow.mapPixelToCoords(srcPixel);
    auto dest = mRenderWindow.mapPixelToCoords(destPixel);
    auto dx = src - dest;

    view.move(dx);
    mRenderWindow.setView(view);
}

void Application::updateSimulationView()
{
    // if (getAnimalTracker().isTrackingAnimal()) {
    //     auto pos = getAnimalTracker().getTrackedAnimalPosition();
    //     mSimulationView.setCenter(pos);
    // }
/*
	 mSimulationView = setupView(getWorldSize(),
                                getSimulationPosition(), getSimulationSize(),

								mRenderWindow.getSize());
*/
	/*
	 auto viewSize = getWorldSize();
	 mSimulationView.reset({ { 0, 0 }, viewSize });
	*/
	 /*
    mSimulationView.setViewport({ static_cast<float>(position.x / windowSize.x),
                       static_cast<float>(position.y / windowSize.y),
                       static_cast<float>(allocation.x / windowSize.x),
                       static_cast<float>(allocation.y / windowSize.y) });
	 */
}

void Application::switchDebug()
{
	getAppConfig().switchDebug();
	chooseBackground();
}

void Application::switchToView( View view)
{
	mCurrentView=view;
	mSimulationView = mOrganView;
	mIsSwitchingView = true;
	chooseBackground();
}

void Application::drawOnHelp(sf::RenderWindow& window, bool micro) const
{
    auto const LEGEND_MARGIN = 10;
    auto const FONT_SIZE = 13;
    auto lastLegendY = LEGEND_MARGIN;
    std::vector<std::string> text (9);
    if(micro)
    {
        text = {    "---------------------",
                    "L: Switch to Lab View",
                    "S: Toggle to ConcView of CS",
                    };
    } else {
        text = {    "---------------------",
                    "CP: cursor position",
                    "M: add mouse at CP",
                    "F: add a cheese at CP",
                    "T: track the entity at CP",
                    "O: switch to OrganView",
                    "Z: stop to track any entity",
                    "R: reset the lab"
                    };
    }
    for (auto& command : text)
    {
        auto legend = sf::Text(command, getAppFont(), FONT_SIZE);        
        legend.setPosition(LEGEND_MARGIN, lastLegendY);
#if SFML_VERSION_MAJOR >= 2 && SFML_VERSION_MINOR >= 4
        legend.setFillColor(sf::Color::Black);
#else
        legend.setColor(sf::Color::Black);
#endif
        window.draw(legend);

        lastLegendY += FONT_SIZE + 4;
    }
}


Application& getApp()
{
    assert(currentApp != nullptr);

    return *currentApp;
}

Lab& getAppEnv()
{
    return getApp().getLab();
}

// if needed
// AnimalTracker& getAppAnimalTracker()
// {
//     return getApp().getAnimalTracker();
// }

Config& getAppConfig()
{
    return getApp().getConfig();
}

sf::Font const& getAppFont()
{
    return getApp().getFont();
}

sf::Texture& getAppTexture(std::string const& name)
{
    return getApp().getTexture(name);
}

View Application::getCurrentView() const
{
	return mCurrentView;
}
void Application::toggleConcentrationView()
{
	if (mCurrentView == CONCENTRATION)
		mCurrentView = ECM;
	else
		if (mCurrentView == ECM)
			mCurrentView = CONCENTRATION;
}

bool isDebugOn()
{
    return getAppConfig().getDebug();
}

bool isOrganViewOn()
{
	return getApp().getCurrentView() != LAB;
}



	

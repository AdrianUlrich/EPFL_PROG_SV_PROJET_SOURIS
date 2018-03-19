#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config(std::string path) : mConfig(j::readFromFile(path))
, simulation_debug(mConfig["debug"].toBool())
, window_simulation_width(mConfig["window"]["simulation"]["width"].toDouble())
, window_simulation_height(mConfig["window"]["simulation"]["height"].toDouble())
, window_stats_height(mConfig["window"]["stats"]["height"].toDouble())
, window_title(mConfig["window"]["title"].toString())
, window_antialiasing_level(mConfig["window"]["antialiasing level"].toInt())

// stats
, stats_refresh_rate(mConfig["stats"]["refresh rate"].toDouble())

		// substance
	,substance_max_value(mConfig["simulation"]["substance"]["max"].toDouble())
	,substance_diffusion_radius(mConfig["simulation"]["substance"]["diffusion radius"].toInt())
	,substance_diffusion_constant(mConfig["simulation"]["substance"]["diffusion constant"].toDouble())
	,base_glucose(mConfig["simulation"]["substance"]["glucose"]["base"].toDouble())
	,vgef_diffusion_radius(mConfig["simulation"]["substance"]["vgef"]["diffusion radius"].toInt())

{
}

// TODO : getter for debug
void Config::switchDebug(){
	mConfig["debug"] = j::boolean(!mConfig["debug"].toBool());
	simulation_debug = mConfig["debug"].toBool();
}

bool Config::getDebug(){
return simulation_debug;
}

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

// simulation
, simulation_lab_texture(mConfig["simulation"]["lab"]["texture"].toString())
, simulation_lab_debug_texture(mConfig["simulation"]["lab"]["debug texture"].toString())
, simulation_lab_fence(mConfig["simulation"]["lab"]["fence"].toString())
, simulation_lab_size(mConfig["simulation"]["lab"]["size"].toDouble())
,  simulation_lab_nb_boxes(mConfig["simulation"]["lab"]["nb boxes"].toInt())
, simulation_time_factor(mConfig["simulation"]["time"]["factor"].toDouble())
, simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))


// cheese
, cheese_texture(mConfig["simulation"]["cheese"]["texture"].toString())

, cheese_initial_energy(mConfig["simulation"]["cheese"]["energy"]["initial"].toDouble())
, cheese_max_energy(mConfig["simulation"]["cheese"]["energy"]["max"].toDouble())

// animal
, animal_random_walk_low_energy(mConfig["simulation"]["animal"]["random walk low energy"].toBool())

, animal_meal_retention(mConfig["simulation"]["animal"]["meal retention"].toDouble())
, animal_feed_time(mConfig["simulation"]["animal"]["feed time"].toDouble())
, animal_satiety_min(mConfig["simulation"]["animal"]["satiety"]["min"].toDouble())
, animal_satiety_max(mConfig["simulation"]["animal"]["satiety"]["max"].toDouble())
, animal_idle_probability(mConfig["simulation"]["animal"]["idle"]["probability"].toDouble())
, animal_idle_time_min(mConfig["simulation"]["animal"]["idle"]["min"].toDouble())
, animal_idle_time_max(mConfig["simulation"]["animal"]["idle"]["max"].toDouble())
, animal_min_energy(mConfig["simulation"]["animal"]["min energy"].toDouble())
, animal_base_energy_consumption(mConfig["simulation"]["animal"]["base consumption"].toDouble())

// mouse
, mouse_max_speed(mConfig["simulation"]["animal"]["mouse"]["max speed"].toDouble())
, mouse_mass(mConfig["simulation"]["animal"]["mouse"]["mass"].toDouble())
, mouse_energy_loss_factor(mConfig["simulation"]["animal"]["mouse"]["energy"]["loss factor"].toDouble())
, mouse_view_range(mConfig["simulation"]["animal"]["mouse"]["view"]["range"].toDouble())
, mouse_view_distance(mConfig["simulation"]["animal"]["mouse"]["view"]["distance"].toDouble())
, mouse_longevity(sf::seconds(mConfig["simulation"]["animal"]["mouse"]["longevity"].toDouble()))
, mouse_energy_initial(mConfig["simulation"]["animal"]["mouse"]["energy"]["initial"].toDouble())
, mouse_texture_white(mConfig["simulation"]["animal"]["mouse"]["texture"]["white"].toString())
, mouse_size(mConfig["simulation"]["animal"]["mouse"]["size"].toDouble())
	, mouse_energy_bite(mConfig["simulation"]["animal"]["mouse"]["energy"]["bite"].toDouble())
		// substance
	,substance_max_value(mConfig["simulation"]["substance"]["max"].toDouble())
	,substance_diffusion_radius(mConfig["simulation"]["substance"]["diffusion radius"].toInt())
	,substance_diffusion_constant(mConfig["simulation"]["substance"]["diffusion constant"].toDouble())
	,base_glucose(mConfig["simulation"]["substance"]["glucose"]["base"].toDouble())
	,base_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["base"].toDouble())
	,delta_glucose(mConfig["simulation"]["substance"]["glucose"]["delta"].toDouble())
	,delta_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["delta"].toDouble())
	,delta_vgef(mConfig["simulation"]["substance"]["vgef"]["delta"].toDouble())
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

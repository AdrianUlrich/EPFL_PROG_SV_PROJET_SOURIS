#include "Config.hpp"
#include <JSON/JSONSerialiser.hpp>
// window
Config::Config(std::string path) : mConfig(j::readFromFile(path))
, simulation_debug(mConfig["debug"].toBool())
, window_simulation_width(mConfig["window"]["simulation"]["width"].toDouble())
, window_simulation_height(mConfig["window"]["simulation"]["height"].toDouble())
, window_stats_width(mConfig["window"]["stats"]["width"].toDouble())
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
, simulation_fixed_step(mConfig["simulation"]["time"]["fixed step"].toDouble())
, simulation_time_max_dt(sf::seconds(mConfig["simulation"]["time"]["max dt"].toDouble()))

	//Organ
	, simulation_organ(mConfig["simulation"]["organ"])
	, simulation_organ_size(mConfig["simulation"]["organ"]["size"].toDouble())

	, simulation_organ_nbCells(mConfig["simulation"]["organ"]["cells"].toInt())
	,ecm_texture(mConfig["simulation"]["organ"]["textures"]["ecm"].toString())
	
	,blood_texture(mConfig["simulation"]["organ"]["textures"]["blood"].toString())
	,liver_texture(mConfig["simulation"]["organ"]["textures"]["liver"].toString())
	,concentration_texture(mConfig["simulation"]["organ"]["textures"]["concentration"].toString())
	
	,liver_cancer_texture(mConfig["simulation"]["organ"]["textures"]["cancer"].toString())
	, base_atp_usage(mConfig["simulation"]["organ"]["atp"]["base usage"].toDouble())
	, range_atp_usage(mConfig["simulation"]["organ"]["atp"]["range"].toDouble())

	// Blood system
	,blood_capillary_min_dist(mConfig["simulation"]["organ"]["blood"]["capillary min dist"].toInt())
	,blood_creation_start(mConfig["simulation"]["organ"]["blood"]["creation start"].toInt())

	// liver

	,liver_fract_uptake(mConfig["simulation"]["organ"]["liver"]["fract uptake"].toDouble())
	,liver_km_glycolysis(mConfig["simulation"]["organ"]["liver"]["km glycolysis"].toDouble())
	,liver_km_max_glycolysis(mConfig["simulation"]["organ"]["liver"]["km max glycolysis"].toDouble())
	,liver_time_next_division(mConfig["simulation"]["organ"]["liver"]["time next division"].toInt())
	,liver_range_next_division(mConfig["simulation"]["organ"]["liver"]["range next division"].toInt())
	,liver_km_krebs(mConfig["simulation"]["organ"]["liver"]["km krebs"].toDouble())
	,liver_km_max_krebs(mConfig["simulation"]["organ"]["liver"]["km max krebs"].toDouble())
	,liver_decay_atp(mConfig["simulation"]["organ"]["liver"]["decay atp"].toInt())
	,liver_division_cost(mConfig["simulation"]["organ"]["liver"]["division cost"].toDouble())	,liver_division_radius(mConfig["simulation"]["organ"]["liver"]["division radius"].toInt())
	,liver_division_energy(mConfig["simulation"]["organ"]["liver"]["division energy"].toDouble())
	,liver_glucose_usage(mConfig["simulation"]["organ"]["liver"]["glucose usage"].toDouble())
	// cancer
	,cancer_fract_uptake(mConfig["simulation"]["organ"]["cancer"]["fract uptake"].toDouble())
	,cancer_km_glycolysis(mConfig["simulation"]["organ"]["cancer"]["km glycolysis"].toDouble())
	,cancer_km_max_glycolysis(mConfig["simulation"]["organ"]["cancer"]["km max glycolysis"].toDouble())
	,cancer_time_next_division(mConfig["simulation"]["organ"]["cancer"]["time next division"].toInt())
	,cancer_range_next_division(mConfig["simulation"]["organ"]["cancer"]["range next division"].toInt())
	,cancer_division_energy(mConfig["simulation"]["organ"]["cancer"]["division energy"].toDouble())
	,cancer_glucose_usage(mConfig["simulation"]["organ"]["cancer"]["glucose usage"].toDouble())
// cheese
, cheese_texture(mConfig["simulation"]["cheese"]["texture"].toString())
//, grass_size(mConfig["simulation"]["grass"]["size"].toDouble())
, cheese_initial_energy(mConfig["simulation"]["cheese"]["energy"]["initial"].toDouble())
, cheese_max_energy(mConfig["simulation"]["cheese"]["energy"]["max"].toDouble())

// animal
, time_between_rotations(sf::seconds(mConfig["simulation"]["animal"]["time between rotations"].toDouble()))
, animal_random_walk_low_energy(mConfig["simulation"]["animal"]["random walk low energy"].toBool())
//, animal_safe_distance(mConfig["simulation"]["animal"]["random walk low energy"].toDouble())
, animal_meal_retention(mConfig["simulation"]["animal"]["meal retention"].toDouble())
, animal_feed_time(mConfig["simulation"]["animal"]["feed time"].toDouble())
, animal_satiety_min(mConfig["simulation"]["animal"]["satiety"]["min"].toDouble())
, animal_satiety_max(mConfig["simulation"]["animal"]["satiety"]["max"].toDouble())
, animal_idle_probability(mConfig["simulation"]["animal"]["idle"]["probability"].toDouble())
, animal_idle_time_min(mConfig["simulation"]["animal"]["idle"]["min"].toDouble())
, animal_idle_time_max(mConfig["simulation"]["animal"]["idle"]["max"].toDouble())
, animal_base_energy_consumption(mConfig["simulation"]["animal"]["base consumption"].toDouble())
, animal_min_energy(mConfig["simulation"]["animal"]["min energy"].toDouble())

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
	,vgef_diffusion_radius(mConfig["simulation"]["substance"]["vgef"]["diffusion radius"].toInt())
	,substance_diffusion_constant(mConfig["simulation"]["substance"]["diffusion constant"].toDouble())
	,base_glucose(mConfig["simulation"]["substance"]["glucose"]["base"].toDouble())
	,base_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["base"].toDouble())
	,delta_glucose(mConfig["simulation"]["substance"]["glucose"]["delta"].toDouble())
	,delta_bromo(mConfig["simulation"]["substance"]["bromopyruvate"]["delta"].toDouble())
	,delta_vgef(mConfig["simulation"]["substance"]["vgef"]["delta"].toDouble())

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

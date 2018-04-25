/*
 * prjsv 2016
 * Marco Antognini
 */

#ifndef INFOSV_CONFIG_HPP
#define INFOSV_CONFIG_HPP

#include <string>
#include "JSON/JSON.hpp"
#include <SFML/Graphics.hpp>

// Define resources location
std::string const RES_LOCATION = "../res/";

// Define the location of the config file
std::string const DEFAULT_CFG = "app.json";

// Define the location of the font file (could be in the config instead of here)
std::string const FONT_LOCATION = RES_LOCATION + "sansation.ttf";


class Config
{
private:
	j::Value mConfig;
	bool simulation_debug;

public:
	Config(std::string path);

	// enables / disables debug mode
	void switchDebug();
	bool getDebug();

	// returns read
	j::Value& getJsonRead(){
		return mConfig;
	}

	j::Value const& getJsonRead() const {
		return mConfig;
	}


	//window
	const double window_simulation_width;
	const double window_simulation_height;
	const double window_stats_height;
	const std::string  window_title;
	const int window_antialiasing_level;

	// stats
	const double stats_refresh_rate;
	const std::string stats_log_folder = "logs/";
	const std::string stats_log_prefix = "log_";
	const std::string stats_log_header = "# Plot with GNUPLOT : gnuplot -e \"plot for [i=1:6] 'log_0.txt' u i w l title columnheader(i)\"";

	// debug
	const sf::Color debug_text_color = sf::Color::White;
	const size_t default_debug_text_size = 20;


	//simulation
	const std::string simulation_lab_texture;
	const std::string simulation_lab_debug_texture;
	const std::string simulation_lab_fence;
	const int  simulation_lab_size;
	const int  simulation_lab_nb_boxes;
	const double  simulation_time_factor;
	const sf::Time  simulation_time_max_dt;


	// living entity
	const std::string entity_texture_tracked = "target.png";
	const double entity_energy_critical = 5;

	// cheese
	const std::string cheese_texture;
	const double cheese_initial_energy = 30;
	const double cheese_max_energy = 300;

	// animal
	const sf::Time time_between_rotations;
	const bool animal_random_walk_low_energy;
	const double animal_meal_retention ;
	const float animal_feed_time;
	const double animal_satiety_min;
	const double animal_satiety_max;
	const double animal_idle_probability;
	const float animal_idle_time_min;
	const float animal_idle_time_max;
	const float animal_base_energy_consumption;
	const double animal_min_energy;

	// mouse
	const double mouse_max_speed;
	const double mouse_mass;
	const double mouse_energy_loss_factor;
	const double mouse_view_range;
	const double mouse_view_distance;
	const sf::Time mouse_longevity;
	const double mouse_energy_initial;
	const std::string mouse_texture_white;
	const double mouse_size;
	const double mouse_energy_bite;

	// substance
	const double substance_max_value;
	const int substance_diffusion_radius;
	const int vgef_diffusion_radius;
	const double substance_diffusion_constant;
	const double base_glucose;
	const double base_bromo;
	const double delta_glucose;
	const double delta_bromo;
	const double delta_vgef;
};

#endif // INFOSV_CONFIG_HPP


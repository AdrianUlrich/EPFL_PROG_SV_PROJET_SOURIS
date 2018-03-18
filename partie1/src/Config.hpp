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

	// substance
	const double substance_max_value;
	const int substance_diffusion_radius;
	const double substance_diffusion_constant;
	const double base_glucose;
	const int vgef_diffusion_radius;
};

#endif // INFOSV_CONFIG_HPP


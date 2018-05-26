/*
 * prjsv 2016
 * Marco Antognini
 */

#ifndef INFOSV_CONSTANTS_HPP
#define INFOSV_CONSTANTS_HPP

#include <string>

// Numerical constants
double const DEG_TO_RAD = 0.0174532925; ///< Degree to Radian conversion constant
double const TAU = 6.283185307;         ///< TAU constant (= 2 * PI)
double const PI = 3.141592654;          ///< PI constant
double const EPSILON = 1e-8;            ///< a small epsilon value
double const SUBSTANCE_PRECISION = 0.001;
//double const SUBSTANCE_PRECISION = +1E-9;

// Stats titles
namespace s
{

std::string const GENERAL = "general";
std::string const MOUSE   = "mouse";
std::string const CHEESE  = "cheese";
std::string const ANIMAL_INDIVIDUAL = "Tracked Animal";
std::string const CHEESE_INDIVIDUAL   = "Tracked cheese";
	
std::string const INDIVIDUAL = "Tracked Animal";
std::string const ENERGY = "energy";
std::string const HEALTH = "health";
std::string const DELTAGLUC = "Delta Glucose";
std::string const DELTABROM = "Delta Bromopyruvate";
std::string const DELTAVGEF = "Delta VGEF";
std::string const CURRENTSUBST = "Current Substance";

} // s

#endif // INFOSV_CONSTANTS_HPP

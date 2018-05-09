#ifndef ORGAN_HPP
#define ORGAN_HPP

class Organ 
{
public:
	void update();
	void drawOn(sf::RenderTarget target);
	void updateRepresentation();
	double getWidth() {return getAppConfig().simulation_organ_size;}
	double getHeight() {return getAppConfig().simulation_organ_size;}
	
protected:
	 void generate();
	 void reloadConfig();
	 void reloadCacheStructure();
	 void createLiver();
	 void createBloodSystem();
	 
	 
private:
	int nbCells;
	float cellSize;
	sf::RenderTexture renderingCache;
	
	
};


#endif // ORGAN_HPP

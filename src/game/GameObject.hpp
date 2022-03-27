#pragma once
#include <SDL2/SDL.h>

// [INFO]: For a class to be considered abstract it must have at least one pure virtual function,
// if none are actually needed, destructor can be made into pure virtual
class GameObject {
  public:
	struct Center {
		int x, y;
	};

  protected:
	// [INFO]: Protected constructor disallows creating instances of class, but allows to inherit it
	GameObject(int x, int y, int w, int h);
	SDL_Rect transform;
	double positionX;
	double positionY;

  public:
	// [INFO]: Abstract class always needs virtual destructor for polymorphism
	// [INFO]: Pure virtual destructor still needs implementation
	virtual ~GameObject() = 0;
	void move(double x, double y);
	const SDL_Rect* getTransform() const;
	Center getCenter();
	static double GetDistance(const SDL_Rect* const transform1, const SDL_Rect* const transform2);
	static double GetDistance(Center center1, Center center2);
};
#ifndef ITEM_UI_H
#define ITEM_UI_H
#include "SDL/include/SDL.h"


#include "p2Point.h"


enum UI_STATES
{
	IDLE,
	HOVER,
	CLICK,
	MAX_STATES,
};

class UiItem
{
public:

	UI_STATES state = IDLE;
	SDL_Rect HitBox;
	p2Point<int> pivot = {0,0};
	
	UiItem(p2Point<int> position, p2Point<int> pivot = {0,0}):pivot(pivot)
	{
		HitBox.x = position.x;
		HitBox.y = position.y;
	}

	virtual void Draw() {};



};

#endif // !ITEM_UI_H


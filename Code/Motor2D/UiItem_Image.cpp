#include "UiItem_Image.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Gui.h"
UiItem_Image::UiItem_Image(SDL_Rect hitBox, const SDL_Rect * section, p2Point<int> pivot) : UiItem(hitBox,pivot)
{
	frame = *section;
	
}

void UiItem_Image::Draw()
{
	App->render->Blit((SDL_Texture*)App->Gui->getTexture(), hitBox.x-pivot.x, hitBox.y-pivot.y, &frame, SDL_FLIP_NONE, 0.0F);
}


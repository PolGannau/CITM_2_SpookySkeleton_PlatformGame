#include "j1Gui.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"

#include "j1Fonts.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
	for (uint iter =0; iter <MAX_FONTS; iter++)
	{
		arrayFonts[iter] = nullptr;
	}
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	PathTextureUI = conf.child("UITexture").attribute("file").as_string("");
	arrayFonts[BASE_FONT] = App->font->Load("fonts/open_sans/OpenSans-Bold.ttf");
	arrayFonts[COPPERPLATE_B_I_48] = App->font->Load("fonts/CopperPlate/CopperPlate_BoldItalic.ttf", 48);
	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	UITexture = App->tex->Load(PathTextureUI.GetString());
	
	SDL_Rect sec = { 485, 829, 328, 103 };
	
	return true;
}



bool j1Gui::Update(float dt)
{
	iPoint mousePos;
	App->input->GetMousePosition(mousePos.x, mousePos.y);
	uint mouseButtonDown = App->input->GetMouseButtonDown();
	for (p2List_item<UiItem*>* thisItem = ListItemUI.start; thisItem; thisItem = thisItem->next)
	{
		if (mousePos.x > thisItem->data->hitBox.x-thisItem->data->pivot.x 
			&& mousePos.x < thisItem->data->hitBox.x - thisItem->data->pivot.x + thisItem->data->hitBox.w 
			&& mousePos.y>thisItem->data->hitBox.y - thisItem->data->pivot.y 
			&& mousePos.y < thisItem->data->hitBox.y - thisItem->data->pivot.y + thisItem->data->hitBox.h)
		{
			if (mouseButtonDown != 0 && thisItem->data->state != CLICK)
			{
				thisItem->data->mouseButtonDown = mouseButtonDown;
				thisItem->data->OnClickDown();
				thisItem->data->state = CLICK;
			}
				
			
			else if (thisItem->data->state == IDLE)
					thisItem->data->state = HOVER;
			
			
		}
		else  if (thisItem->data->state == HOVER)
			thisItem->data->state = IDLE;
		if(thisItem->data->state == CLICK && App->input->GetMouseButtonState(thisItem->data->mouseButtonDown)==KEY_UP)
		{
			thisItem->data->state = IDLE;
		}

		
	}
	return true;
}
// Called after all Updates
bool j1Gui::PostUpdate()
{
	for (p2List_item<UiItem*>* thisItem = ListItemUI.start; thisItem; thisItem = thisItem->next)
	{
		thisItem->data->Draw();
		if (showUIHitBox)
		{
			
			App->render->DrawQuad(thisItem->data->hitBox,255,255,255,255,false, false);
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
	{
		showUIHitBox = !showUIHitBox;
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	for (p2List_item<UiItem*>* thisItem = ListItemUI.start; thisItem; thisItem = thisItem->next)
	{
		ListItemUI.del(thisItem);
	}
	ListItemUI.clear();
	return true;
}


UiItem_Label* j1Gui::AddLabel(const char* text, SDL_Color color, TTF_Font * font, p2Point<int> pos)
{
	UiItem* newLabel = new UiItem_Label( text, color, font, pos);
	ListItemUI.add(newLabel);
	UiItem_Label* thisLabel = (UiItem_Label*) newLabel;
	return thisLabel;
}

UiItem_Image * j1Gui::AddImage(SDL_Rect hitBox, const SDL_Rect * section, p2Point<int> pivot)
{
	UiItem* newImage = new UiItem_Image(hitBox, section, pivot);
	ListItemUI.add(newImage);
	UiItem_Image* thisImage = (UiItem_Image*)newImage;
	return thisImage;
	
}

UiItem_Button * j1Gui::AddButton(SDL_Rect hitBox, const SDL_Rect* idle, const SDL_Rect * click, const SDL_Rect * hover, p2Point<int> pivot)
{
	UiItem* newButton = new UiItem_Button(hitBox, idle, click, hover, pivot);
	ListItemUI.add(newButton);
	UiItem_Button* button = (UiItem_Button*)newButton;
	return button;
}

 
// const getter for atlas
 const SDL_Texture* j1Gui::getTexture() const
{
	return UITexture;
}

// class Gui ---------------------------------------------------


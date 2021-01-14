#include <windows.h>
#include "sofheader.h"

#include "DetourXS/detourxs.h"

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <map>

using namespace std;


std::array <menuItemC*,16> Menu::rootMenus;
std::array <menuItemC*,16> Menu::activeMenus;

bool Menu::forwardGateOpen[16] = {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true};
bool Menu::sideGateOpen[16] = {true,true,true,true,true,true,true,true,true,true,true,true,true,true,true,true};


void Menu::onMapBegin(void) {
	char registerLine[64];
	sprintf(registerLine,"pics/sofree/menu_bg.m32");
	orig_SV_FindIndex(registerLine, CS_GHOULFILES, MAX_GHOULFILES, 1,"ghoulfile");

	sprintf(registerLine,"pics/sofree/logo.m32");
	orig_SV_FindIndex(registerLine, CS_GHOULFILES, MAX_GHOULFILES, 1,"ghoulfile");
}


/*
inbuffer is the char buffer from drawScoreboard function that
sends %s string package packet to client
so just appending to that.
*/
void Menu::drawMenu(char * inbuffer, edict_t * ent) {
	int pnum = get_player_slot_from_ent(ent);

	char out[256];
	//top left origin
	//black background for menu
	sprintf(out,"xv %d yv %d picn pics/sofree/menu_bg ",160-128,120-128);
	strcat(inbuffer,out);
	//50 height 256 width
	sprintf(out,"xv %d yv %d picn pics/sofree/logo ",160-128,120-128);
	strcat(inbuffer,out);
	menuItemC* active = activeMenus[pnum];

	//draw all of your children please
	active->draw(inbuffer,ent);
}

/*
Every client has a root menu.
Its stored in the array Menu::rootMenus ( size of 16 )
This function sets an element in that array.
*/
void Menu::setPlayerRootMenu(int who,menuItemC* baseMenu) {
	rootMenus[who] = baseMenu;
}

/*
Get element from array instead of set.
*/
menuItemC* Menu::getPlayerRootMenu(int who) {
	return rootMenus[who];
}

/*
	Do this once when they connect, give them a menu item that is persistent over their connection
*/
void Menu::generateMenu(edict_t * ent) {
	//client has joined the server
	//how do we save his settings?
	//is every player's settings set to default at connect?

	int pnum = get_player_slot_from_ent(ent);
	//root submenu has no parent

	subMenuC* m = new subMenuC(NULL,"root");
	setPlayerRootMenu(pnum,m);
	activeMenus[pnum] = m;

	//root menu has no back.

	subMenuC * mm = new subMenuC(m,"MENU ITEM 1");

	//goback
	mm->appendItem(m,"GO BACK");

	//later try to use a leaf instead of a submenu
	mm->appendItem(new subMenuC(mm,"SUB MENU ITEM 1"));
	m->appendItem(mm);
	m->appendItem(new subMenuC(m,"MENU ITEM 2"));
	m->appendItem(new subMenuC(m,"MENU ITEM 3"));
	m->appendItem(new subMenuC(m,"MENU ITEM 4"));
	m->appendItem(new subMenuC(m,"MENU ITEM 5"));
	m->appendItem(new subMenuC(m,"MENU ITEM 6"));
}


/*
Limit 1 menu operation per draw cycle
*/
/*
void Menu::setForwardState(int who, bool state)
{
	playerForwardStates[who] = state;
}
void Menu::setBackwardState(int who, bool state)
{
	playerBackwardStates[who] = state;
}*/

void Menu::selectionMove(int who,int direction) {
	//close gate
	if ( forwardGateOpen[who] ) {
		forwardGateOpen[who] = false;
		subMenuC* active = activeMenus[who];
		if ( direction > 0 ) {
			active->up(who);
		} else {
			active->down(who);
		}
	}
}

void Menu::selectionRight(int who) {
	if ( sideGateOpen[who] ) {
		sideGateOpen[who] = false;
		subMenuC* active = activeMenus[who];
		active->right(who);
	}
}

void Menu::selectionLeft(int who) {
	if ( sideGateOpen[who] ) {
		sideGateOpen[who] = false;
		subMenuC* active = activeMenus[who];
		active->left(who);
	}
}

//this is not called every server frame...
void subMenuC::draw(char * inbuffer, edict_t * ent) {
	//iterate your children
	for (std::map<int,menuItemC *>::iterator it=children.begin(); it!=children.end(); ++it) {
		//it->first this is your key
		//it->second this is your value


		menuItemC* m = it->second;
		int pos = m->position;

		char out[256];
		char * cc = strdup(m->name.c_str());
		//y position of text items
		int offsety = (120 - 128 + 50 + 16) + 8 * (pos-1);
		int offsetx = 160 - 128 + 16;
		if ( highlightedElemPos != pos ) {
			toggleBits(cc);	
			//altstring is grey
			sprintf(out,"xv %i yv %i altstring \"%s\" ",offsetx,offsety,cc);
		} else {
			sprintf(out,"xv %i yv %i string \"\x9E %s\" ",offsetx,offsety,cc);
		}
		strcat( inbuffer, out);
		free(cc);
	}
}

void menuItemC::toggleBits(char * c) {
	for (int i = 0; i < strlen(c); i++ ) {
		*(c+i) = *(c+i) | 0x80;
	}
}
/*
each submenu has its own 'private list'
*/
subMenuC::subMenuC(menuItemC * own,std::string nam)
{
	//the parent menu
	owner = own;
	//the string of the menu item
	name = nam;
	//how many children it has
	iChildren = 0;

	//its position in its parent's list
	position = 0;

	//start with 1st element highlighted
	highlightedElemPos = 1;
}
/*
	append item to what?????? to some dynamic map ???
*/
void subMenuC::appendItem(menuItemC * newItem, char * overridename = NULL) {
	children[iChildren] = newItem;
	iChildren++;
	//let the newItem know its position within its parent
	//thus position starts at 1. not 0.
	newItem->position = iChildren;
	if ( overridename ) {
		newItem->name = overridename;
	}
}

void subMenuC::up(int who) {
	highlightedElemPos = highlightedElemPos + 1;
	int containerSize = children.size();
	if ( highlightedElemPos > containerSize ) {
		highlightedElemPos = 1;
	}
}
void subMenuC::down(int who) {
	highlightedElemPos = highlightedElemPos - 1;
	int containerSize = children.size();
	if ( highlightedElemPos < 1 ) {
		highlightedElemPos = containerSize;
	}
}


void subMenuC::right(int who) {
	if ( children[highlightedElemPos-1]->iChildren > 0 ) {
		//changing the active item/submenu/leaf
		Menu::activeMenus[who] = children[highlightedElemPos-1];	
	}

	//by changing this, the draw function should consequently change and thus the appearance
}
void subMenuC::left(int who) {
	
}
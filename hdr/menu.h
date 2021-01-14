#include <array>
class menuItemC;
class subMenuC;
//singleton?
class Menu {
public:
	static std::array <menuItemC*,16> rootMenus;
	// static std::array <bool,16> playerForwardStates;
	// static std::array <bool,16> playerBackwardStates;
	static std::array <menuItemC*,16> activeMenus;

	static bool forwardGateOpen[16];
	static bool sideGateOpen[16];

    static void setPlayerRootMenu(int who,menuItemC* baseMenu);
    static menuItemC * getPlayerRootMenu(int who);

	static void generateMenu(edict_t * ent);
	static void drawMenu(char * inbuffer,edict_t * ent);

	// static void setForwardState(int who, bool state);
	// static void setBackwardState(int who, bool state);

	static void onMapBegin(void);

	static void selectionMove(int who,int direction);
	static void selectionRight(int who);
	static void selectionLeft(int who);
};

class menuItemC {
public:
	std::map <int,menuItemC *> children;
	menuItemC * owner;
	std::string name;
	int iChildren;
	int position;

	
	
	void toggleBits(char * c);

	//active menu is drawn
	virtual void draw(char * inbuffer, edict_t * ent) = 0;
	virtual void right(int who) = 0;
	virtual void left(int who) = 0;
	virtual void up(int who) = 0;
	virtual void down(int who) = 0;

};


class subMenuC : public menuItemC {
	public:
		subMenuC(menuItemC * owner,std::string name);

		int highlightedElemPos;

		void moveHighlighted(int direction);

		void appendItem( menuItemC * item, char* overridename = NULL);
		void draw(char * inbuffer, edict_t * ent);
		void right(int who);
		void left(int who);
		void up(int who);
		void down(int who);
};

//leaves dont have children
class leafItemC : public menuItemC {
public:
	leftItemC(menuItemC * owner, std::string name);

	//the leaf item is a wrapper around widgets
	//it will call the individual draw functions of the widgets who are children of this leaf
	void draw(char * inbuffer, edict_t * ent);
	void right(int who);
	void left(int who);
	void up(int who);
	void down(int who);

};


class WidgetC {
	public:
		virtual void draw(char * inbuffer, edict_t * ent) = 0;
		virtual void right(int who) = 0;
		virtual void left(int who) = 0;
		virtual void up(int who) = 0;
		virtual void down(int who) = 0;
};
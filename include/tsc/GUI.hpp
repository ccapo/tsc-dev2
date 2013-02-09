#ifndef GUI_HPP
#define GUI_HPP

#include "Global.hpp"

class GUI
{
	public:
	GUI()
	{
		con = new TCODConsole(DISPLAY_WIDTH, PANEL_HEIGHT);
	}
	~GUI()
	{
		if( con ) delete con;
		log.clearAndDelete();
	}

	void Render();
	void MessageLog(const TCODColor &col, const char *text, ...);

	protected:
	TCODConsole *con;

	struct Message
	{
		char *text;
		TCODColor col;
		Message(const char *text, const TCODColor &col);
		~Message();
	};
	TCODList<Message *> log;

	void RenderBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
	void RenderMouseLook();
};

#endif

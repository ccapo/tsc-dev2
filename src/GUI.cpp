#include "Main.hpp"

void GUI::Render()
{
	// Clear the GUI console
	con->setDefaultBackground(TCODColor::black);
	con->clear();

	// Draw the health bar
	RenderBar(1, 1, BAR_WIDTH, "HP", engine->player->entity->health.hp, engine->player->entity->stats.hpmax, TCODColor::red, TCODColor::darkestRed);

	// Draw the magic bar
	RenderBar(1, 3, BAR_WIDTH, "MP", engine->player->entity->health.mp, engine->player->entity->stats.mpmax, TCODColor::blue, TCODColor::darkestBlue);

	// Draw the experience bar
	RenderBar(1, 5, BAR_WIDTH, "XP", engine->player->entity->health.xp, engine->player->entity->health.xpnext, TCODColor::green, TCODColor::darkestGreen);

	// Draw the Message Log
	int y = MSG_HEIGHT;
	float colCoef = 1.0f;
	float dcolCoef = (1.0f - 0.1f)/static_cast<float>(MSG_HEIGHT);
	for(int i = log.size() - 1; i >= 0; i--)
	{
		Message *message = log.get(i);
		con->setDefaultForeground(message->col*colCoef);
		con->print(MSG_X, y, message->text);
		y--;
		colCoef -= dcolCoef;
	}

	// Mouse Look
	RenderMouseLook();

	// Blit the GUI console on the root console
	TCODConsole::blit(con, 0, 0, DISPLAY_WIDTH, PANEL_HEIGHT, TCODConsole::root, 0, DISPLAY_HEIGHT - PANEL_HEIGHT - 1);
}

void GUI::RenderBar(int x, int y, int width, const char *name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor)
{
	// Fill the background
	con->setDefaultBackground(backColor);
	con->rect(x, y, width, 1, false, TCOD_BKGND_SET);

	int barWidth = static_cast<int>(width*value/maxValue);
	if( barWidth > 0 )
	{
		// Draw the bar
		con->setDefaultBackground(barColor);
		con->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
	}
	// Print text on top of the bar
	con->setDefaultForeground(TCODColor::white);
	con->printEx(x + width/2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s: %g/%g", name, value, maxValue);
}

GUI::Message::Message(const char *text, const TCODColor &col): text(strdup(text)), col(col) {}

GUI::Message::~Message()
{
	free(text);
}

void GUI::RenderMouseLook()
{
	char buffer[CHARMAX] = "";
	bool first = true;
	Map *map = &engine->map[engine->mapID];

	if( engine->mouse.cx < 0 || engine->mouse.cx >= DISPLAY_WIDTH || engine->mouse.cy < 0 || engine->mouse.cy >= DISPLAY_HEIGHT )
	{
		// If mouse is out of FOV, nothing to render
		return;
	}

	for(int i = 0; i < map->objects.size(); i++)
	{
		// Find entities under the mouse cursor
		Object *object = map->objects.get(i);
		for(int i = 0; i < object->sym.size(); i++)
		{
			if( object->x.get(i) == engine->mouse.cx && object->y.get(i) == engine->mouse.cy )
			{
				if( !first )
				{
					strcat(buffer, ", ");
				}
				else
				{
					first = false;
				}
				strcat(buffer, object->name);
			}
		}
	}

	// Display the list of entities under the mouse cursor
	con->setDefaultForeground(TCODColor::lightGrey);
	con->print(1, 0, buffer);
}

void GUI::MessageLog(const TCODColor &col, const char *text, ...)
{
	// Build the text
	va_list ap;
	char buf[CHARMAX];
	va_start(ap, text);
	vsprintf(buf, text, ap);
	va_end(ap);

	char *lineBegin = buf;
	char *lineEnd;
	do
	{
		// Make room for the new message
		if( log.size() == MSG_HEIGHT )
		{
			Message *toRemove = log.get(0);
			log.remove(toRemove);
			delete toRemove;
		}

		// Detect end of the line
		lineEnd = strchr(lineBegin,'\n');
		if( lineEnd ) *lineEnd = '\0';

		// Add a new message to the log
		Message *msg = new Message(lineBegin, col);
		log.push(msg);

		// Go to next line
		lineBegin = lineEnd + 1;
	} while( lineEnd );
}

#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#define ENGINE_NO_GAME_EXCEPTION "Game is not set johnySU. Before start Engine, set the game"

#define KEYBOARD_LISTENER_ALREADY_ADDED "This listener is already added"

#define NO_SUCH_RENDER_OPTION "There is no such RenderingOption"

class Exception: public std::runtime_error
{
public:
	explicit Exception(const std::string& _Message)
		: runtime_error(_Message)
	{
	}
};

#endif

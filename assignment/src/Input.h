#ifndef INPUT_H_
#define INPUT_H_

#include <map>
#include <string>
#include <GLFW/glfw3.h>

/// <summary>
/// Input is a singleton that provides easier access input state.
/// </summary>
class Input
{
private:
	// Singleton
	inline static Input* instance = nullptr;

	// Constructor
	// There are probably more contructors that 
	// should be removed as well. 
	Input() {};

public:
	// Static methods

	/// <summary>
	/// Get the Input instance
	/// </summary>
	static Input* GetInstance();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="name">Button name</param>
	/// <param name="keyCode">GLFW key code</param>
	static void BindButton(std::string name, int keyCode);

	/// <summary>
	/// Was the button pressed this frame?
	/// </summary>
	static bool ButtonDown(std::string name);

	/// <summary>
	/// Was the button released this frame?
	/// </summary>
	static bool ButtonUp(std::string name);

	/// <summary>
	/// Is the button currently held?
	/// </summary>
	static bool ButtonHeld(std::string name);

	static void ClearFlags();

public:
	struct ButtonBinding
	{
		std::string name;
		int keyCode = 0;
		bool pressed = false;
		bool released = false;
		bool held = false;
	};

	// map to store all bindings
	std::map<std::string, ButtonBinding> bindings = {};
};

#endif // !INPUT_H_

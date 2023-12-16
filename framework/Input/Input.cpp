#include <logger.h>
#include "Input.h"

InputManager* InputManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new InputManager();
		Log::info("InputManager", "Instantiating input singleton");
	}

	return instance;
}

void InputManager::BindButton(std::string name, int keyCode)
{
	ButtonBinding b = { keyCode, false, false, false };
	GetInstance()->bindings.try_emplace(name,  b);

	Log::info("InputManager", "Button binding: \"", name, "\" -> ", keyCode);
}

bool InputManager::ButtonDown(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("InputManager", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.pressed;
}

bool InputManager::ButtonUp(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("InputManager", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.released;
}

bool InputManager::ButtonHeld(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("InputManager", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.held;
}

void InputManager::ClearFlags()
{
	for (auto& b : instance->bindings)
	{
		b.second.pressed = false;
		b.second.released = false;
	}
}

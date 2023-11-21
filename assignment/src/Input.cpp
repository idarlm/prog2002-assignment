#include <logger.h>
#include "Input.h"

Input* Input::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Input();
		Log::info("Input", "Instantiating input singleton");
	}

	return instance;
}

void Input::BindButton(std::string name, int keyCode)
{
	ButtonBinding b = { name, keyCode, false, false, false };
	GetInstance()->bindings.try_emplace(name,  b);

	Log::info("Input", "Button binding: \"", name, "\" -> ", keyCode);
}

bool Input::ButtonDown(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("Input", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.pressed;
}

bool Input::ButtonUp(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("Input", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.released;
}

bool Input::ButtonHeld(std::string name)
{
	auto b = instance->bindings.find(name);
	if (b == instance->bindings.end())
	{
		Log::error("Input", "Binding does not exist: \"", name, "\"");
		return false;
	}

	return b->second.held;
}

void Input::ClearFlags()
{
	for (auto& b : instance->bindings)
	{
		b.second.pressed = false;
		b.second.released = false;
	}
}

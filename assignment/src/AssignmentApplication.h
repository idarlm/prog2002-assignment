#ifndef ASSIGNMENTAPPLICATION_H_
#define ASSIGNMENTAPPLICATION_H_

#include <GLFWApplication.h>
#include <vector>
#include <memory>
#include "Entity.h"

/// <summary>
/// AssignmentApplication contains the code for data loading
/// and the application loop.
/// </summary>
class AssignmentApplication : public GLFWApplication 
{
private:
	std::vector<std::shared_ptr<Entity>> entities = {};

public:
	inline static int selected = 0;

public:
	AssignmentApplication(std::string version);

	/// <summary>
	/// Loads all data and gets the application ready to run.
	/// Should be called after setting window properties (size, title...)
	/// </summary>
	/// <returns></returns>
	unsigned Init() override;

	/// <summary>
	/// Run starts the application loop.
	/// </summary>
	/// <returns></returns>
	unsigned Run() const override;

	void AddEntity(std::shared_ptr<Entity> entity) { entities.push_back(entity); }
};

#endif // !ASSIGNMENTAPPLICATION_H_

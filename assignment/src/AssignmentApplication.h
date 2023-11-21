#ifndef ASSIGNMENTAPPLICATION_H_
#define ASSIGNMENTAPPLICATION_H_

#include <GLFWApplication.h>

class AssignmentApplication : public GLFWApplication 
{
public:
	AssignmentApplication(std::string version);

	unsigned Init() override;
	unsigned Run() const override;
};

#endif // !ASSIGNMENTAPPLICATION_H_

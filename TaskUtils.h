#ifndef TASKUTILS_H
#define TASKUTILS_H

class TaskUtils
{
public:
	static const char* _clouds_path;
	static const char* _bc_path;

	static int RandomInt(size_t range = 0);
	static char KeyPressed();
};

#endif

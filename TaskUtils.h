#ifndef TASKUTILS_H
#define TASKUTILS_H

class TaskUtils
{
public:
	static const char* _clouds_path;
	static const char* _bc_path;
	static const char* _apple_path;
	static const char* _snake_head_path;

	static int RandomInt(int range = 0);
	static char KeyPressed();
};

#endif

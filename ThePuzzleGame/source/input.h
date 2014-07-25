#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"

class Input{
public:
	Input();

	void Update();
	void Reset();

	static void OnClickCallback(s3ePointerEvent* event);
	static void OnDragCallback(s3ePointerMotionEvent* event);
	static void OnMultiTouchClickCallback(s3ePointerTouchEvent* event);
	static void OnMultiTouchDragCallback(s3ePointerTouchMotionEvent* event);
};

extern Input* g_Input;
#endif
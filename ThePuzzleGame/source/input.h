#if !defined(_INPUT_H)
#define _INPUT_H

#include "s3ePointer.h"

class Input{
private:
	int m_x, m_y;
	bool m_Touched;
	bool m_PrevTouched;
public:
	int GetX() const;
	int GetY() const;
public:
	Input();

	/**
	* @brief Updates the input. Should be called every frame.
	*/
	void Update();

	/**
	* @brief Resets the input.
	*/
	void Reset();

	/**
	* @brief Returns true when the current event has been a click.
	*/
	bool isClick();

	/**
	* @brief Returns true when the current event is a Drag.
	*/
	bool isDragging();

	// Callback functions for Input handling
	static void OnClickCallback(s3ePointerEvent* event);
	static void OnDragCallback(s3ePointerMotionEvent* event);
	static void OnMultiTouchClickCallback(s3ePointerTouchEvent* event);
	static void OnMultiTouchDragCallback(s3ePointerTouchMotionEvent* event);
};

// a global variable for input handling
extern Input* g_Input;

#endif
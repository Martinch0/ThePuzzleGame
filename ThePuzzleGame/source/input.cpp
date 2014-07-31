#include "Input.h"

Input* g_Input = NULL;


Input::Input() : m_Touched(false), m_PrevTouched(false)
{
	if (s3ePointerGetInt(S3E_POINTER_MULTI_TOUCH_AVAILABLE) != 0)
	{
		s3ePointerRegister(S3E_POINTER_TOUCH_EVENT, (s3eCallback)OnMultiTouchClickCallback, 0);
		s3ePointerRegister(S3E_POINTER_TOUCH_MOTION_EVENT, (s3eCallback)OnMultiTouchDragCallback, 0);
	}
	else
	{
		s3ePointerRegister(S3E_POINTER_BUTTON_EVENT, (s3eCallback)OnClickCallback, 0);
		s3ePointerRegister(S3E_POINTER_MOTION_EVENT, (s3eCallback)OnDragCallback, 0);
	}
}

void Input::Update()
{
	s3ePointerUpdate();
}

void Input::Reset()
{
	m_PrevTouched = false;
	m_Touched = false;
}

bool Input::isClick()
{
	return m_PrevTouched && !m_Touched;
}

bool Input::isDragging()
{
	return m_PrevTouched && m_Touched;
}

void Input::OnClickCallback(s3ePointerEvent* event)
{
	g_Input->m_PrevTouched = g_Input->m_Touched;
	g_Input->m_Touched = event->m_Pressed != 0;
	g_Input->m_x = event->m_x;
	g_Input->m_y = event->m_y;
}

void Input::OnDragCallback(s3ePointerMotionEvent* event)
{
	g_Input->m_x = event->m_x;
	g_Input->m_y = event->m_y;
}

void Input::OnMultiTouchClickCallback(s3ePointerTouchEvent* event)
{
	g_Input->m_PrevTouched = g_Input->m_Touched;
	g_Input->m_Touched = event->m_Pressed != 0;
	g_Input->m_x = event->m_x;
	g_Input->m_y = event->m_y;
}

void Input::OnMultiTouchDragCallback(s3ePointerTouchMotionEvent* event)
{
	g_Input->m_x = event->m_x;
	g_Input->m_y = event->m_y;
}

int Input::GetX() const
{
	return m_x;
}
int Input::GetY() const
{
	return m_y;
}
#ifndef ARE_AVRO_WINDOW_H
#define ARE_AVRO_WINDOW_H

class DLLEXPORT Window{
public:
	glob void Win32_CreateWindow(HWND* window, HINSTANCE hInstance, U32 width, U32 height, char* title, B8* isRunning);
	//glob INLINEFORCE void UpdateWindow(B8* isRunning){ m_isRunning = isRunning; }
private:
	intern I64 CALLBACK Win32_Callback(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
	Window(){}
	Window(const Window& rhs){}
	void operator=(const Window& rhs){}
};

#endif
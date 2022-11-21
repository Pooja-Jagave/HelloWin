#include <Windows.h>
#include <assert.h>

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
// HINSTANCE = Handle to an "instance" - the program itself
{
    static TCHAR szClassName[] = TEXT("The standerd Window"); // window caption
    static TCHAR szWindowName[] = TEXT("HelloWin!");

    HWND hWnd = NULL;  // HWND = Handle to a window
    HBRUSH hBrush = NULL;
    HCURSOR hCursor = NULL;
    HICON hIcon = NULL;
    HICON hIconSm = NULL;

    WNDCLASSEX wndEx; // Windows class structure
    MSG msg; // Message structure

    ZeroMemory(&wndEx, sizeof(WNDCLASSEX));
    ZeroMemory(&msg, sizeof(MSG));

    hBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
    /* GetStockObject = Obtains a graphic object, in this case a brush used for painting
    the  window's background */
    assert(hBrush);

    hCursor = LoadCursor(NULL, IDC_ARROW); // IDC = ID number for an cursor
    // LoadeCursor = Loads a mouse cursor for use by a program
    assert(hCursor);

    hIcon = LoadIcon(NULL, IDI_APPLICATION);// IDI = ID number for an icon
    // LoadIcon = Loades an icon for use by Program.
    assert(hIcon);

    hIconSm = LoadIcon(NULL, IDI_APPLICATION); // ID number for an icon
    assert(hIconSm);

    wndEx.cbSize = sizeof(WNDCLASSEX);

    wndEx.cbClsExtra = 0;
    wndEx.cbWndExtra = 0;
    wndEx.hbrBackground = hBrush;
    wndEx.hCursor = hCursor;
    wndEx.hIcon = hIcon;
    wndEx.hIconSm = hIconSm;
    wndEx.hInstance = hInstance;
    wndEx.lpfnWndProc = WndProc; // p = Pointer, fn = function
    wndEx.lpszClassName = szClassName; // sz = string terminated by 0 character
    wndEx.lpszMenuName = 0;
    wndEx.style = CS_VREDRAW | CS_HREDRAW;


    ATOM bRet = RegisterClassEx(&wndEx); 
    // RegisterClass = Registers a window class for the program's window
    assert(bRet);

    hWnd = CreateWindowEx(WS_EX_APPWINDOW, szClassName, szWindowName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
   CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,  NULL, NULL, hInstance, NULL);
   // createWindow = Creates a window based on a window class.
   // WS = Windows style
   // CS = Class style option
   // szClassName = window class name
   // szWindowName = window caption
   // WS_OVERLAPPEDWINDOW = window style
   // CW_USEDEFAULT = initial x position
   // CW_USEDEFAULT = initial y position
   // CW_USEDEFAULT = initial x size
   // CW_USEDEFAULT = initial y size
   // NULL = Parent window handle
   // NULL = window menu handal
   // hInstance = Program instance handale
   // NULL = creation parameters
   assert(hWnd != NULL);

   ShowWindow(hWnd, nShowCmd); // show the window on the screen
   UpdateWindow(hWnd); // Directs the window to paint itself

   while(GetMessage(&msg, NULL, 0, 0)) // Obtains a message from the message queue.
   {
       TranslateMessage(&msg); // Translates some keyboard messages.
       DispatchMessage(&msg); // Sends a messages to a window procedure.
   }

   return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_DESTROY: // WM = Window message
            PostQuitMessage(0); // Insert a "quit" Message into the message queue.
            break;
    }

    return (DefWindowProc(hWnd, uMsg, wParam, lParam)); // Performs default processing of messages
}
// WindowsProject1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject1.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];    
static COLORREF colorText = RGB(255, 255, 255); // задаём цвет текста// the main window class name
static HWND hWnD;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
static int finalx = 1100;
static int x = 500;
static int y = 250;
bool direction = true;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PANDA));
    wcex.hCursor        = (HCURSOR)LoadImage(NULL,L"Normal.cur" , IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hBtnStart, hBtnStop;
   hWnD = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   HMENU hMenubar = CreateMenu();
   HMENU hFileMenu = CreateMenu(); 
   HMENU hDisplayMenu = CreatePopupMenu(); 

   RECT rect;

   GetWindowRect(hWnD, &rect);
   x = (int)((rect.right - rect.left)/2);
   
   AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
   AppendMenu(hFileMenu, MF_STRING | MF_POPUP, (UINT_PTR)hDisplayMenu, L"Operation"); 
   AppendMenu(hDisplayMenu, MF_STRING, IDM_START, L"Start");
   AppendMenu(hDisplayMenu, MF_STRING, IDM_STOP, L"Stop"); 
   AppendMenu(hFileMenu, MF_STRING, IDM_EXIT, L"Exit"); 
   SetMenu(hWnD, hMenubar);

   /*hBtnStart = CreateWindow(L"button", L"Start", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 55, 200, 30, hWnd, (HMENU)101, hInst, 0);
   hBtnStop = CreateWindow(L"button", L"Stop", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 50, 100, 200, 30, hWnd, (HMENU)101, hInst, 0);*/

   if (!hWnD)
   {
      return FALSE;
   }

   ShowWindow(hWnD, nCmdShow);
   UpdateWindow(hWnD);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    //static HWND hButton;

    switch (message)
    {
    case WM_SIZE:
        y = (int)(HIWORD(lParam)/2); 
        finalx = LOWORD(lParam);
        break;
    case WM_TIMER: {
        if (x == finalx - 80)
            direction = false;
        else if(x == 0)
            direction = true;
        if (direction)
            x += 1;
        else
            x -= 1;

        InvalidateRect(hWnd, NULL, FALSE);
    } break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_START:
                colorText = RGB(255, 0, 0);
                SetTimer(hWnD, 1000, 2, NULL);
                break;
            case IDM_STOP:
                KillTimer(hWnD,1000);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rect; // стр-ра, определяющая размер клиентской области
            
            GetClientRect(hWnd, &rect); // получаем ширину и высоту области для рисования
            SetTextColor(hdc, colorText); // устанавливаем цвет контекстного устройства
            TextOut(hdc, x, y, L"Hello world: ", strlen("Hello world:  "));

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
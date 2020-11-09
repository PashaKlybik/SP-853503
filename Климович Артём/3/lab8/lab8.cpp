#include "framework.h"
#include "lab8.h"
#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//ìîå
bool Visible = false;
HWND Add, Clear;
HBRUSH brush;
HPEN pen;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_LAB8, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB8));

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

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB8));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB8);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	Add = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		520, 120, 60, 60, hWnd, (HMENU)IDC_DRAW_ID, NULL, NULL);
	Clear = CreateWindow(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW | BS_PUSHBUTTON,
		590, 120, 60, 60, hWnd, (HMENU)IDC_CLEAR_ID, NULL, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

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
	switch (message)
	{
	case WM_COMMAND:
		int Action;
		Action = LOWORD(wParam);
		switch (Action)
		{
		case IDC_CLEAR_ID:
			Visible = false;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDC_DRAW_ID:
			Visible = true;
			InvalidateRect(hWnd, NULL, true);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DRAWITEM:
	{
		DRAWITEMSTRUCT* draw = (DRAWITEMSTRUCT*)lParam;
		HDC hdc = draw->hDC;
		pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
		switch (draw->CtlID)
		{
		case IDC_DRAW_ID:
		{
			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(206, 240, 201));
			}
			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 25, 40, NULL);
			LineTo(hdc, 30, 20);
			MoveToEx(hdc, 35, 40, NULL);
			LineTo(hdc, 30, 20);
			MoveToEx(hdc, 32, 32, NULL);
			LineTo(hdc, 28, 32);
		}
		break;
		case IDC_CLEAR_ID:
		{
			if (draw->itemAction == ODA_SELECT) {
				brush = CreateSolidBrush(RGB(0, 0, 255));
			}
			else {
				brush = CreateSolidBrush(RGB(167, 56, 83));
			}

			SelectObject(hdc, brush);
			SelectObject(hdc, pen);

			Ellipse(hdc, 0, 0, 60, 60);
			MoveToEx(hdc, 20, 20, NULL);
			LineTo(hdc, 40, 40);
			MoveToEx(hdc, 40, 20, NULL);
			LineTo(hdc, 20, 40);
		}
		break;
		}

	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		if (Visible)
		{
			pen = CreatePen(BS_SOLID, 7, RGB(100, 100, 100));
			SelectObject(hdc, pen);
			Arc(hdc, 330, 40, 430, 100, 360, 80, 400, 80);
			Arc(hdc, 180, 40, 280, 100, 210, 80, 250, 80);

			brush = CreateSolidBrush(RGB(50, 50, 50));
			SelectObject(hdc, brush);
			Ellipse(hdc, 160, 260, 200, 300);
			Ellipse(hdc, 380, 260, 420, 300);

			brush = CreateSolidBrush(RGB(19, 168, 176));
			pen = CreatePen(BS_SOLID, 2, RGB(0, 0, 0));
			SelectObject(hdc, brush);
			SelectObject(hdc, pen);
			POINT p[18] = { 100, 275, 160, 275,
							480, 275, 450, 200, 200, 200, 130, 200
			};
			Polygon(hdc, p, 6);

			brush = CreateSolidBrush(RGB(48, 230, 72));
			SelectObject(hdc, brush);
			POINT p2[4] = { 290, 200, 290, 275, 380,250,380,200 };
			Polygon(hdc, p2, 4);

			pen = CreatePen(BS_SOLID, 1, RGB(0, 0, 0));
			brush = CreateSolidBrush(RGB(149, 184, 242));
			SelectObject(hdc, pen);
			SelectObject(hdc, brush);
			Rectangle(hdc, 200, 100, 290, 200);
			Rectangle(hdc, 290, 100, 380, 200);
		}
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

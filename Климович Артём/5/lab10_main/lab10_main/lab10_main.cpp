#include "framework.h"
#include "lab10_main.h"

#define MAX_LOADSTRING 100



WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


PAINTSTRUCT ps;
HDC hdc;
HBRUSH brush;
UINT DRAW;
UINT COLOR;
UINT SHAPE;
bool draw = false;
int color = 0, shape = 0;
int PositionX = -1, PositionY = -1;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB10MAIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB10MAIN));

	MSG msg;

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



ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB10MAIN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB10MAIN);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	DRAW = RegisterWindowMessage((LPCWSTR)DRAW_MESSAGE);
	COLOR = RegisterWindowMessage((LPCWSTR)COLOR_MESSAGE);
	SHAPE = RegisterWindowMessage((LPCWSTR)SHAPE_MESSAGE);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		PositionX = LOWORD(lParam);
		PositionY = HIWORD(lParam);
		InvalidateRect(hWnd, NULL, true);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
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
		hdc = BeginPaint(hWnd, &ps);
		if (draw && PositionX != -1) {

			switch (color)
			{
			case 0:
				brush = CreateSolidBrush(RGB(255, 0, 0));
				break;
			case 1:
				brush = CreateSolidBrush(RGB(0, 255, 0));
				break;
			case 2:
				brush = CreateSolidBrush(RGB(0, 0, 255));
				break;
			default:
				brush = CreateSolidBrush(RGB(255, 255, 255));
				break;
			}
			SelectObject(hdc, brush);

			switch (shape)
			{
			case 0:
			{
				POINT p[4] = { PositionX + 10, PositionY + 0, PositionX + 20, PositionY + 10,
					PositionX + 10, PositionY + 20, PositionX + 0, PositionY + 10 };
				Polygon(hdc, p, 4);
			}
			break;
			case 1:
				Rectangle(hdc, PositionX, PositionY, PositionX + 20, PositionY + 20);
				break;
			case 2:
				Ellipse(hdc, PositionX, PositionY, PositionX + 20, PositionY + 20);
				break;
			case 3:
			{
				POINT p[10] = { PositionX + 15, PositionY + 10,PositionX + 20, PositionY + 3, PositionX + 25, PositionY + 10, PositionX + 35, PositionY + 13,
								PositionX + 27, PositionY + 18, PositionX + 30, PositionY + 25, PositionX + 20, PositionY + 20, PositionX + 10, PositionY + 25,
								PositionX + 13, PositionY + 17, PositionX + 5, PositionY + 13 };
				Polygon(hdc, p, 10);
			}
			break;
			default:
				break;
			}
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		if (message == DRAW)
		draw = lParam;
	else if (message == SHAPE)
		shape = lParam;
	else if (message == COLOR)
		color = lParam;
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

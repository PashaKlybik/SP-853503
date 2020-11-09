
#include "framework.h"
#include "lab10.h"

#define MAX_LOADSTRING 100
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
HWND next_page;
UINT DRAW;
UINT COLOR;
UINT SHAPE;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_LAB10, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB10));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB10));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB10);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 250, 250, nullptr, nullptr, hInstance, nullptr);


	CreateWindow(L"button", L"Ромб",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 10, 80, 30, hWnd, (HMENU)RBUTTONROMB_ID, hInstance, NULL);
	CreateWindow(L"button", L"Квадрат",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 35, 80, 30, hWnd, (HMENU)RBUTTONSQUARE_ID, hInstance, NULL);
	CreateWindow(L"button", L"Круг",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 60, 80, 30, hWnd, (HMENU)RBUTTONROUND_ID, hInstance, NULL);
	CreateWindow(L"button", L"Звезда",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		10, 85, 80, 30, hWnd, (HMENU)RBUTTONSTAR_ID, hInstance, NULL);
	CreateWindow(L"button", L"Красный",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		110, 10, 80, 30, hWnd, (HMENU)RBUTTONRED_ID, hInstance, NULL);
	CreateWindow(L"button", L"Зеленый",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		110, 35, 80, 30, hWnd, (HMENU)RBUTTONGREEN_ID, hInstance, NULL);
	CreateWindow(L"button", L"Голубой",
		WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
		110, 60, 80, 30, hWnd, (HMENU)RBUTTONBLUE_ID, hInstance, NULL);

	CreateWindow(L"button", L"Draw",
		WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
		60, 150, 80, 30, hWnd, (HMENU)CHECKBOX_ID, hInstance, NULL);

	CheckRadioButton(hWnd, RBUTTONRED_ID, RBUTTONBLUE_ID, RBUTTONRED_ID);
	CheckRadioButton(hWnd, RBUTTONROMB_ID, RBUTTONSTAR_ID, RBUTTONROMB_ID);

	DRAW = RegisterWindowMessage(L"DrawMessage");
	COLOR = RegisterWindowMessage(L"ColorMessage");
	SHAPE = RegisterWindowMessage(L"ShapeMessage");

	next_page = FindWindow(NULL, L"lab10_main");

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
	int wmId;
	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		switch (wmId)
		{
		case RBUTTONRED_ID:
		case RBUTTONGREEN_ID:
		case RBUTTONBLUE_ID:
			if (next_page == NULL) break;
			SendMessage(next_page, COLOR, 0, wmId - RBUTTONRED_ID);
			CheckRadioButton(hWnd, RBUTTONRED_ID, RBUTTONBLUE_ID, wmId);
			break;
		case RBUTTONROMB_ID:
		case RBUTTONSQUARE_ID:
		case RBUTTONROUND_ID:
		case RBUTTONSTAR_ID:
			if (next_page == NULL) break;
			SendMessage(next_page, SHAPE, 0, wmId - RBUTTONROMB_ID);
			CheckRadioButton(hWnd, RBUTTONROMB_ID, RBUTTONSTAR_ID, wmId);
			break;
		case CHECKBOX_ID:
		{
			if (next_page == NULL) break;
			SendMessage(next_page, DRAW, 0, 0);
			HWND hWndCheck = GetDlgItem(hWnd, CHECKBOX_ID);
			LRESULT state = SendMessage(hWndCheck, BM_GETCHECK, 0, 0);
			if (state == BST_CHECKED)
			{
				SendMessage(next_page, DRAW, 0, 1);
			}
			if (state == BST_UNCHECKED)
			{
				SendMessage(next_page, DRAW, 0, 0);
			}
		}
		break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
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
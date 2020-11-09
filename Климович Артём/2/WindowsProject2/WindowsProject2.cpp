// WindowsProject2.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "WindowsProject2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND static hButtonAdd, hButtonDelete, hButtonClear, hButtonToRight;
HWND static hList, hList1;
HWND static hEdit;
// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
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

	hButtonDelete = CreateWindowW(L"button", L"Delete", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 185, 110, 70, 40, hWnd, (HMENU)IDM_DELETE, hInstance, NULL);
	hButtonAdd = CreateWindowW(L"button", L"Add", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 185, 150, 70, 40, hWnd, (HMENU)IDM_ADD, hInstance, NULL);
	hButtonClear = CreateWindowW(L"button", L"Clear", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 185, 190, 70, 40, hWnd, (HMENU)IDM_CLEAR, hInstance, NULL);
	hButtonToRight = CreateWindowW(L"button", L"ToRight", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 185, 230, 70, 40, hWnd, (HMENU)IDM_TORIGHT, hInstance, NULL);
	hList = CreateWindowW(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 270, 110, 200, 150, hWnd, (HMENU)ID_LIST, hInstance, NULL);
	hList1 = CreateWindowW(L"listbox", NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 470, 110, 200, 150, hWnd, (HMENU)ID_LIST1, hInstance, NULL);
	hEdit = CreateWindowW(L"edit", NULL, WS_VISIBLE | WS_CHILD | LBS_STANDARD, 670, 10, 200, 30, hWnd, (HMENU)ID_EDIT, hInstance, NULL);
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
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_ADD:
		{
			int len = GetWindowTextLength(hEdit) + 1;
			TCHAR* buff = new TCHAR[len];
			len = GetWindowText(hEdit, buff, len);
			buff[len] = 0;
			if (buff[0] == '\0')
				break;
			int string_consist = SendMessage(hList, LB_FINDSTRINGEXACT, 0, (LPARAM)buff);
			if (string_consist == -1)
			{
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buff);
				SetWindowText(hEdit, L"");
			}
			delete[] buff;
			break;
		}
		case IDM_DELETE:
			int itemIndex;
			itemIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (itemIndex != -1)
				SendMessage(hList, LB_DELETESTRING, itemIndex, 0);
			itemIndex = SendMessage(hList1, LB_GETCURSEL, 0, 0);
			if (itemIndex != -1)
				SendMessage(hList1, LB_DELETESTRING, itemIndex, 0);
			break;
		case IDM_TORIGHT:
		{
			int itemIndex;
			TCHAR lpszBuffer[MAX_PATH];
			itemIndex = SendMessage(hList, LB_GETCURSEL, 0, 0);
			if (itemIndex == -1)
				break;
			SendMessage(hList, LB_GETTEXT, itemIndex, (LPARAM)(LPCTSTR)lpszBuffer);
			int string_consist = SendMessage(hList1, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszBuffer);
			if (string_consist == -1)
			{
				SendMessage(hList1, LB_ADDSTRING, 0, (LPARAM)lpszBuffer);
				SetWindowText(hEdit, L"");
			}
			SendMessage(hList, LB_DELETESTRING, itemIndex, 0);
			break;
		}
		case IDM_CLEAR:
			SendMessage(hList, LB_RESETCONTENT, 0, 0);
			SendMessage(hList1, LB_RESETCONTENT, 0, 0);
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
		// TODO: Add any drawing code that uses hdc here...
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

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

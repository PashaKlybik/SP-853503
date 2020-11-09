#include "framework.h"
#include "lab9.h"

#define MAX_LOADSTRING 100
#define STEP 10



HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];
PAINTSTRUCT ps;
HDC hdc ;
HDC hCompatibleDC ;
HANDLE Image[5];

int currentX = 0, currentY = 0, ClickX = 0, ClickY = 0, VisibleImage = 0;
bool reverse = false;

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


    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB9));

    MSG msg;

    // Цикл основного сообщения:
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
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB9));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB9);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    Image[0] = LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 32, 37, LR_LOADFROMFILE);
    Image[1] = LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 32, 37, LR_LOADFROMFILE);
    Image[2] = LoadImage(NULL, L"3.bmp", IMAGE_BITMAP, 32, 37, LR_LOADFROMFILE);
    Image[3] = LoadImage(NULL, L"4.bmp", IMAGE_BITMAP, 32, 37, LR_LOADFROMFILE);
    Image[4] = LoadImage(NULL, L"5.bmp", IMAGE_BITMAP, 32, 37, LR_LOADFROMFILE);
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
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
    case WM_LBUTTONDOWN:
    {
        ClickX = LOWORD(lParam) - 32;
        ClickY = HIWORD(lParam) - 37;
        SetTimer(hWnd, NULL, 100, NULL);
    }
    break;
    case WM_TIMER:
    {
        if (abs(currentX - ClickX) >= STEP) {
            if (ClickX > currentX) {
                currentX += STEP;
                reverse = false;
            }
            else {
                currentX -= STEP;
                reverse = true;
            }
            VisibleImage = (VisibleImage + 1) % 5;
            InvalidateRect(hWnd, NULL, true);
            SetTimer(hWnd, NULL, 100, NULL);
        }
        if (abs(currentY - ClickY) >= STEP) {
            if (ClickY > currentY)
                currentY += STEP;
            else
                currentY -= STEP;
            VisibleImage = (VisibleImage + 1) % 5;
            InvalidateRect(hWnd, NULL, true);
            SetTimer(hWnd, NULL, 100, NULL);
        }
        
    }
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        hCompatibleDC = CreateCompatibleDC(hdc);
        SelectObject(hCompatibleDC, Image[VisibleImage]);
        if (reverse)
            StretchBlt(hdc, currentX, currentY, 100, 100, hCompatibleDC, 100, 0, -100, 100, SRCCOPY);
        else
            StretchBlt(hdc, currentX, currentY, 100, 100, hCompatibleDC, 0, 0, 100, 100, SRCCOPY);
        DeleteDC(hCompatibleDC);

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


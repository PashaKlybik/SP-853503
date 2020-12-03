// SP_laba2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SP_laba2.h"

#define MAX_LOADSTRING 100
#define ID_BUTTON_ADD 1
#define ID_BUTTON_CLEAR 2
#define ID_BUTTON_TORIGHT 3
#define ID_BUTTON_DELETE 4
#define ID_EDIT 5
#define ID_LISTBOX_LEFT 6
#define ID_LISTBOX_RIGHT 7

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
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

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPLABA2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLABA2));

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

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLABA2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLABA2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
bool isSelectedLeft = false, isSelectedRight = false, isUnique = true;
int counterLeft = 0, counterRight = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hBtnAdd, hBtnClear, hBtnToRight, hBtnDelete, hEdit, hListBoxLeft, hListBoxRight;
    WCHAR buf[1024], tempBuf[1024];
    int i = NULL;
    switch (message)
    {
        case WM_CREATE:
        {
            hListBoxLeft = CreateWindow(L"listbox", NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_EXTENDEDSEL,
                50, 50, 200, 800,
                hWnd, (HMENU)ID_LISTBOX_LEFT, hInst, NULL);
            ShowWindow(hListBoxLeft, SW_SHOWNORMAL);
            hListBoxRight = CreateWindow(L"listbox", NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                400, 50, 200, 800,
                hWnd, (HMENU)ID_LISTBOX_RIGHT, hInst, NULL);
            ShowWindow(hListBoxRight, SW_SHOWNORMAL);
            hEdit = CreateWindow(L"edit", NULL,
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                1100, 300, 300, 20,
                hWnd, (HMENU)ID_EDIT, hInst, NULL);
            ShowWindow(hEdit, SW_SHOWNORMAL);
            hBtnAdd = CreateWindow(L"button", L"Add",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                900, 600, 100, 30,
                hWnd, (HMENU)ID_BUTTON_ADD, hInst, NULL);
            ShowWindow(hBtnAdd, SW_SHOWNORMAL);
            hBtnClear = CreateWindow(L"button", L"Clear",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                1500, 600, 100, 30,
                hWnd, (HMENU)ID_BUTTON_CLEAR, hInst, NULL);
            ShowWindow(hBtnClear, SW_SHOWNORMAL);
            hBtnToRight = CreateWindow(L"button", L"ToRight",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                1100, 600, 100, 30,
                hWnd, (HMENU)ID_BUTTON_TORIGHT, hInst, NULL);
            ShowWindow(hBtnToRight, SW_SHOWNORMAL);
            hBtnDelete = CreateWindow(L"button", L"Delete",
                WS_CHILD | WS_VISIBLE | WS_BORDER,
                1300, 600, 100, 30,
                hWnd, (HMENU)ID_BUTTON_DELETE, hInst, NULL);
            ShowWindow(hBtnDelete, SW_SHOWNORMAL);
        }
        break;
        case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
                // Разобрать выбор в меню:
            switch (wmId)
            {
                case ID_BUTTON_CLEAR:
                {
                    for (int j = counterLeft - 1; j >= 0; j--)
                    {
                        SendMessage(hListBoxLeft, LB_DELETESTRING, j, 0);
                    }
                    for (int j = counterRight - 1; j >= 0; j--)
                    {
                        SendMessage(hListBoxRight, LB_DELETESTRING, j, 0);
                    }
                    counterLeft = 0;
                    counterRight = 0;
                }
                break;
                case ID_BUTTON_ADD:
                {
                    GetWindowText(hEdit, buf, lstrlen(buf));
                    for (int j = counterLeft - 1; j >= 0; j--)
                    {
                        SendMessage(hListBoxLeft, LB_GETTEXT, j, (LPARAM)tempBuf);
                        if (lstrcmp(buf ,tempBuf) == 0)
                        {
                            isUnique = false;
                            break;
                        }
                    }
                    if (lstrlen(buf) > 0 & isUnique)
                    {
                        SendMessage(hListBoxLeft, LB_ADDSTRING, 0, (LPARAM)buf);
                        UpdateWindow(hListBoxLeft);
                        counterLeft += 1;
                    }
                    SetWindowText(hEdit, NULL);
                    isUnique = true;
                }
                break;
                case ID_BUTTON_TORIGHT:
                {
                    if (isSelectedLeft)
                    {
                        i = SendMessage(hListBoxLeft, LB_GETCURSEL, 0, 0);
                        SendMessage(hListBoxLeft, LB_GETTEXT, i, (LPARAM)buf);
                        for (int j = counterRight - 1; j >= 0; j--)
                        {
                            SendMessage(hListBoxRight, LB_GETTEXT, j, (LPARAM)tempBuf);
                            if (lstrcmp(buf, tempBuf) == 0)
                            {
                                isUnique = false;
                                break;
                            }
                        }
                        if (isUnique)
                        {
                            SendMessage(hListBoxRight, LB_ADDSTRING, 0, (LPARAM)buf);
                            counterRight += 1;
                        }
                        isUnique = true;
                        isSelectedLeft = false;
                    }
                }
                break;
                case ID_BUTTON_DELETE:
                {
                    if (isSelectedLeft)
                    {
                        i = SendMessage(hListBoxLeft, LB_GETCURSEL, 0, 0);
                        SendMessage(hListBoxLeft, LB_DELETESTRING, i, 0);
                        counterLeft -= 1;
                        isSelectedLeft = false;
                    }
                    if (isSelectedRight)
                    {
                        i = SendMessage(hListBoxRight, LB_GETCURSEL, 0, 0);
                        SendMessage(hListBoxRight, LB_DELETESTRING, i, 0);
                        counterRight -= 1;
                        isSelectedRight = false;
                    }
                }
                break;
                case ID_LISTBOX_LEFT:
                {
                    isSelectedLeft = true;
                }
                break;
                case ID_LISTBOX_RIGHT:
                {
                    isSelectedRight = true;
                }
                break;
                case IDM_ABOUT:
                    DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
                // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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

// Обработчик сообщений для окна "О программе".
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

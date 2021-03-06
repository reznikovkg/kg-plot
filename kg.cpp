// kg.cpp: Определяет точку входа для приложения.
//

//other vars

#include "stdafx.h"

bool _GRID = true;
bool _AXES = true;
bool _NUMS = true;

#define MAX_LOADSTRING 100
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);




#define _USE_MATH_DEFINES
#include <cmath>

typedef double Cell;

double
X0 = 200,
Y0 = 200,
px = 50,
py = 50;


Cell x_start = -100;
Cell x_final = 100;

Cell x_step = 1.0;
Cell x_nums = (x_final - x_start) / x_step;

Cell f_1(Cell x) {
	return x*x;
}

Cell x_t(Cell t) {
	return cos(t);
}

Cell y_t(Cell t) {
	return sin(t);
}
#include "include/reznikovkg_3d.h"

Scene3D scene(X0, Y0, px, py, "V.txt", "Ver.txt");







int WINAPI wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_KG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KG));

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
//  НАЗНАЧЕНИЕ: регистрирует класс окна.
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_KG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100, 100, 1200, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);


   //Открыть дилоговое окно с запуском программы 
   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//


#include "include1/CallBack.h"
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
		case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			switch (wmId)
            {
				case IDM_TUNING:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_TUNINGBOX), 0, Tuning);
					break;
				}
				case IDM_REFRESH:
				{
					InvalidateRect(hWnd, nullptr, false);
					break;
				}
				case IDM_HELP:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_HELPBOX), 0, Help);
					break;
				}
				case IDM_ABOUT:
				{
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
					break;
				}
				case IDM_EXIT:
				{
					DestroyWindow(hWnd);
					break;
				}
				default: return DefWindowProc(hWnd, message, wParam, lParam);
            }
			break;
        }
		case WM_PAINT:
        {
			HDC dc = GetDC(hWnd);
			scene.Clear(dc);

			scene.Render(dc);

			ReleaseDC(hWnd, dc);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
			
        }
	case WM_SIZE:
	{
		HDC dc = GetDC(hWnd);
		scene.SetResolution(dc);
		ReleaseDC(hWnd, dc);
		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	break;
	case WM_MOUSEWHEEL:
	{
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);

		if (GET_WHEEL_DELTA_WPARAM(wParam)>0)
		{
			scene.sizeedit(1.1, P.x, P.y); //+++
		}
		else
		{
			scene.sizeedit(0.9, P.x, P.y); //---
		}

		InvalidateRect(hWnd, nullptr, false);
		return 0;
	}
	break;
	case WM_LBUTTONDOWN:
	{
		POINT P;
		P.x = GET_X_LPARAM(lParam);
		P.y = GET_Y_LPARAM(lParam);
		ScreenToClient(hWnd, &P);
		scene.StartDragging(P.x, P.y);
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (scene.IsDragging())
		{
			POINT P;
			P.x = GET_X_LPARAM(lParam);
			P.y = GET_Y_LPARAM(lParam);
			ScreenToClient(hWnd, &P);

			scene.Drag(P.x, P.y);
			InvalidateRect(hWnd, nullptr, false);
		}
		return 0;
	}
	break;
	case WM_LBUTTONUP:
	{
		scene.StopDragging();
		return 0;
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

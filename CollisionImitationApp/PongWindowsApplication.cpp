// PongWindowsApplication.cpp: Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "PongWindowsApplication.h"
#include "math.h"
#include "Actors.h"
#include "chrono"

#define MAX_LOADSTRING 100
#define MAIN_TIMER 1

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int rad = 40;
int anti_accel = 0.5;
const int actors_count = 4;

Actor actors[actors_count];

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void moveActors(HWND hWnd, long int _delta);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PONGWINDOWSAPPLICATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PONGWINDOWSAPPLICATION));

    MSG msg;
	long int delta;
	std::chrono::time_point<std::chrono::high_resolution_clock> prev_time = std::chrono::high_resolution_clock::now();
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } 
		delta = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - prev_time).count();
		prev_time = std::chrono::high_resolution_clock::now();
		moveActors(msg.hwnd, delta);
		
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PONGWINDOWSAPPLICATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PONGWINDOWSAPPLICATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   НАЗНАЧЕНИЕ: сохраняет обработку экземпляра и создает главное окно.
//
//   КОММЕНТАРИИ:
//
//        В данной функции дескриптор экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится на экран главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить дескриптор экземпляра в глобальной переменной

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
//  НАЗНАЧЕНИЕ:  обрабатывает сообщения в главном окне.
//
//  WM_COMMAND — обработать меню приложения
//  WM_PAINT — отрисовать главное окно
//  WM_DESTROY — отправить сообщение о выходе и вернуться
//
//
// For mouse-dragging:
double mb_offset_x = 0;
double mb_offset_y = 0;
Actor* act_pressed = NULL;

RECT rctW;
RECT rct;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE: {

		GetClientRect(hWnd, &rct);
		GetWindowRect(hWnd, &rctW);

		Actor::m_Rad = rad;
		actors[0] = Actor(100,100);
		actors[0].vec.x = 1000;
		actors[0].vec.y = 0;
		actors[1] = Actor(600,159);
		actors[1].vec.x = -750;
		actors[1].vec.y = -300;
		actors[2] = Actor(150,300);
		actors[2].vec.x = 0;
		actors[2].vec.y = -500;
		actors[3] = Actor(500, 400);
		actors[3].vec.x = 0;
		actors[3].vec.y = 450;

		SetTimer(hWnd, MAIN_TIMER, 1, NULL);
	} 
		break;
	case WM_TIMER: {
//		moveActors(hWnd);
		InvalidateRect(hWnd, NULL, true);
	}	break;
	case WM_LBUTTONDOWN: {
		for (int i = 0; i < actors_count; i++) {
			if ((actors[i].X - LOWORD(lParam)) * (actors[i].X - LOWORD(lParam)) + (actors[i].Y - HIWORD(lParam)) * (actors[i].Y - HIWORD(lParam)) <= rad * rad) {
				POINT pt;
				GetCursorPos(&pt);
				mb_offset_x = actors[i].X - pt.x;
				mb_offset_y = actors[i].Y - pt.y;
				act_pressed = &actors[i];
				break;
			}
		}
	} break;
	case WM_LBUTTONUP: {
		act_pressed = NULL;
		mb_offset_x = 0;
		mb_offset_y = 0;
	} break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		for (Actor a : actors) {
			Ellipse(hdc, a.X - rad, a.Y - rad, a.X + rad, a.Y + rad);
		}
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
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
    case WM_DESTROY:
        PostQuitMessage(0);
		KillTimer(hWnd, MAIN_TIMER);
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

void moveActors(HWND hWnd, long int _delta) {
	for (int i = 0; i < actors_count; i++) {

		// <Collisions detection>
		for (int j = i + 1; j < actors_count; j++) {
//			Actor moved_i = actors[i];
//			moved_i.move(moved_i.vec.x, moved_i.vec.y);
			if (Actor::touch(actors[i], actors[j])) {
				if (&actors[j] == act_pressed) {
					Actor temp(actors[j].X, actors[j].Y, (actors[i].vec * (-1)) + (actors[j].vec * (-1)));
					Actor::collide(actors[i], temp, false);
				}
				else if (&actors[i] == act_pressed) {
					Actor temp(actors[i].X, actors[i].Y, actors[i].vec + (actors[j].vec * (-1)));
					Actor::collide(temp, actors[j], true);
				}
				else {
					Actor::collide(actors[i], actors[j], false);
				}
			}
		}

		// Detecting wall_collisions;
		if (actors[i].X < 0 + rad) {
			actors[i].vec.reflect(true);
			actors[i].X = 0 + 1 + rad;
		}
		else if (actors[i].X > rct.right - rad) {
			actors[i].vec.reflect(true);
			actors[i].X = rct.right - 1 - rad;
		}
		if (actors[i].Y < 0 + rad) {
			actors[i].vec.reflect(false);
			actors[i].Y = 0 + 1 + rad;
		}
		else if (actors[i].Y > rct.bottom - rad) {
			actors[i].vec.reflect(false);
			actors[i].Y = rct.bottom - 1 - rad;
		}

		double delta_d = _delta * 1.0 / 1000000000;
		// Moving pressed actor (vector setup)
		if (&actors[i] == act_pressed) {
			POINT pt;
			GetCursorPos(&pt);
			act_pressed->vec.x = pt.x - act_pressed->X + mb_offset_x;
			act_pressed->vec.y = pt.y - act_pressed->Y + mb_offset_y;
			act_pressed->move(act_pressed->vec.x, act_pressed->vec.y);
			act_pressed->vectorUpdate(act_pressed->vec.x * pow(delta_d, -1), act_pressed->vec.y * pow(delta_d, -1));
		}
		else {

			// Moving all actors
			
			actors[i].move(actors[i].vec.x * delta_d, actors[i].vec.y * delta_d);
			//actors[i].move(actors[i].vec.x, actors[i].vec.y);
		}
	}
}
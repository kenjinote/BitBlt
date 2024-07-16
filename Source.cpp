#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>
#include "resource.h"

TCHAR szClassName[] = TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap;
	switch (msg)
	{
	case WM_CREATE:
		hBitmap = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
		break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			HDC hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hBitmap);
			BITMAP bm;
			GetObject(hBitmap, sizeof(bm), &bm);

			RECT rect;
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));

			TextOut(hdc, 0, 0, L"SRCCOPY", 7);
			SetRect(&rect, 16, 32, 16 + bm.bmWidth, 32 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 32, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);

			TextOut(hdc, 0, 64, L"SRCAND", 6);
			SetRect(&rect, 16, 96, 16 + bm.bmWidth, 96 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 96, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCAND);

			TextOut(hdc, 0, 128, L"SRCPAINT", 8);
			SetRect(&rect, 16, 160, 16 + bm.bmWidth, 160 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 160, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCPAINT);

			TextOut(hdc, 0, 192, L"SRCINVERT", 9);
			SetRect(&rect, 16, 224, 16 + bm.bmWidth, 224 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 224, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCINVERT);

			TextOut(hdc, 0, 256, L"SRCERASE", 8);
			SetRect(&rect, 16, 288, 16 + bm.bmWidth, 288 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 288, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCERASE);

			TextOut(hdc, 0, 320, L"NOTSRCCOPY", 10);
			SetRect(&rect, 16, 352, 16 + bm.bmWidth, 352 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 352, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, NOTSRCCOPY);

			TextOut(hdc, 0, 384, L"NOTSRCERASE", 11);
			SetRect(&rect, 16, 416, 16 + bm.bmWidth, 416 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 416, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, NOTSRCERASE);

			TextOut(hdc, 0, 448, L"MERGECOPY", 9);
			SetRect(&rect, 16, 480, 16 + bm.bmWidth, 480 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 480, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, MERGECOPY);

			TextOut(hdc, 0, 512, L"MERGEPAINT", 10);
			SetRect(&rect, 16, 544, 16 + bm.bmWidth, 544 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 544, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, MERGEPAINT);

			TextOut(hdc, 0, 576, L"WHITENESS", 9);
			SetRect(&rect, 16, 608, 16 + bm.bmWidth, 608 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 608, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, WHITENESS);

			TextOut(hdc, 0, 640, L"BLACKNESS", 9);
			SetRect(&rect, 16, 672, 16 + bm.bmWidth, 672 + bm.bmHeight);
			FillRect(hdc, &rect, hBrush);
			BitBlt(hdc, 16, 672, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, BLACKNESS);

			DeleteObject(hBrush);

			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		DeleteObject(hBitmap);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPreInst, LPWSTR pCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASS wndclass = {
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		0,
		LoadCursor(0,IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		0,
		szClassName
	};
	RegisterClass(&wndclass);
	HWND hWnd = CreateWindowW(
		szClassName,
		L"Window",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		0,
		0,
		hInstance,
		0
	);
	ShowWindow(hWnd, SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

#include <Windows.h>
#include <winuser.h>
#include <wingdi.h>

boolean isDown, vkShift, vkUpX, vkUpY, moveX, moveY;
POINT p;
RECT clientRect;
/*
			vertical.x

horizont.y				horizont.x

			vertical.y
*/
POINT horizont = {0,0};
POINT vertical = {0,0};

int vSpeedHor = 0;
int vSpeedVer = 0;

int rSpeed = 0;
int maxSpeed = 50;
int i;

HBITMAP hBitmap = NULL;
HINSTANCE		hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{

	case WM_CREATE:
	{
		hBitmap = (HBITMAP)LoadImage(hInst, L"G:\\Ћабы\\5 сем\\OSiSP\\WimApppp\\him.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		return 0;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT     ps;
		HDC             hdc = BeginPaint(hwnd, &ps);
		HDC				hdcMem;
		RECT			rect;
		BITMAP			bitmap;
		HGDIOBJ			oldBitmap;
		
		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, horizont.y, vertical.x, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		/*rect.left = horizont.y;
		rect.right = horizont.y + 100;
		rect.top = vertical.x;
		rect.bottom = vertical.y + 100;
		
		FillRect(hdc, &rect, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));*/

		EndPaint(hwnd, &ps);
	}
	return 0;


	case WM_MOUSEWHEEL:
	{
		int	zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		if (vkShift)
		{
			if (zDelta < 0)
			{
				horizont.x++;
				horizont.y++;
			}
			else
			{
				horizont.x--;
				horizont.y--;
			}
		}
		else if (zDelta< 0)
		{
			vertical.y++;
			vertical.x++;
		}
		else
		{
			vertical.y--;
			vertical.x--;
		}
	RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
	return 0;
	case WM_KEYUP:
	{
		switch (wParam)
		{
		case VK_SHIFT:
			vkShift = false;
			vkUpX = true;
			return 0;
		case VK_RIGHT:
			vSpeedHor = 0;
			vkUpX = true;
			vkUpY = false;
			GetClientRect(hwnd, &clientRect);
			if (horizont.x  > clientRect.right - 100) {
				horizont.x = clientRect.right - 100;
				horizont.y = horizont.x ;
			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_LEFT:
			vSpeedHor = 0;
			vkUpX = true;
			vkUpY = false;
			GetClientRect(hwnd, &clientRect);
			if (horizont.y < clientRect.left) {
				horizont.y = clientRect.left;
				horizont.x = horizont.y ;
			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_UP:
			vSpeedVer = 0;
			vkUpX = false;
			vkUpY = true;
			GetClientRect(hwnd, &clientRect);
			if (vertical.x < clientRect.top) {
				vertical.x = clientRect.top;
				vertical.y = vertical.x ;
			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_DOWN:
			vSpeedVer = 0;
			vkUpX = false;
			vkUpY = true;
			GetClientRect(hwnd, &clientRect);
			if (vertical.y > clientRect.bottom - 100) {
				vertical.y = clientRect.bottom - 100;
				vertical.x = vertical.y ;
			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		}
	}
	return 0;

	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SHIFT:
			vkShift = true;
			vkUpX = false;
			return 0;
		case VK_RIGHT:
			vkUpX = false;
			horizont.x++;
			horizont.y++;
			vSpeedHor++;
			rSpeed++;
			horizont.x = horizont.x + (vSpeedHor * 2) +rSpeed;
			horizont.y = horizont.y + (vSpeedHor * 2) +rSpeed;
			GetClientRect(hwnd, &clientRect);
			if (horizont.x >= clientRect.right)
			{
				vSpeedHor = vSpeedHor * (-1);
				horizont.x = clientRect.right;
				horizont.y = horizont.x;
				horizont.x = horizont.x + (vSpeedHor * 2);
				horizont.y = horizont.y + (vSpeedHor * 2);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
				
			}
			 RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_LEFT:
			vkUpX = false;
			horizont.x--;
			horizont.y--;
			vSpeedHor--;
			rSpeed--;
			horizont.x = horizont.x + (vSpeedHor * 2) + rSpeed;
			horizont.y = horizont.y + (vSpeedHor * 2) + rSpeed;
			GetClientRect(hwnd, &clientRect);
			if (horizont.y <= clientRect.left)
			{
				vSpeedHor = vSpeedHor * (-1);
				horizont.y = clientRect.left;
				horizont.x = horizont.y;
				horizont.x = horizont.x + (vSpeedHor * 2);
				horizont.y = horizont.y + (vSpeedHor * 2);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_UP:
			vkUpY = false;
			vertical.y--;
			vertical.x--;
			vSpeedVer--;
			rSpeed--;
			vertical.x = vertical.x + (vSpeedVer * 2) + rSpeed;
			vertical.y = vertical.y + (vSpeedVer * 2) + rSpeed;
			GetClientRect(hwnd, &clientRect);
			if (vertical.x <= clientRect.top)
			{
				vSpeedVer = vSpeedVer * (-1);
				vertical.x = clientRect.top;
				vertical.y = vertical.x;
				vertical.x = vertical.x + (vSpeedVer * 2);
				vertical.y = vertical.y + (vSpeedVer * 2);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_DOWN:
			vkUpY = false;
			vertical.y++;
			vertical.x++;
			vSpeedVer++;
			rSpeed++;
			vertical.x = vertical.x + (vSpeedVer * 2) + rSpeed;
			vertical.y = vertical.y + (vSpeedVer * 2) + rSpeed;
			GetClientRect(hwnd, &clientRect);
			if (vertical.y >= clientRect.bottom)
			{
				vSpeedVer = vSpeedVer * (-1);
				vertical.y = clientRect.bottom;
				vertical.x = vertical.y;
				vertical.x = vertical.x + (vSpeedVer * 2);
				vertical.y = vertical.y + (vSpeedVer * 2);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

			}
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);//change to invalidate rect&&&&
			return 0;
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (isDown)
		{
			GetCursorPos(&p);

			horizont.y = horizont.x;
			vertical.x = vertical.y;
			horizont.x = p.x-50;
			vertical.y = p.y-75;
		
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
		}
	}
	return 0;

	case WM_LBUTTONDOWN:
	{									
		ScreenToClient(hwnd, &p);
		if (p.x <= horizont.x+80 && p.x >= horizont.x - 200)
		{
			if (p.y <= vertical.y+80 && p.y >= vertical.y - 200)
			{
				isDown = true;
			}
		}

	}
	return 0;

	case WM_LBUTTONUP:
	{
		isDown = false;
	}
	return 0;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
			if ((rSpeed > 0) && vkUpX)	
			{
				rSpeed--;
				horizont.x = horizont.x + rSpeed;
				horizont.y = horizont.y + rSpeed;
				
				if (horizont.x + 100 >= clientRect.right)
					rSpeed = rSpeed * (-1);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			}
			if ((rSpeed < 0) && vkUpX)
			{
				rSpeed++;
				horizont.x = horizont.x + rSpeed;
				horizont.y = horizont.y + rSpeed;
				if (horizont.y <= clientRect.left)
					rSpeed = rSpeed * (-1);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			}
			if ((rSpeed > 0) && vkUpY)
			{
				rSpeed--;
				vertical.x = vertical.x + rSpeed;
				vertical.y = vertical.y + rSpeed;

				if (vertical.y + 100 >= clientRect.bottom)
					rSpeed = rSpeed * (-1);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			}
			if ((rSpeed < 0) && vkUpY)
			{
				rSpeed++;
				vertical.x = vertical.x + rSpeed;
				vertical.y = vertical.y + rSpeed;
				if (vertical.x <= clientRect.top)
					rSpeed = rSpeed * (-1);
				RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			}
			return 0;
		}
	}

	case WM_DESTROY:
	{
		KillTimer(hwnd,1);
		DeleteObject(hBitmap);
		PostQuitMessage(EXIT_SUCCESS);
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int CALLBACK wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR szCmdLine, int nCmdShow)
{
	MSG msg{};
	HWND hwnd{};
	WNDCLASSEX wc{sizeof(WNDCLASSEX)};
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	
	wc.lpszClassName = L"MyAppClass";
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return EXIT_FAILURE;

	hwnd = CreateWindow(wc.lpszClassName, L"YuriEnt.", WS_OVERLAPPEDWINDOW, 0, 0, 1500, 800, nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	SetTimer(hwnd,1,50,NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}





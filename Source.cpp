#include <Windows.h>
#include <winuser.h>
#include <wingdi.h>


boolean isDown,vkShift;
POINT p;
RECT clientRect;
struct
{
	int x, y;
	int z, w;
} pos = { 0 };

int vSpeedx = 0;
int vSpeedy = 0;
int vSpeedz = 0;
int vSpeedw = 0;
int maxSpeed = 50;
int i;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
		SetTimer(hwnd,1,100,nullptr);
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT     ps;
		HDC             hdc = BeginPaint(hwnd, &ps);
		RECT rect;
		
		rect.left = pos.w;
		rect.right = pos.x + 100;
		rect.top = pos.y;
		rect.bottom = pos.z + 100;
		
		FillRect(hdc, &rect, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));

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
				pos.x++;
				pos.w++;
			}
			else
			{
				pos.x--;
				pos.w--;
			}
		}
		else if (zDelta< 0)
		{
			pos.y++;
			pos.z++;
		}
		else
		{
			pos.y--;
			pos.z--;
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
			return 0;
		case VK_RIGHT:
			vSpeedx = 0;
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_LEFT:
			vSpeedw = 0;
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_UP:
			vSpeedz = 0;
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_DOWN:
			vSpeedy = 0;
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
			return 0;
		case VK_RIGHT:
			pos.x++;
			pos.w++;
			vSpeedx++;
			pos.x = pos.x + (vSpeedx * 2);
			pos.w = pos.w + (vSpeedx * 2);

			GetClientRect(hwnd, &clientRect);
			if (pos.x+100 >= clientRect.right)
			{
				for (i = 0;i < 15;i++)
				{
					//Sleep(10);
					pos.x--;
					pos.w--;
					vSpeedw++;
					//vSpeedx--;
					pos.x = pos.x - (vSpeedw * 2);
					pos.w = pos.w - (vSpeedw * 2);
					RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
				}
			}
			 RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_LEFT:
			pos.x--;
			pos.w--;
			vSpeedw++;
			pos.x = pos.x - (vSpeedw * 2);
			pos.w = pos.w - (vSpeedw * 2);
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_UP:
			pos.y--;
			pos.z--;
			vSpeedz++;
			pos.y = pos.y - (vSpeedz * 2);
			pos.z = pos.z - (vSpeedz * 2);
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		case VK_DOWN:
			pos.y++;
			pos.z++;
			vSpeedy++;
			pos.y = pos.y + (vSpeedy * 2);
			pos.z = pos.z + (vSpeedy * 2);
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			return 0;
		}
	}
	return 0;

	case WM_MOUSEMOVE:
	{
		if (isDown)
		{
			GetCursorPos(&p);

			pos.w = pos.x;
			pos.z = pos.y;
			pos.x = p.x-50;
			pos.y = p.y-75;
		
			RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
		}
	}
	return 0;

	case WM_LBUTTONDOWN:
	{
		ScreenToClient(hwnd, &p);
		if (p.x <= pos.x+80 && p.x >= pos.x - 200)
		{
			if (p.y <= pos.y+80 && p.y >= pos.y - 200)
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


	case WM_DESTROY:
	{
		KillTimer(hwnd,1);
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

	hwnd = CreateWindow(wc.lpszClassName, L"YuriEnt.", WS_OVERLAPPEDWINDOW, 0, 0, 600, 600, nullptr, nullptr, wc.hInstance, nullptr);
	if (hwnd == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}

	return msg.wParam;
}





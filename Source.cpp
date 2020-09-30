#include <Windows.h>
#include <winuser.h>
#include <wingdi.h>

boolean isDown,vkShift;
POINT p;
struct
{
	int x, y;
	int z, w;
} pos = { 0};
int vSpeedx = 0;
int vSpeedy = 0;
int vSpeedz = 0;
int vSpeedw = 0;
int maxSpeed = 50;

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{
	//	PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hwnd, &ps);
		//GetClientRect(hwnd,);
     	//RECT rect;
	//	rect.left = 0;
		//rect.right = ;
	//	rect.top = 0;
	//	rect.bottom = 10000;
		//FillRect(hdc, &rect, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
		//HPEN newPen = CreatePen(PS_SOLID, 5, RGB(0,0,255));
	//	HGDIOBJ oldPen = SelectObject(hdc, newPen);
	//	Rectangle(hdc, 0,100,0,100);
	//	SelectObject(hdc, oldPen);
	//	DeleteObject(newPen);
	//	EndPaint(hwnd, &ps);
		//BOOL Rectangle(HDC hdc,int left,int top,int right,int bottom);
		//hBitmap = (HBITMAP)LoadImage(GetModuleHandle(nullptr),L"g:\\Ћабы\\5 сем\\OSiSP\\WimApppp\\him.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT     ps;
		HDC             hdc = BeginPaint(hwnd, &ps);;
		RECT rect;
		//BITMAP          bitmap;
		//HDC             hdcMem;
	//	HGDIOBJ         oldBitmap;
	//	GetClientRect(hwnd,&rect);
		
		
		rect.left = pos.w;
		rect.right = pos.x + 100;
		rect.top = pos.y;
		rect.bottom = pos.z + 100;
	//	rect.top = pos.z + 100;
	//	rect.bottom = pos.y;
		FillRect(hdc, &rect, reinterpret_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
		//hdc = BeginPaint(hwnd, &ps);
	//	rect.left = pos.w;
	//	rect.right = pos.x + 100;
	//	rect.top = pos.y;
	//	rect.bottom = pos.z + 100;
	//	FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));
		//hdcMem = CreateCompatibleDC(hdc);
		//oldBitmap = SelectObject(hdcMem, hBitmap);

		//GetObject(hBitmap, sizeof(bitmap), &bitmap);

	//	BitBlt(hdc, pos.x, pos.y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

		//SelectObject(hdcMem, oldBitmap);
		//DeleteDC(hdcMem);

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
			//	if (GetCapture())
		{
			//ScreenToClient(hwnd, &p);
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
		//GetCursorPos(&p);
		ScreenToClient(hwnd, &p);
		//if (p.x >= pos.x && p.x <= pos.x + 200)// hBitmap.width)
		if (p.x <= pos.x+80 && p.x >= pos.x - 200)
		{
			//check if the cursor is within the image.y limits
		//	if (p.y <= pos.y && p.y >= pos.y + 200)//g_carInfo.height)
			if (p.y <= pos.y+80 && p.y >= pos.y - 200)//magic numbers try to change to image width and length
			{
				//SetCapture(hwnd);
				isDown = true;
			}
		}

	}
	return 0;

	case WM_LBUTTONUP:
	{
		//ReleaseCapture();
		isDown = false;
	}
	return 0;


	case WM_DESTROY:
	{
		//DeleteObject(hBitmap);
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

	return static_cast<int>(msg.wParam);

}





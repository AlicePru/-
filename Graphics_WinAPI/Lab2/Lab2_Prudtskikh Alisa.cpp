#include <windows.h>
LONG WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
int x = 0, y = 0;
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
	
{
	
	HWND hwnd;
	MSG msg;
	WNDCLASS w;
	memset(&w, 0, sizeof(WNDCLASS));//�������� ��������� ,���� � ����� ���� ������� ������ �� ��� ��������� � ��� ����� �������� �����. 
	w.style = CS_HREDRAW | CS_VREDRAW;
	w.lpfnWndProc = WndProc;//��������� �� ������� ���������.������� ��������� -�-� �������������� ��������� ����.
	w.hInstance = hInstance;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.lpszClassName = L"My Class";
	w.hCursor = LoadCursor(NULL, IDC_ARROW);
	RegisterClass(&w);
	hwnd = CreateWindow(L"My Class", L"My title", WS_OVERLAPPEDWINDOW,
		500, 300, 300, 280, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}
LONG WINAPI WndProc(HWND hwnd, UINT Message, WPARAM wparam, LPARAM lparam)
{
	HDC hdc;//����� �� �������� ���������� .�������� ���������� ��� ���������� ���������� �������.������ � ���� ������� ����� ��� �����,��������� ����,�����,����� ����.
	WORD t;
	TCHAR buff[100];
	//int x, y;
	switch (Message) {
		case WM_LBUTTONDOWN:
			x = LOWORD(lparam);//������� ����������� ����������� ������ �� ������.������-������ ���������� ������ �� ������
			y = HIWORD(lparam);//
			hdc = GetDC(hwnd);
			SetTextColor(hdc, RGB(0, 255, 127));
			t = wsprintf(buff, L"Coordinates of cursor %d, %d ", x, y);
			TextOut(hdc, x, y, buff, t);
			ReleaseDC(hwnd, hdc);
			break;

	case WM_RBUTTONDOWN:
		x = LOWORD(lparam);
		y = HIWORD(lparam);
		break;

	case WM_RBUTTONUP:
		
		int nXEnd, nYEnd;
		nXEnd = LOWORD(lparam);
		nYEnd = HIWORD(lparam);
		hdc = GetDC(hwnd);
		SelectObject(hdc, CreatePen(PS_COSMETIC, 5, RGB(238, 99, 99)));
		MoveToEx(hdc, x, y, NULL);
		LineTo(hdc, nXEnd, nYEnd);
		ReleaseDC(hwnd,hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);//�������� ��������� � �������� �������������� ������� ���������� � ��������� �� ���������
		break;
	default:
		return DefWindowProc(hwnd, Message, wparam, lparam);//���� ��� ������������ ��� ����� ���� ���������,�� ��� ������������ � ���. ����������� ����������� ��
	}
	return 0;
}

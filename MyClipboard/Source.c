#include <Windows.h>
#include <stdio.h>
#define size_buffer 128






int WINAPI WinMain(HINSTANCE hlnstance, // ����������, ������������� ����������� ����������

    HINSTANCE hPrevInstance, // ��� ������������� � winl6. � Win32 �� ������������

    LPSTR lpCmdLine, // ��������� �� ��������� ������, ���� ���������� ��� ��������

    int nCmdShow) // ��������, ������� ����� ���� �������� � ������� Show Window ()

{
    //ClipboardInputText(L"�� ��, �������??!!");
    ClipboardGetText();
    return 0;
}



int ClipboardInputText(LPWSTR buffer)//�������� ������ � ��������� �����

{
    DWORD len;//����� ���������
    HANDLE hMem;//���������� ���������� ������� ������
    len = wcslen(buffer) + 1; // ����������� ����� ������ � ������� �������  
    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR)); //��������� ������ � ���������� ������� ���������    
    memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR));// ����������� ������� ������ �� buffer � hMem
    GlobalUnlock(hMem); //�������������� ���������� ���� ������ (������� ��������� ��� ������ ��������)
    OpenClipboard(0);//������� ����� ������
    EmptyClipboard();//�������� ����� ������
    SetClipboardData(CF_UNICODETEXT, hMem);//�������� � ����� ������ ������ ���������������� ����
    CloseClipboard();//������� ����� ������, ������� ��� ��������� ��� ������ ����������    
    return 0;
}
int ClipboardGetText()
{
    LPWSTR tempData = L"Hello";
    while (TRUE)
    {
       
        OpenClipboard(0);
        LPWSTR data = (LPWSTR)GetClipboardData(CF_UNICODETEXT);
        if (wcscmp(data,tempData)!=0)
        {
            tempData = data;
            MessageBoxW(NULL, data, L"����� � ������))", MB_ICONINFORMATION | MB_OK);
        }
        CloseClipboard();
        Sleep(100);
    }
    
}
#include <Windows.h>
#include <stdio.h>
#define size_buffer 128






int WINAPI WinMain(HINSTANCE hlnstance, // дескриптор, присваиваемый запущенному приложению

    HINSTANCE hPrevInstance, // для совместимости с winl6. в Win32 не используется

    LPSTR lpCmdLine, // указатель на командною строку, если приложение так запущено

    int nCmdShow) // значение, которое может быть передано в функцию Show Window ()

{
    //ClipboardInputText(L"Ты шо, дурачёк??!!");
    ClipboardGetText();
    return 0;
}



int ClipboardInputText(LPWSTR buffer)//записать строку в системный буфер

{
    DWORD len;//длина сообщения
    HANDLE hMem;//дескриптор глобальной области памяти
    len = wcslen(buffer) + 1; // определение длины строки в формате юникода  
    hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(LPWSTR)); //выделение памяти в глобальной области видимости    
    memcpy(GlobalLock(hMem), buffer, len * sizeof(LPWSTR));// копирование области памяти из buffer в hMem
    GlobalUnlock(hMem); //разблокировать содержимое этой памяти (сделать доступным для других программ)
    OpenClipboard(0);//открыть буфер обмена
    EmptyClipboard();//очистить буфер обмена
    SetClipboardData(CF_UNICODETEXT, hMem);//записать в буфер обмена данные соответствующего типа
    CloseClipboard();//закрыть буфер обмена, сделать его доступным для других приложений    
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
            MessageBoxW(NULL, data, L"Нашел в буфере))", MB_ICONINFORMATION | MB_OK);
        }
        CloseClipboard();
        Sleep(100);
    }
    
}
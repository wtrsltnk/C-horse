// GT_HelloWorldWin32.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <Scintilla.h>
#include <SciLexer.h>

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("win32app");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Win32 Guided Tour Application");

HINSTANCE hInst;
HWND hEditor;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int CALLBACK WinMain(_In_ HINSTANCE hInstance, _In_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Scintilla_RegisterClasses(hInstance);
    Scintilla_LinkLexers();

    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Win32 Guided Tour"),
            MB_OK);

        return 1;
    }

    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindow(
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        600, 400,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Win32 Guided Tour"),
            MB_OK);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT SendEditor(UINT Msg, WPARAM wParam=0, LPARAM lParam=0) {
    return ::SendMessage(hEditor, Msg, wParam, lParam);
}

void SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char *face) {
    SendEditor(SCI_STYLESETFORE, style, fore);
    SendEditor(SCI_STYLESETBACK, style, back);
    if (size >= 1)
        SendEditor(SCI_STYLESETSIZE, style, size);
    if (face)
        SendEditor(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
}

const COLORREF black = RGB(0,0,0);
const COLORREF white = RGB(0xff,0xff,0xff);

const char cppKeywords[] =
        "alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept"
        "auto bitand bitor bool break case catch char char16_t char32_t class compl"
        "concept const constexpr const_cast continue decltype default delete do double"
        "dynamic_cast else enum explicit export extern false float for friend goto"
        "if import inline int long module mutable namespace new noexcept not not_eq"
        "nullptr operator or or_eq private protected public register reinterpret_cast"
        "requires return short signed sizeof static static_assert static_cast struct"
        "switch synchronized template this thread_local throw true try typedef typeid"
        "typename union unsigned using virtual void volatile wchar_t while xor xor_eq";

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        hEditor = CreateWindowW(
                    _T("Scintilla"),
                    _T("Source"),
                    WS_CHILD | WS_VSCROLL | WS_HSCROLL | WS_CLIPCHILDREN,
                    0, 0,
                    500, 100,
                    hWnd,
                    0,
                    hInst,
                    0);
        ShowWindow(hEditor, SW_SHOW);
        SetFocus(hEditor);

        SetAStyle(STYLE_DEFAULT, black, white, 11, "Courier new");
        SendEditor(SCI_SETLEXER, SCLEX_CPP);
        SendEditor(SCI_SETTABWIDTH, 4, 0);

        // set the forground color for some styles
        SendEditor(SCI_STYLESETFORE, SCE_C_STRING, RGB(55, 155, 55));
        SendEditor(SCI_STYLESETFORE, SCE_C_WORD, RGB(55, 55, 255));
        SendEditor(SCI_STYLESETFORE, SCE_C_WORD2, RGB(55, 55, 255));
        SendEditor(SCI_STYLESETFORE, SCE_C_IDENTIFIER, RGB(0, 0, 0));
        SendEditor(SCI_STYLESETFORE, SCE_C_UUID, RGB(255, 0, 0));

        SendEditor(SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>(cppKeywords));

        int nWidth = SendEditor(SCI_TEXTWIDTH, STYLE_LINENUMBER, (long)_T("9"));
        SendEditor(SCI_SETMARGINWIDTHN, 0, 4 * (nWidth + 4));
    }
    case WM_SIZE:
    {
        if (wParam != 1)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);
            SetWindowPos(hEditor, 0, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, 0);
        }
        break;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }
    default:
    {
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    }

    return 0;
}

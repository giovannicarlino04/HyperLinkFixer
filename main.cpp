#include <windows.h>
#include <string>
#include <algorithm>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddControls(HWND);
void ReplaceSpaces(HWND);
void CopyText(HWND);

HWND hTextBoxInput, hTextBoxOutput, hButtonFix, hButtonCopy;

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"HyperlinkFixer";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClass(&wc))
        return -1;

    CreateWindow(L"HyperlinkFixer", L"Hyperlink Fixer", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 400, 200, NULL, NULL, hInstance, NULL);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_COMMAND:
        switch (wp)
        {
        case 1:
            ReplaceSpaces(hWnd);
            break;
        case 2:
            CopyText(hWnd);
            break;
        }
        break;
    case WM_CREATE:
        AddControls(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
    }
    return 0;
}

void AddControls(HWND hWnd)
{
    hTextBoxInput = CreateWindow(L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
        20, 20, 350, 20, hWnd, NULL, NULL, NULL);

    hTextBoxOutput = CreateWindow(L"EDIT", L"",
        WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_READONLY,
        20, 60, 350, 20, hWnd, NULL, NULL, NULL);

    hButtonFix = CreateWindow(L"BUTTON", L"Fix Hyperlink",
        WS_VISIBLE | WS_CHILD,
        20, 100, 150, 30, hWnd, (HMENU)1, NULL, NULL);

    hButtonCopy = CreateWindow(L"BUTTON", L"Copy to Clipboard",
        WS_VISIBLE | WS_CHILD,
        220, 100, 150, 30, hWnd, (HMENU)2, NULL, NULL);
}void ReplaceSpaces(HWND hWnd)
{
    wchar_t inputText[256];
    GetWindowText(hTextBoxInput, inputText, 256);

    std::wstring text = inputText;
    std::wstring result;

    for (const auto& ch : text)
    {
        switch (ch)
        {
            case L' ':
                result += L"%20";
                break;
            case L'!':
                result += L"%21";
                break;
            case L'"':
                result += L"%22";
                break;
            case L'#':
                result += L"%23";
                break;
            case L'$':
                result += L"%24";
                break;
            case L'%':
                result += L"%25";
                break;
            case L'&':
                result += L"%26";
                break;
            case L'\'':
                result += L"%27";
                break;
            case L'(':
                result += L"%28";
                break;
            case L')':
                result += L"%29";
                break;
            case L'*':
                result += L"%2A";
                break;
            case L'+':
                result += L"%2B";
                break;
            case L',':
                result += L"%2C";
                break;
            case L'/':
                result += L"%2F";
                break;
            case L':':
                result += L"%3A";
                break;
            case L';':
                result += L"%3B";
                break;
            case L'<':
                result += L"%3C";
                break;
            case L'=':
                result += L"%3D";
                break;
            case L'>':
                result += L"%3E";
                break;
            case L'?':
                result += L"%3F";
                break;
            case L'@':
                result += L"%40";
                break;
            case L'[':
                result += L"%5B";
                break;
            case L'\\':
                result += L"%5C";
                break;
            case L']':
                result += L"%5D";
                break;
            case L'^':
                result += L"%5E";
                break;
            case L'_':
                result += L"%5F";
                break;
            case L'`':
                result += L"%60";
                break;
            case L'{':
                result += L"%7B";
                break;
            case L'|':
                result += L"%7C";
                break;
            case L'}':
                result += L"%7D";
                break;
            case L'~':
                result += L"%7E";
                break;
            default:
                result += ch;
                break;
        }
    }

    SetWindowText(hTextBoxOutput, result.c_str());
}


void CopyText(HWND hWnd)
{
    wchar_t outputText[256];
    GetWindowText(hTextBoxOutput, outputText, 256);

    const size_t len = wcslen(outputText) + 1;
    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len * sizeof(wchar_t));
    memcpy(GlobalLock(hMem), outputText, len * sizeof(wchar_t));
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_UNICODETEXT, hMem);
    CloseClipboard();
}

// Calculator.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <commctrl.h>

static TCHAR szWindowClass[] = _T("Calculator");
static TCHAR szTitle[] = _T("Five-Function Calculator");

HINSTANCE hInst;

void OnButtonClick(LPARAM lParam);
std::wstring removeTrailingZeros(std::wstring build);

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


HWND traceDisplay;
HWND calcDisplay;
HWND button0;
HWND button1;
HWND button2;
HWND button3;
HWND button4;
HWND button5;
HWND button6;
HWND button7;
HWND button8;
HWND button9;
HWND buttonPlus;
HWND buttonNeg;
HWND buttonMult;
HWND buttonDiv;
HWND buttonPercent;
HWND buttonC;
HWND buttonCE;
HWND buttonEq;
HWND buttonDec;

HWND tabControl;



int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Five Function Calculator"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        375, 450,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Five Function Calculator"),
            NULL);

        return 1;
    }

    // Create tab control
    tabControl = CreateWindow(WC_TABCONTROL, L"", WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | TCS_FIXEDWIDTH,
        0, 0, 355, 450, hWnd, NULL, hInstance, NULL);

    // Create pages
    TCITEM tie;
    tie.mask = TCIF_TEXT;

    tie.pszText = const_cast<LPWSTR>(L"Calculator");
    TabCtrl_InsertItem(tabControl, 0, &tie);

    tie.pszText = const_cast<LPWSTR>(L"Trace Logic");
    TabCtrl_InsertItem(tabControl, 1, &tie);
    


    // Create the display
    calcDisplay = CreateWindow(
        L"EDIT",                             
        L"",                                 
        WS_VISIBLE | WS_BORDER | WS_CHILD | ES_READONLY | ES_RIGHT,
        25, 50, 305, 75,                   
        hWnd,
        NULL,                               
        hInstance,
        NULL                               
    );

    HFONT hFont = CreateFont(75, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
    SendMessage(calcDisplay, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

    //create display for tracing
    traceDisplay = CreateWindow(
        L"EDIT", 
        L"", 
        WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | WS_VSCROLL | ES_READONLY,
        15, 40, 325, 350, 
        hWnd, 
        NULL, 
        hInstance, 
        NULL);

    hFont = CreateFont(15, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"));
    SendMessage(traceDisplay, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(TRUE, 0));

    // Create 7 button
    button7 = CreateWindow(
        L"BUTTON",           
        L"7",         
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 
        25, 150, 50, 50,    
        hWnd,
        NULL,
        hInstance,
        NULL                
    );

    // Create 8 button
    button8 = CreateWindow(
        L"BUTTON",
        L"8",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        85, 150, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 9 button
    button9 = CreateWindow(
        L"BUTTON",
        L"9",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        145, 150, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create C button
    buttonC = CreateWindow(
        L"BUTTON",
        L"C",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        225, 150, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create CE button
    buttonCE = CreateWindow(
        L"BUTTON",
        L"CE",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        285, 150, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 4 button
    button4 = CreateWindow(
        L"BUTTON",
        L"4",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        25, 210, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 5 button
    button5 = CreateWindow(
        L"BUTTON",
        L"5",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        85, 210, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 6 button
    button6 = CreateWindow(
        L"BUTTON",
        L"6",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        145, 210, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create + button
    buttonPlus = CreateWindow(
        L"BUTTON",
        L"+",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        225, 210, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create - button
    buttonNeg = CreateWindow(
        L"BUTTON",
        L"-",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        285, 210, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 1 button
    button1 = CreateWindow(
        L"BUTTON",
        L"1",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        25, 270, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 2 button
    button2 = CreateWindow(
        L"BUTTON",
        L"2",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        85, 270, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 3 button
    button3 = CreateWindow(
        L"BUTTON",
        L"3",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        145, 270, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create * button
    buttonMult = CreateWindow(
        L"BUTTON",
        L"*",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        225, 270, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create / button
    buttonDiv = CreateWindow(
        L"BUTTON",
        L"/",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        285, 270, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create 0 button
    button0 = CreateWindow(
        L"BUTTON",
        L"0",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        25, 330, 110, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create decimal button
    buttonDec = CreateWindow(
        L"BUTTON",
        L".",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        145, 330, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create = button
    buttonEq = CreateWindow(
        L"BUTTON",
        L"=",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        225, 330, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );

    // Create % button
    buttonPercent = CreateWindow(
        L"BUTTON",
        L"%",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        285, 330, 50, 50,
        hWnd,
        NULL,
        hInstance,
        NULL
    );


    ShowWindow(traceDisplay, SW_HIDE);
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_NOTIFY:
        if (((LPNMHDR)lParam)->code == TCN_SELCHANGE) {
            int tab = TabCtrl_GetCurSel(tabControl);
            switch (tab) {
            case 0:
                ShowWindow(button0, SW_SHOW);
                ShowWindow(button1, SW_SHOW);
                ShowWindow(button2, SW_SHOW);
                ShowWindow(button3, SW_SHOW);
                ShowWindow(button4, SW_SHOW);
                ShowWindow(button5, SW_SHOW);
                ShowWindow(button6, SW_SHOW);
                ShowWindow(button7, SW_SHOW);
                ShowWindow(button8, SW_SHOW);
                ShowWindow(button9, SW_SHOW);
                ShowWindow(buttonC, SW_SHOW);
                ShowWindow(buttonCE, SW_SHOW);
                ShowWindow(buttonPlus, SW_SHOW);
                ShowWindow(buttonNeg, SW_SHOW);
                ShowWindow(buttonMult, SW_SHOW);
                ShowWindow(buttonDiv, SW_SHOW);
                ShowWindow(buttonEq, SW_SHOW);
                ShowWindow(buttonPercent, SW_SHOW);
                ShowWindow(buttonDec, SW_SHOW);
                ShowWindow(calcDisplay, SW_SHOW);
                ShowWindow(traceDisplay, SW_HIDE);
                break;
            case 1:
                ShowWindow(button0, SW_HIDE);
                ShowWindow(button1, SW_HIDE);
                ShowWindow(button2, SW_HIDE);
                ShowWindow(button3, SW_HIDE);
                ShowWindow(button4, SW_HIDE);
                ShowWindow(button5, SW_HIDE);
                ShowWindow(button6, SW_HIDE);
                ShowWindow(button7, SW_HIDE);
                ShowWindow(button8, SW_HIDE);
                ShowWindow(button9, SW_HIDE);
                ShowWindow(buttonC, SW_HIDE);
                ShowWindow(buttonCE, SW_HIDE);
                ShowWindow(buttonPlus, SW_HIDE);
                ShowWindow(buttonNeg, SW_HIDE);
                ShowWindow(buttonMult, SW_HIDE);
                ShowWindow(buttonDiv, SW_HIDE);
                ShowWindow(buttonEq, SW_HIDE);
                ShowWindow(buttonPercent, SW_HIDE);
                ShowWindow(buttonDec, SW_HIDE);
                ShowWindow(calcDisplay, SW_HIDE);
                ShowWindow(traceDisplay, SW_SHOW);
                break;
            }
        }
        break;
    case WM_COMMAND:
        if (HIWORD(wParam) == BN_CLICKED) {
            OnButtonClick(lParam);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_CTLCOLORSTATIC: {
        HDC hdcStatic = (HDC)wParam;
        SetBkColor(hdcStatic, RGB(255, 255, 255));
        return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
    }
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

std::wstring build;
std::wstring trace = L"";
int decisions = 0;
float previous = 0.0;
std::wstring op;

void OnButtonClick(LPARAM lParam) {

    //build initial input

    //select operation
        //if still at zero and minus is selected make negative
        //if operation selected, and then minus is selected make negative
        //if operation is selected, and then CE is selected, clear operation
        //if operation is selected, and then C is selected, clear everything

    //build my input
        //if equal selected, do calculation, store result as previous


    if ((HWND)lParam == button0) {
        build += L"0";
        decisions++;
        trace += L"Current Input: " + build 
            + L", Current Operation: " + op 
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 0button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        
    }
    else if ((HWND)lParam == button1) {
        build += L"1";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 1button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button2) {
        build += L"2";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 2button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button3) {
        build += L"3";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 3button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button4) {
        build += L"4";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 4button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button5) {
        build += L"5";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 5button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button6) {
        build += L"6";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 6button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button7) {
        build += L"7";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 7button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button8) {
        build += L"8";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 8button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == button9) {
        build += L"9";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == 9button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == buttonPlus) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == +button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (build.size() != 0) {
            previous = std::stof(build);
            decisions++;
            trace += L"Current Input: " + build
                + L", Current Operation: " + op
                + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                + L", Current Decision: if currentInput != ''"
                + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        }
        build = L"";
        op = L"+";
    }
    else if ((HWND)lParam == buttonNeg) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == -button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (op.size() == 1 || (build.size() == 0 && previous == 0.0)) {
            decisions++;
            trace += L"Current Input: " + build
                + L", Current Operation: " + op
                + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                + L", Current Decision: if currentOp != '' or (currentInput == '' and currentState != 0)"
                + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            build += L"-";
        }
        else {
            decisions++;
            trace += L"Current Input: " + build
                + L", Current Operation: " + op
                + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                + L", Current Decision: if currentOp == '' and (currentInput != '' or currentState == 0)"
                + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            if (build.size() != 0) {
                previous = std::stof(build);
                decisions++;
                trace += L"Current Input: " + build
                    + L", Current Operation: " + op
                    + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                    + L", Current Decision: if currentState != 0"
                    + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            }
            build = L"";
            op = L"-";
        }
    }
    else if ((HWND)lParam == buttonMult) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == *button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (build.size() != 0) {
            previous = std::stof(build);
        }
        build = L"";
        op = L"*";
    }
    else if ((HWND)lParam == buttonDiv) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == /button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (build.size() != 0) {
            previous = std::stof(build);
        }
        build = L"";
        op = L"/";
    }
    else if ((HWND)lParam == buttonPercent) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == %button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (build.size() != 0) {
            float current = std::stof(build);
            current = previous * (current / 100);
            build = std::to_wstring(current);
            build = removeTrailingZeros(build);
            decisions++;
            trace += L"Current Input: " + build
                + L", Current Operation: " + op
                + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                + L", Current Decision: if currentInput != ''"
                + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        }
    }
    else if ((HWND)lParam == buttonDec) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == .button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        build += L".";
    }
    else if ((HWND)lParam == buttonC) {
        previous = 0.0;
        build = L"";
        op = L"";
        
        decisions = 0;
        trace = L"";
    }
    else if ((HWND)lParam == buttonCE) {
        build = L"";
        op = L"";
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == CEbutton"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
    }
    else if ((HWND)lParam == buttonEq) {
        decisions++;
        trace += L"Current Input: " + build
            + L", Current Operation: " + op
            + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
            + L", Current Decision: if buttonPress == =button"
            + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
        if (build.size() != 0) {
            decisions++;
            trace += L"Current Input: " + build
                + L", Current Operation: " + op
                + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                + L", Current Decision: if currentInput != ''"
                + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            float result = previous;
            float current = std::stof(build);
            if (op == L"+") {
                result = previous + current;
                decisions++;
                trace += L"Current Input: " + build
                    + L", Current Operation: " + op
                    + L", Current State: " + removeTrailingZeros(std::to_wstring(result))
                    + L", Current Decision: if currentOp == +"
                    + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            }
            else if (op == L"-") {
                result = previous - current;
                decisions++;
                trace += L"Current Input: " + build
                    + L", Current Operation: " + op
                    + L", Current State: " + removeTrailingZeros(std::to_wstring(result))
                    + L", Current Decision: if currentOp == -"
                    + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            }
            else if (op == L"*") {
                result = previous * current;
                decisions++;
                trace += L"Current Input: " + build
                    + L", Current Operation: " + op
                    + L", Current State: " + removeTrailingZeros(std::to_wstring(result))
                    + L", Current Decision: if currentOp == +"
                    + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
            }
            else if (op == L"/") {
                decisions++;
                trace += L"Current Input: " + build
                    + L", Current Operation: " + op
                    + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                    + L", Current Decision: if currentOp == /"
                    + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
                if (current == 0.0f) {
                    decisions++;
                    trace += L"Current Input: " + build
                        + L", Current Operation: " + op
                        + L", Current State: " + removeTrailingZeros(std::to_wstring(previous))
                        + L", Current Decision: if currentInput == 0"
                        + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
                    build = L"Err";
                }
                else {
                    result = previous / current;
                    decisions++;
                    trace += L"Current Input: " + build
                        + L", Current Operation: " + op
                        + L", Current State: " + removeTrailingZeros(std::to_wstring(result))
                        + L", Current Decision: if currentInput != 0"
                        + L", Decisions: " + std::to_wstring(decisions) + L"\r\n \r\n";
                }
            }
            op = L"";
            previous = result;
            build = std::to_wstring(previous);
            build = removeTrailingZeros(build);
        }
    }

    LPCWSTR display;
    display = build.c_str();
    SetWindowText(calcDisplay, display);

    LPCWSTR traceDisp;
    traceDisp = trace.c_str();
    SetWindowText(traceDisplay, traceDisp);
}

std::wstring removeTrailingZeros(std::wstring build) {
    size_t lastNonZero = build.find_last_not_of('0');
    build.erase(lastNonZero + 1);
    if (build.back() == '.')
        build.pop_back();
    return build;
}
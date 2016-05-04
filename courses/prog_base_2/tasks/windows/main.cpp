#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <CommCtrl.h>
#include <stdlib.h>=

struct DirectorHwnds {
    HWND nameHwnd;
    HWND surnameHwnd;
    HWND investmentsHwnd;
};

struct DirectorHwndsPair {
    DirectorHwnds editHwnds;
    DirectorHwnds staticHwnds;
    WNDPROC oldEditProc;
};

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow) {
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Startup Director"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           430,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           malloc(sizeof(DirectorHwndsPair))
           );

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0)) {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

HWND createStaticWin(const char *text, int x, int y, int w, int h, HWND hwnd, HINSTANCE hinst, DirectorHwndsPair *dHwndsPair) {
    HWND hWin = CreateWindowEx(
        0,
        WC_STATIC,
        text,
        WS_CHILD | WS_VISIBLE,
        x, y, w, h,
        hwnd,
        NULL,
        hinst,
        NULL
        );

    SetWindowLong(hWin, GWL_USERDATA, (LONG)dHwndsPair);

    return hWin;
}

HWND createEditWin(const char *text, int x, int y, int w, int h, HWND hwnd, HINSTANCE hinst, DirectorHwndsPair *dHwndsPair) {
    HWND hWin = CreateWindowEx(
        0,
        WC_EDIT,
        text,
        WS_CHILD | WS_VISIBLE | WS_BORDER,
        x, y, w, h,
        hwnd,
        NULL,
        hinst,
        NULL
        );

    SetWindowLong(hWin, GWL_USERDATA, (LONG)dHwndsPair);

    return hWin;
}

LRESULT CALLBACK EditProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {                  /* handle the messages */
    case WM_DESTROY:
        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_CREATE: {
        HINSTANCE hinst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
        DirectorHwndsPair *dHwndsPair = (DirectorHwndsPair *)((CREATESTRUCT *)lParam)->lpCreateParams;

        createStaticWin("Form 1", 50, 20, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Name", 50, 50, 130, 23, hwnd, hinst, dHwndsPair);
        dHwndsPair->editHwnds.nameHwnd = createEditWin("Ivan", 50, 70, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Surname", 50, 100, 130, 23, hwnd, hinst, dHwndsPair);
        dHwndsPair->editHwnds.surnameHwnd = createEditWin("Vasilievich", 50, 120, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Investments", 50, 150, 130, 23, hwnd, hinst, dHwndsPair);
        dHwndsPair->editHwnds.investmentsHwnd = createEditWin("45000000", 50, 170, 130, 23, hwnd, hinst, dHwndsPair);

        char buffer[128];
        createStaticWin("Form 2", 230, 20, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Name", 230, 50, 130, 23, hwnd, hinst, dHwndsPair);
        GetWindowText(dHwndsPair->editHwnds.nameHwnd, buffer, sizeof(buffer));
        dHwndsPair->staticHwnds.nameHwnd = createStaticWin(buffer, 230, 70, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Surname", 230, 100, 130, 23, hwnd, hinst, dHwndsPair);
        GetWindowText(dHwndsPair->editHwnds.surnameHwnd, buffer, sizeof(buffer));
        dHwndsPair->staticHwnds.surnameHwnd = createStaticWin(buffer, 230, 120, 130, 23, hwnd, hinst, dHwndsPair);
        createStaticWin("Investments", 230, 150, 130, 23, hwnd, hinst, dHwndsPair);
        GetWindowText(dHwndsPair->editHwnds.investmentsHwnd, buffer, sizeof(buffer));
        dHwndsPair->staticHwnds.investmentsHwnd = createStaticWin(buffer, 230, 170, 130, 23, hwnd, hinst, dHwndsPair);

        dHwndsPair->oldEditProc = (WNDPROC)SetWindowLong(dHwndsPair->editHwnds.nameHwnd, GWL_WNDPROC, (LONG)EditProcedure);
        SetWindowLong(dHwndsPair->editHwnds.surnameHwnd, GWL_WNDPROC, (LONG)EditProcedure);
        SetWindowLong(dHwndsPair->editHwnds.investmentsHwnd, GWL_WNDPROC, (LONG)EditProcedure);

        break;
    }
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}

LRESULT CALLBACK EditProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    DirectorHwndsPair *dHwndsPair = (DirectorHwndsPair *)GetWindowLong(hwnd, GWL_USERDATA);
    LRESULT lResult = CallWindowProc(dHwndsPair->oldEditProc, hwnd, message, wParam, lParam);

    switch (message) {
    case WM_CHAR: {
        char buffer[128];

        GetWindowText(dHwndsPair->editHwnds.nameHwnd, buffer, sizeof(buffer));
        SetWindowText(dHwndsPair->staticHwnds.nameHwnd, TEXT(buffer));
        GetWindowText(dHwndsPair->editHwnds.surnameHwnd, buffer, sizeof(buffer));
        SetWindowText(dHwndsPair->staticHwnds.surnameHwnd, TEXT(buffer));
        GetWindowText(dHwndsPair->editHwnds.investmentsHwnd, buffer, sizeof(buffer));
        SetWindowText(dHwndsPair->staticHwnds.investmentsHwnd, TEXT(buffer));

        break;
    }
    }

    return lResult;
}

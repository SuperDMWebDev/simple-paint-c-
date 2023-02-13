// Paint_Demo.cpp : Defines the entry point for the application.
// lam re chuot -> dien tich , chu vi , ve hinh vuong, hinh tron 

#include "framework.h"
#include "Simple Paint.h"
#include "windowsx.h"
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <time.h>
#include <fstream>
#include <sstream>
#include <math.h>
#include <memory>
#include "Tokenizer.h"
#include "Line.h"
#include "Ellipse1.h"
#include "Rectangle1.h"
#include "Point.h"
#include "Text.h"
#include "Shape.h"

#define MAX_LOADSTRING 100
#define IMAGE_WIDTH     18
#define IMAGE_HEIGHT    18
#define BUTTON_WIDTH    0
#define BUTTON_HEIGHT   0
#define NOCRYPT
#define NOSERVICE
#define NOMCX
#define NOIME
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnDestroy(HWND hwnd);
void OnPaint(HWND hwnd);
void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);
INT_PTR CALLBACK Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
vector<Shape*> shapes;
vector<Text*> texts;
vector<string> type;
int fromX = 0;
int fromY = 0;
int toX = 0;
int toY = 0;
bool isPreview = false;
bool isDrawing = false;
HFONT hfont;
int findDrawing[100];
bool isCutting = false;
bool isPasting = false; 
WCHAR* string1 = NULL;
int select = 0;
HDC hdc;
HBITMAP bitmap1;
int widthSetting = 3;
int lengthOfString = 0;
int newWidth = 0;
bool shiftClicked = false;
WCHAR buffer[100];
Point position;
vector <Shape*> temporaryShape;
vector <Text*> temporaryText;
vector<string> temporaryType;
vector <Shape*> temporaryShape1;
vector<string> temporaryType1;
CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbUsing = RGB(0, 0, 0); // Black
DWORD rgbFilling = RGB(255, 255, 255); // white // Tạo ra brush từ màu đã chọn
wstring fileNameStr;
CHOOSEFONT  cf;
LOGFONT  lf;
HFONT  hfNew, hfOld;
char str[80] = "";
HPEN hpen;
HWND inputValue;
wstring ws;
string contentOfString;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

    return RegisterClassExW(&wcex);
}



BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}


//FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)

//PURPOSE: Processes messages for the main window.

//WM_COMMAND  - process the application menu
//WM_PAINT    - Paint the main window
//WM_DESTROY  - post a quit message and return
string c;
INT_PTR CALLBACK Input(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
    case WM_CLOSE: // xu li khi nhan tat
        EndDialog(hDlg, LOWORD(wParam));
        return (INT_PTR)TRUE;
    case WM_COMMAND:

        if (LOWORD(wParam) == IDOK) // xu li khi nhan ok
        {

            inputValue = GetDlgItem(hDlg, IDC_EDIT1);
            lengthOfString = GetWindowTextLength(inputValue); // tim do dai de tao chuoi
            WCHAR* a = new WCHAR[MAX_PATH];
            GetWindowText(inputValue, a, lengthOfString + 1); // nhan them ky tu \0
            string1 = a; 
            wstring ws(string1);
            string string2(ws.begin(), ws.end());
            contentOfString = string2; // chuoi dung de in ra noi dung
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }


    return (INT_PTR)FALSE;
}




LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
        HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
        HANDLE_MSG(hWnd, WM_RBUTTONDOWN, OnRButtonDown);
        HANDLE_MSG(hWnd, WM_RBUTTONUP, OnRButtonUp);
        HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
    case WM_KEYDOWN:
        if (wParam == VK_SHIFT)
        {
            shiftClicked = true;
        }
        break;
    case WM_KEYUP:
        if (wParam == VK_SHIFT)
        {
            shiftClicked = false;
        }


    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}



void drawLast(HDC hdc)
{
    int countShape = 0;
    int countText = 0;
    vector<string> tokens;
    for (int i = 0; i < type.size(); i++)
    {
        if (type[i] == "Line")
        {

            tokens = Tokenizer::split(shapes[countShape]->toString(), ": ");

            Line* line = Line::parse(tokens[1]);
            int width = line->width();
            DWORD Color = line->color();
            HPEN hpen = CreatePen(PS_DASHDOT, width, Color);
            SelectObject(hdc, hpen);
            MoveToEx(hdc, line->start().x(), line->start().y(), NULL);
            LineTo(hdc, line->end().x(), line->end().y());
            DeleteObject(hpen);
            countShape++;

        }
        else if (type[i] == "Rectangle")
        {


            tokens = Tokenizer::split(shapes[countShape]->toString(), ": ");

            Rectangle1* rectangle = Rectangle1::parse(tokens[1]);

            int width = rectangle->width();
            DWORD lineColor = rectangle->lineColor(); // chinh lai thanh lineColor
            DWORD fillColor = rectangle->fillColor();

            HPEN hpen = CreatePen(PS_DASHDOT, width, lineColor);
            SelectObject(hdc, hpen);
            HBRUSH brush = CreateSolidBrush(fillColor);
            SelectObject(hdc, brush);
            Rectangle(hdc, rectangle->topLeft().x(), rectangle->topLeft().y(), rectangle->rightBottom().x(), rectangle->rightBottom().y());
            DeleteObject(hpen);
            DeleteObject(brush);
            countShape++;
        }
        else if (type[i] == "Ellipse")
        {
            vector<string> tokens;

            tokens = Tokenizer::split(shapes[countShape]->toString(), ": ");

            Ellipse1* ellipse = Ellipse1::parse(tokens[1]);

            int lineWidth = ellipse->width();
            DWORD lineColor = ellipse->lineColor();
            DWORD fillColor = ellipse->fillColor();

            HPEN hpen = CreatePen(PS_DASHDOT, lineWidth, lineColor);
            SelectObject(hdc, hpen);


            HBRUSH brush = CreateSolidBrush(fillColor);
            SelectObject(hdc, brush);
            Ellipse(hdc, ellipse->topLeft().x(), ellipse->topLeft().y(), ellipse->rightBottom().x(), ellipse->rightBottom().y());
            DeleteObject(hpen);
            DeleteObject(brush);

            countShape++;

        }
        else if (type[i] == "Text")
        {

            SelectObject(hdc, hfont);
            SetTextColor(hdc, texts[countText]->color());
            int len;
            string s = texts[countText]->content();
            int slength = (int)s.length() + 1;
            len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
            wchar_t* buf = new wchar_t[len];
            MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
            wstring r(buf);
            delete[] buf;
            LPCWSTR result = r.c_str();
            TextOut(hdc, texts[countText]->x(), texts[countText]->y(), result, texts[countText]->length());
            
            countText = countText + 1;
        }
        else if (type[i] == "Point")
        {
            vector<string> tokens;

            tokens = Tokenizer::split(shapes[countShape]->toString(), ",");

            Point* point = new Point(stoi(tokens[0]), stoi(tokens[1]));

            HPEN hpen = CreatePen(PS_DASHDOT, widthSetting, rgbUsing);

            SelectObject(hdc, hpen);
            int right = point->x() + 2;
            int bottom = point->y() + 2;
            Ellipse(hdc, point->x(), point->y(), right, bottom);
            DeleteObject(hpen);
            countShape++;
        }


    }
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    // Lấy font hệ thống
    LOGFONT lf;
    GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
    hfont = CreateFont(lf.lfHeight, lf.lfWidth,
        lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
        lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
        lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
        lf.lfPitchAndFamily, lf.lfFaceName);

    InitCommonControls();
    TBBUTTON tbButtons[] =
    {
        { STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { STD_DELETE,   ID_EDIT_DELETE,TBSTATE_ENABLED,TBSTYLE_BUTTON, 0, 0},
        {STD_CUT,   ID_EDIT_CUT, TBSTATE_ENABLED,  TBSTYLE_BUTTON,0,0},
        {STD_PASTE, ID_EDIT_PASTE, TBSTATE_ENABLED,  TBSTYLE_BUTTON,0,0}
    };
    HWND hToolBarWnd = CreateToolbarEx(hwnd,
        WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
        ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
        0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
        BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
        sizeof(TBBUTTON));

    // tự tạo các button để thực hiện các chức năng 
    TBBUTTON userButtons[] =
    {
        { 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
        { 0, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 1, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 2, ID_DRAW_LINE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
        { 3, ID_DRAW_POINT, TBSTATE_ENABLED,TBSTYLE_BUTTON,0,0},
        { 4, ID_DRAW_TEXT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
    };
    TBADDBITMAP	tbBitmap = { hInst, IDB_BITMAP1 };
    // Thêm danh sách ảnh vào toolbar
    int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM)sizeof(tbBitmap) / sizeof(TBADDBITMAP),
        (LPARAM)(LPTBADDBITMAP)&tbBitmap);
    // Xác định chỉ mục hình ảnh c ủa mỗi button từ ảnh bự liên hoàn nhiều tấm
    userButtons[1].iBitmap += idx;
    userButtons[2].iBitmap += idx;
    userButtons[3].iBitmap += idx;
    userButtons[4].iBitmap += idx;
    userButtons[5].iBitmap += idx;
    // Thêm nút bấm vào toolbar
    SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM)sizeof(userButtons) / sizeof(TBBUTTON),
        (LPARAM)(LPTBBUTTON)&userButtons);

    return TRUE;

}

bool onNewDialog = false;
void newFile(HWND hwnd)
{
    if (shapes.size() > 0 || texts.size() > 0)
    {
        if (MessageBox(hwnd, L"Save Image?", L"Save Image", MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            OPENFILENAME ofn;       // common dialog box structure

            wchar_t filePath[MAX_PATH] = L"Untitled";
            // Initialize OPENFILENAME
            ZeroMemory(&ofn, sizeof(ofn));
            ofn.lStructSize = sizeof(ofn);
            ofn.hwndOwner = hwnd;

            // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
            // use the contents of szFile to initialize itself.
            ofn.lpstrFile = (LPTSTR)filePath;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrFilter = (LPWSTR)L"Text Files(*.txt)\0*.txt\0\0";
            ofn.lpstrFileTitle = NULL;
            ofn.nMaxFileTitle = 0;
            ofn.lpstrInitialDir = NULL;
            ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_NOVALIDATE | OFN_ENABLETEMPLATEHANDLE | OFN_CREATEPROMPT;
            ofn.lpstrDefExt = (LPWSTR)L"txt";
            wstring fileNameStr;
            if (GetSaveFileName(&ofn))
                fileNameStr = wstring(filePath);
            ofstream writer(fileNameStr);
            writer << shapes.size() << endl;
            int countShape = 0;
            int countText = 0;
            for (int i = 0; i < type.size(); i++)
            {

                if (type[i] == "Rectangle" || type[i] == "Ellipse" || type[i] == "Point" || type[i] == "Line")
                {
                    if (type[i] == "Point")
                    {

                        writer << "Point: " << shapes[countShape]->toString() << endl;

                    }
                    else
                    {

                        writer << shapes[countShape]->toString() << endl;

                    }
                    countShape++;
                }
                else if (type[i] == "Text")
                {
                    writer << texts[countText]->toString() << endl;
                    countText++;
                }
            }
            writer.close();

        }
        if (onNewDialog == true)
        {
            MessageBox(hwnd, L"New file has been created", L"Notification", MB_OK | MB_ICONINFORMATION);
        }
        shapes.clear();
        type.clear();
        texts.clear();
        temporaryShape.clear();
        temporaryType.clear();
        temporaryText.clear();
        temporaryShape1.clear();
        temporaryType1.clear();
        InvalidateRect(hwnd, NULL, TRUE);

    }

}


void saveFile(HWND hwnd)
{
    OPENFILENAME ofn;       // common dialog box structure

    wchar_t filePath[MAX_PATH] = L"Untitled";
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;

    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile = (LPTSTR)filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = (LPWSTR)L"Text Files(*.txt)\0*.txt\0\0";
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_NOVALIDATE | OFN_ENABLETEMPLATEHANDLE | OFN_CREATEPROMPT;
    ofn.lpstrDefExt = (LPWSTR)L"txt";
    wstring fileNameStr;
    if (GetSaveFileName(&ofn))
    {
        fileNameStr = wstring(filePath);

        ofstream writer(fileNameStr);
        writer << type.size() << endl;

        int countShape = 0;
        int countText = 0;
        for (int i = 0; i < type.size(); i++)
        {

                if (type[i] == "Rectangle" || type[i] == "Ellipse" || type[i] == "Point" || type[i] == "Line")
                {
                    if (type[i] == "Point")
                    {

                        writer << "Point: " << shapes[countShape]->toString() << endl;

                    }
                    else
                    {

                        writer << shapes[countShape]->toString() << endl;

                    }
                    countShape++;
                }
                else if (type[i] == "Text")
                {
                    writer << texts[countText]->toString() << endl;
                    countText++;
                }
         }


        
        writer.close();

    }

}



void openFile(HWND hwnd)
{

    OPENFILENAME ofn;       // common dialog box structure
    wchar_t filePath[MAX_PATH] = L"Untitled";
    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;

    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    ofn.lpstrFile = (LPTSTR)filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = (LPWSTR)L"Text Files(*.txt)\0*.txt\0\0";
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_NOVALIDATE | OFN_ENABLETEMPLATEHANDLE | OFN_CREATEPROMPT;
    ofn.lpstrDefExt = (LPWSTR)L"txt";
    wstring fileNameStr;
    if (GetOpenFileName(&ofn))
    {
        fileNameStr = wstring(filePath);


        ifstream reader(fileNameStr);
        string buffer;
        getline(reader, buffer);
        int count = stoi(buffer);

        Shape* shape1 = NULL;
        Text* text = NULL;
        bool k = true;
        for (int i = 0; i < count; i++)
        {
            k = true;
            getline(reader, buffer);
            if (buffer != "")
            {
                auto tokens = Tokenizer::split(buffer, ": ");
                string typeShape = tokens[0];
                type.push_back(typeShape);

                if (typeShape == "Line")
                {
                    if (k == true)
                    {
                        shape1 = Line::parse(tokens[1]);
                        shapes.push_back(shape1);
                        k = false;
                    }
                }
                else if (typeShape == "Rectangle")
                {
                    if (k == true)
                    {
                        shape1 = Rectangle1::parse(tokens[1]);
                        shapes.push_back(shape1);
                        k = false;
                    }
                }
                else if (typeShape == "Ellipse")
                {
                    if (k == true)
                    {
                        shape1 = Ellipse1::parse(tokens[1]);
                        shapes.push_back(shape1);
                        k = false;
                    }
                }
                else if (typeShape == "Point")
                {
                    if (k == true)
                    {
                        shape1 = Point::parse(tokens[1]);
                        shapes.push_back(shape1);
                        k = false;
                    }
                }
                else if (typeShape == "Text")
                {
                    if (k == true)
                    {
                        getline(reader, buffer);
                        text = Text::parse(tokens[1], buffer);
                        texts.push_back(text);
                        k = false;
                    }
                }

            }

        }

        reader.close();

        OnPaint(hwnd);

    }


}



void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch (id) {
    case ID_FILE_NEW:
        isDrawing = false;
        isCutting = false;
        isPasting = false;
        onNewDialog = true;
        newFile(hwnd);
        break;
    case ID_FILE_OPEN:
        isDrawing = false;
        isCutting = false;
        isPasting = false;
        onNewDialog = false;
        newFile(hwnd);
        openFile(hwnd);
        break;
    case ID_FILE_SAVE:
        // OPENFILENAME OpenFileName;

        if (shapes.size() > 0 || texts.size() > 0)
        {
            saveFile(hwnd);
        }
        break;
    case IDM_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
        break;

    case ID_CHOOSE_FILLCOLOR:
        ZeroMemory(&cc, sizeof(CHOOSECOLOR));
        cc.lStructSize = sizeof(CHOOSECOLOR);
        cc.hwndOwner = hwnd;
        cc.lpCustColors = (LPDWORD)acrCustClr;
        cc.rgbResult = rgbUsing;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (ChooseColor(&cc))
        {

            rgbFilling = cc.rgbResult;
        }
        break;
    case ID_CHOOSE_LINECOLOR:
        ZeroMemory(&cc, sizeof(CHOOSECOLOR));
        cc.lStructSize = sizeof(CHOOSECOLOR);
        cc.hwndOwner = hwnd;
        cc.lpCustColors = (LPDWORD)acrCustClr;
        cc.rgbResult = rgbUsing;
        cc.Flags = CC_FULLOPEN | CC_RGBINIT;
        if (ChooseColor(&cc))
        {

            rgbUsing = cc.rgbResult;
        }
        break;
    case ID_CHOOSE_FONT:
        ZeroMemory(&cf, sizeof(CHOOSEFONT));
        cf.lStructSize = sizeof(CHOOSEFONT);
        cf.hwndOwner = hwnd;
        cf.lpLogFont = &lf;
        cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

        if (ChooseFont(&cf) == TRUE)
        {
            hfont = CreateFontIndirect(cf.lpLogFont);

        }
        break;
    case ID_LINEWIDTH_1PX:
        newWidth = 1;
        if (newWidth > 0)
        {
            widthSetting = newWidth;
        }
        break;
    case ID_LINEWIDTH_3PX:
        newWidth = 3;
        if (newWidth > 0)
        {
            widthSetting = newWidth;
        }
        break;
    case ID_LINEWIDTH_5PX:
        newWidth = 5;
        if (newWidth > 0)
        {
            widthSetting = newWidth;
        }
        break;
    case ID_LINEWIDTH_8PX:
        newWidth = 8;
        if (newWidth > 0)
        {
            widthSetting = newWidth;
        }
        break;
    case ID_CHOOSE_UNDO:
        if (type.size() > 0)
        {
            string a = type[type.size() - 1];
            if (a == "Rectangle" || a == "Ellipse" || a == "Line" || a == "Point")
            {
                Shape* shape1 = shapes[shapes.size() - 1];
                string type1 = type[type.size() - 1];
                shapes.pop_back();
                type.pop_back();
                temporaryShape.push_back(shape1);
                temporaryType.push_back(type1);
            }
            else if (a == "Text")
            {
                Text* text = texts[texts.size() - 1];
                string type1 = type[type.size() - 1];
                texts.pop_back();
                type.pop_back();
                temporaryText.push_back(text);
                temporaryType.push_back(type1);

            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case ID_CHOOSE_REDO:
        if (temporaryType.size() > 0)
        {
            string a = temporaryType[temporaryType.size() - 1];
            if (a == "Rectangle" || a == "Ellipse" || a == "Line" || a == "Point")
            {
                Shape* shape1 = temporaryShape[temporaryShape.size() - 1];
                string type1 = temporaryType[temporaryType.size() - 1];
                temporaryShape.pop_back();
                temporaryType.pop_back();
                shapes.push_back(shape1);
                type.push_back(type1);
            }
            else if (a == "Text")
            {
                Text* text1 = temporaryText[temporaryText.size() - 1];
                string type1 = temporaryType[temporaryType.size() - 1];
                temporaryText.pop_back();
                temporaryType.pop_back();
                texts.push_back(text1);
                type.push_back(type1);
            }
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;
    case ID_DRAW_LINE:
        findDrawing[0] = 1;
        findDrawing[1] = 0;
        findDrawing[2] = 0;
        findDrawing[3] = 0;
        findDrawing[4] = 0;
        findDrawing[5] = 0;
        break;
    case ID_DRAW_ELLIPSE:
        findDrawing[0] = 0;
        findDrawing[1] = 1;
        findDrawing[2] = 0;
        findDrawing[3] = 0;
        findDrawing[4] = 0;
        findDrawing[5] = 0;
        break;

    case ID_DRAW_RECTANGLE:
        findDrawing[0] = 0;
        findDrawing[1] = 0;
        findDrawing[2] = 1;
        findDrawing[3] = 0;
        findDrawing[4] = 0;
        findDrawing[5] = 0;
        break;
    case ID_DRAW_TEXT:
        findDrawing[0] = 0;
        findDrawing[1] = 0;
        findDrawing[2] = 0;
        findDrawing[3] = 1;
        findDrawing[4] = 0;
        findDrawing[5] = 0;
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, Input);
        break;
    case ID_DRAW_POINT:
        findDrawing[0] = 0;
        findDrawing[1] = 0;
        findDrawing[2] = 0;
        findDrawing[3] = 0;
        findDrawing[4] = 1;
        findDrawing[5] = 0;
        break;
    case ID_EDIT_DELETE:
        findDrawing[0] = 0;
        findDrawing[1] = 0;
        findDrawing[2] = 0;
        findDrawing[3] = 0;
        findDrawing[4] = 0;
        findDrawing[5] = 1;
        break;
    case ID_EDIT_CUT:
        isCutting = true;
        isPasting = false;
        break;
    case ID_EDIT_PASTE:
        isPasting = true;
        isCutting = false;
        break;
    case IDM_EXIT:
        if (shapes.size() > 0 || texts.size() > 0) {
            if (MessageBox(hwnd, L"Save Image?", L"Save Image", MB_YESNO | MB_ICONQUESTION) == IDYES) {
                saveFile(hwnd);
            }
        }
        PostQuitMessage(0);
        break;

    }
}

void OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}

void OnPaint(HWND hwnd)
{
    PAINTSTRUCT ps;
    hdc = BeginPaint(hwnd, &ps);
    RECT rect;
    GetClientRect(hwnd, &rect);
    HDC hdc1 = CreateCompatibleDC(hdc); // tao 1 hdc1
    HBITMAP bitmap1 = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	//tạo 1 bitmap ảo
    SelectBitmap(hdc1, bitmap1);

    FillRect(hdc1, &rect, (HBRUSH)(COLOR_BTNFACE));   //tô màu cho hdc ảo

    SetBkMode(hdc1, TRANSPARENT);

    drawLast(hdc1);

    hpen = CreatePen(PS_DASHDOT, widthSetting, rgbUsing);
    SelectObject(hdc1, hpen);
    SelectObject(hdc1, CreateSolidBrush(rgbFilling));
    if (findDrawing[5] == 1)
    {
        DeleteObject(hpen);
        hpen = CreatePen(PS_DASHDOT, 1, RGB(0, 0, 0));
        SelectObject(hdc1, hpen);
        SelectObject(hdc1, CreateSolidBrush(RGB(255, 255, 255)));
        select = 5;

    }
    else
    {
        for (int i = 0; i < 5; i++)
        {
            if (findDrawing[i] == 1)
            {
                select = i;
            }
        }
    }


    if (isDrawing == true and isCutting == false)
    {


        switch (select)
        {

        case 0:
            MoveToEx(hdc1, fromX, fromY, NULL);
            LineTo(hdc1, toX, toY);
            break;
        case 1:
            if (shiftClicked == false)
            {
                Ellipse(hdc1, fromX, fromY, toX, toY);

            }
            else
            {
                toY = toX - fromX + fromY;
                Ellipse(hdc1, fromX, fromY, toX, toY);
            }
            break;
        case 2:
            if (shiftClicked == false)
            {
                Rectangle(hdc1, fromX, fromY, toX, toY);
            }
            else
            {
                toY = toX - fromX + fromY;
                Rectangle(hdc1, fromX, fromY, toX, toY);
            }
            break;
        case 3:
            // Do nothing
            break;
        case 4:
            Ellipse(hdc1, fromX, fromY, fromX + 2, fromY + 2);
            break;
        case 5:
            Rectangle(hdc1, fromX, fromY, toX, toY);
            break;
        }
        select = 0;

    }
    BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdc1, 0, 0, SRCCOPY);
    SelectObject(hdc1, bitmap1);

    DeleteObject(bitmap1);
    DeleteDC(hdc1);
    EndPaint(hwnd, &ps);

}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
    isPreview = true;
    isDrawing = true;
    fromX = x;
    fromY = y;
    isCutting = false;
    isPasting = false;
    HDC hdc = GetDC(hwnd);
    MoveToEx(hdc, x, y, NULL);

}
void OnRButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{


    HDC hdc = GetDC(hwnd);
    MoveToEx(hdc, x, y, NULL);
    vector<string> tokens;
    int countShape = 0;
    bool success = 1;
    int t = 0;
    if (isCutting)
    {

        if (type.size() > 0)
        {
            int u = type.size();
            for (int i = 0; i < u; i++)
            {

                string a = type[t];
                t++;
                success = 0;
                if (a == "Text")
                {

                    continue;
                }
                if (a == "Rectangle")
                {
                    tokens = Tokenizer::split(shapes[countShape]->toString(), ": ");
                    Rectangle1* rectangle = Rectangle1::parse(tokens[1]);
                    if (x > rectangle->topLeft().x() and x < rectangle->rightBottom().x() and y > rectangle->topLeft().y() and y < rectangle->rightBottom().y())
                    {


                        Shape* shape1 = shapes[countShape];
                        shapes.erase(shapes.begin() + countShape);
                        type.erase(type.begin() + countShape);
                        temporaryShape1.push_back(shape1);
                        temporaryType1.push_back(a);
                        success = 1;





                    }
                    else
                    {
                        countShape++;
                    }
                    if (success == 1)
                    {
                        t--;

                    }

                }
                else if (a == "Ellipse")
                {
                    tokens = Tokenizer::split(shapes[countShape]->toString(), ": ");
                    Ellipse1* ellipse = Ellipse1::parse(tokens[1]);
                    if (x > ellipse->topLeft().x() and x < ellipse->rightBottom().x() and y > ellipse->topLeft().y() and y < ellipse->rightBottom().y())
                    {

                        Shape* shape1 = shapes[countShape];

                        shapes.erase(shapes.begin() + countShape);
                        type.erase(type.begin() + countShape);
                        temporaryShape1.push_back(shape1);
                        temporaryType1.push_back(a);
                        success = 1;




                    }
                    else
                    {
                        countShape++;
                    }
                    if (success == 1)
                    {
                        t--;

                    }

                }
                else
                {
                    countShape++;
                }


            }
        }



    }
    else if (isPasting)
    {
        int i = 0;
        while (temporaryType1.size() > 0)
        {
            string a = temporaryType1[0];
            if (a == "Rectangle")
            {

                tokens = Tokenizer::split(temporaryShape1[0]->toString(), ": ");
                Rectangle1* rectangle = Rectangle1::parse(tokens[1]);
                Point topLeft(x, y);
                Point rightBottom(x + rectangle->rightBottom().x() - rectangle->topLeft().x(), y + rectangle->rightBottom().y() - rectangle->topLeft().y());
                rectangle->setrightBottom(rightBottom);
                rectangle->setTopLeft(topLeft);
                type.push_back(a);
                shapes.push_back(rectangle);
                temporaryShape1.erase(temporaryShape1.begin() + 0);
                temporaryType1.erase(temporaryType1.begin() + 0);



            }
            else if (a == "Ellipse")
            {
                tokens = Tokenizer::split(temporaryShape1[0]->toString(), ": ");
                Ellipse1* ellipse = Ellipse1::parse(tokens[1]);
                Point topLeft(x, y);
                Point rightBottom(x + ellipse->rightBottom().x() - ellipse->topLeft().x(), y + ellipse->rightBottom().y() - ellipse->topLeft().y());
                ellipse->setrightBottom(rightBottom);
                ellipse->setTopLeft(topLeft);
                type.push_back(a);
                shapes.push_back(ellipse);
                temporaryShape1.erase(temporaryShape1.begin() + 0);
                temporaryType1.erase(temporaryType1.begin() + 0);



            }
        }

    }



    isCutting = false;
    isPasting = false;
    InvalidateRect(hwnd, NULL, TRUE);
}
void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
    if (isDrawing)
    {
        toX = x;
        toY = y;
        position.setX(x);
        position.setY(y);

        wsprintf(buffer, L"Coordiante: %d  %d", position.x(), position.y());
        SetWindowText(hwnd, buffer);

        // Báo hiệu cần xóa đi toàn bộ màn hình
        InvalidateRect(hwnd, NULL, FALSE);

    }


}
void OnRButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
    isCutting = false;
    isPasting = false;
}
void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{


    if (findDrawing[0] == 1)
    {
        Shape* line = new Line(Point(fromX, fromY), Point(toX, toY), widthSetting, rgbUsing);
        shapes.push_back(line);
        type.push_back("Line");
        wsprintf(buffer, L"Perimeter: %d Area: %d", line->perimeter(), line->area());
        SetWindowText(hwnd, buffer);

    }
    else if (findDrawing[1] == 1)
    {
        Shape* ellipse = NULL;
        ellipse = new Ellipse1(Point(fromX, fromY), Point(toX, toY), widthSetting, rgbUsing, rgbFilling);
        shapes.push_back(ellipse);
        type.push_back("Ellipse");
        wsprintf(buffer, L"Perimeter: %d Area: %d", ellipse->perimeter(), ellipse->area());
        SetWindowText(hwnd, buffer);
    }
    else if (findDrawing[2] == 1)
    {
        Shape* rectangle = NULL;
        rectangle = new Rectangle1(Point(fromX, fromY), Point(toX, toY), widthSetting, rgbUsing, rgbFilling);
        shapes.push_back(rectangle);
        type.push_back("Rectangle");
        wsprintf(buffer, L"Perimeter: %d Area: %d", rectangle->perimeter(), rectangle->area());
        SetWindowText(hwnd, buffer);
    }
    else if (findDrawing[3] == 1)
    {
        Text* text = new Text(fromX, fromY, contentOfString, lengthOfString, lf, rgbUsing);
        texts.push_back(text);
        type.push_back("Text");

    }
    else if (findDrawing[4] == 1)
    {

        Shape* point = NULL;
        point = new Point(fromX, fromY);
        shapes.push_back(point);
        type.push_back("Point");
        wsprintf(buffer, L"Perimeter: 0 Area: 0");
        SetWindowText(hwnd, buffer);

    }
    else if (findDrawing[5] == 1)
    {
        Shape* rectangle = NULL;
        rectangle = new Rectangle1(Point(fromX, fromY), Point(toX, toY), widthSetting, RGB(255, 255, 255), RGB(255, 255, 255));
        shapes.push_back(rectangle);
        type.push_back("Rectangle");
    }

    isDrawing = false;
    InvalidateRect(hwnd, NULL, FALSE);
}



// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

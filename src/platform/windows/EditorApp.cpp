#define NOMINMAX
#include <windows.h>
#include <string>
#include "budgie/Engine.hpp"
#include "budgie/Scene.hpp"

namespace {
constexpr COLORREF Background = RGB(20, 27, 42);
constexpr COLORREF Panel = RGB(28, 38, 57);
constexpr COLORREF Accent = RGB(44, 126, 230);
budgie::Scene g_scene;

void text(HDC dc, int x, int y, const wchar_t* value, COLORREF color = RGB(225,235,250), int size = 15) {
    SetTextColor(dc, color);
    SetBkMode(dc, TRANSPARENT);
    HFONT font = CreateFontW(size,0,0,0,FW_MEDIUM,FALSE,FALSE,FALSE,DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY,DEFAULT_PITCH,L"Segoe UI");
    auto old = SelectObject(dc,font);
    TextOutW(dc,x,y,value,lstrlenW(value));
    SelectObject(dc,old);
    DeleteObject(font);
}
void fill(HDC dc, RECT r, COLORREF color) {
    HBRUSH brush=CreateSolidBrush(color); FillRect(dc,&r,brush); DeleteObject(brush);
}
void drawGrid(HDC dc, RECT r) {
    HPEN pen=CreatePen(PS_SOLID,1,RGB(49,65,88)); auto old=(HPEN)SelectObject(dc,pen);
    for(int x=r.left; x<r.right; x+=32){MoveToEx(dc,x,r.top,nullptr);LineTo(dc,x,r.bottom);}
    for(int y=r.top; y<r.bottom; y+=32){MoveToEx(dc,r.left,y,nullptr);LineTo(dc,r.right,y);}
    SelectObject(dc,old); DeleteObject(pen);
}
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch(msg) {
    case WM_CREATE:
        g_scene.createEntity("Camera");
        g_scene.createEntity("Directional Light");
        g_scene.createEntity("Cube");
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps; HDC dc=BeginPaint(hwnd,&ps); RECT client{}; GetClientRect(hwnd,&client);
        fill(dc,client,Background);
        RECT top{0,0,client.right,42}; fill(dc,top,Panel);
        text(dc,16,12,L"◆  BUDGIEOS ENGINE",RGB(100,174,255),17);
        text(dc,270,14,L"File     Edit     Create     Build     Help",RGB(205,218,238),14);
        RECT left{0,42,190,client.bottom-58}; fill(dc,left,Panel);
        text(dc,14,60,L"WORLD OUTLINER",RGB(117,180,255),13);
        int y=92; for(const auto& entity:g_scene.entities()) {
            std::wstring name(entity.name.begin(),entity.name.end());
            text(dc,18,y,L"◇",RGB(105,170,245),14); text(dc,40,y,name.c_str()); y+=27;
        }
        RECT right{client.right-220,42,client.right,client.bottom-58}; fill(dc,right,Panel);
        text(dc,client.right-202,60,L"INSPECTOR",RGB(117,180,255),13);
        text(dc,client.right-202,96,L"Transform"); text(dc,client.right-190,125,L"Position  0, 0, 0",RGB(165,184,211),13);
        text(dc,client.right-190,150,L"Rotation  0, 0, 0",RGB(165,184,211),13);
        text(dc,client.right-190,175,L"Scale     1, 1, 1",RGB(165,184,211),13);
        RECT viewport{190,42,client.right-220,client.bottom-58}; fill(dc,viewport,RGB(17,24,38)); drawGrid(dc,viewport);
        text(dc,viewport.left+18,viewport.top+16,L"SCENE VIEWPORT",RGB(117,180,255),12);
        int cx=(viewport.left+viewport.right)/2, cy=(viewport.top+viewport.bottom)/2;
        HPEN axis=CreatePen(PS_SOLID,2,Accent); auto old=(HPEN)SelectObject(dc,axis);
        MoveToEx(dc,cx-45,cy,nullptr);LineTo(dc,cx+45,cy);MoveToEx(dc,cx,cy-45,nullptr);LineTo(dc,cx,cy+45);
        SelectObject(dc,old);DeleteObject(axis);
        RECT bottom{0,client.bottom-58,client.right,client.bottom}; fill(dc,Panel);
        text(dc,14,client.bottom-39,L"CONTENT BROWSER",RGB(117,180,255),12);
        text(dc,190,client.bottom-39,L"Assets     Materials     Scenes     Scripts",RGB(185,202,226),13);
        EndPaint(hwnd,&ps); return 0;
    }
    case WM_SIZE: InvalidateRect(hwnd,nullptr,TRUE); return 0;
    case WM_DESTROY: PostQuitMessage(0); return 0;
    }
    return DefWindowProcW(hwnd,msg,wp,lp);
}
}
int WINAPI wWinMain(HINSTANCE instance,HINSTANCE, PWSTR,int show) {
    const wchar_t CLASS_NAME[]=L"BudgieOSEngineWindow";
    WNDCLASSW wc{}; wc.lpfnWndProc=WindowProc; wc.hInstance=instance;
    wc.lpszClassName=CLASS_NAME; wc.hCursor=LoadCursor(nullptr,IDC_ARROW);
    wc.hbrBackground=CreateSolidBrush(Background);
    if(!RegisterClassW(&wc)) return 1;
    HWND hwnd=CreateWindowExW(0,CLASS_NAME,L"BudgieOS Engine 1.0 — Ultimate Edition",
        WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,1280,800,nullptr,nullptr,instance,nullptr);
    if(!hwnd) return 1;
    ShowWindow(hwnd,show); UpdateWindow(hwnd);
    MSG msg{}; while(GetMessageW(&msg,nullptr,0,0)>0){TranslateMessage(&msg);DispatchMessageW(&msg);}
    return static_cast<int>(msg.wParam);
}

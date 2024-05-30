#include <graphics.h>
#include <conio.h>
#define PI 3.1415926535
void trans(IMAGE *dstimg, int x, int y, IMAGE *srcimg)
{
    HDC dstDC = GetImageHDC(dstimg);
    HDC srcDC = GetImageHDC(srcimg);
    int w = srcimg->getwidth();
    int h = srcimg->getheight();
    BLENDFUNCTION bf = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
    AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
int main()
{
    initgraph(640, 640);
    setbkcolor(TRANSPARENT);
    IMAGE img1, img2, img3, img4, img5;
    loadimage(&img1, _T("back.png"), 640, 220);
    loadimage(&img2, _T("child.png"), 100, 100);
    loadimage(&img3, _T("bk2.png"), 640, 420);
    loadimage(&img4, _T("wheel.png"), 200, 200);
    loadimage(&img5, _T("quit.png"), 100, 50);
    putimage(0, 0, &img1);
    trans(NULL, 500, 100, &img2);
    putimage(0, 220, &img3);
    trans(NULL, 220, 320, &img4);
    putimage(0, 0, &img5);

    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 10);
    setlinecolor(LIGHTGRAY);
    circle(320, 420, 100);
    setlinecolor(RED);
    setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 3);
    line(410, 420, 430, 420);
    double cur = 0;
    ExMessage kb;
    while (1)
    {
        if (peekmessage(&kb, EM_KEY))
        {
            setlinecolor(RED);
            setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 8);
            line(410, 420, 430, 420);
            arc(220, 320, 420, 520, cur, cur + PI / 3);
            cur += PI / 3;
            break;
        }
    }
    while (1)
    {
        if (peekmessage(&kb, EX_KEY))
        {
            setlinecolor(RED);
            setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 8);
            line(410, 420, 430, 420);
            arc(220, 320, 420, 520, cur, cur + PI / 4 + 0.02);
            cur += PI / 4;
            if (kb.vkcode == VK_ESCAPE)
            {
                closegraph();
                return 0;
            }
        }
        if (cur >= 0)
        {
            setlinecolor(LIGHTGRAY);
            setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 10);
            arc(220, 320, 420, 520, cur - PI / 90 + 0.022, cur);
            cur -= PI / 90;
        }
        if (cur > 2 * PI)
        {
            IMAGE img6;
            loadimage(&img6, _T("success.png"), 100, 50);
            trans(NULL, 270, 400, &img6);
            while (1)
            {
                kb = getmessage(EX_KEY);
                if (kb.vkcode == VK_ESCAPE)
                {
                    closegraph();
                    return 0;
                }
            }
        }
        Sleep(1);
    }
}
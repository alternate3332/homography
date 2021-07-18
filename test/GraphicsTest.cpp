#include <stdio.h>
#include <vector>
#include <functional>
#include <tuple>
#include <string>
#include "Graphics.h"

using namespace suzu;

bool testCopyOrClonePointNotAffectsOriginObj(){
    Point<int> p(2,3);
    Point<int> pequal = p;
    Point<int> pclone = p.clone();
    Point<int> pcopy;
    pcopy = p;

    bool res = (p.x == 2) && (p.y == 3);
    res &= ((pequal.x == 2) && (pequal.y == 3));
    res &= ((pclone.x == 2) && (pclone.y == 3));
    res &= ((pcopy.x == 2) && (pcopy.y == 3));
    
    if(res != true){
        printf("construtor failed\n");
        return false;
    }

    p.x = 3;
    res &= (pequal.x == 2);
    res &= (pclone.x == 2);
    res &= (pcopy.x == 2);
    
    return res;
}

bool testCopyOrCloneRectNotAffectsOriginObj(){
    Point<int> leftTop(0, 0);
    Point<int> rightTop(10, 0);
    Point<int> leftBottom(0, 10);
    Point<int> rightBottom(10, 10);

    bool res = true;

    Rect<int> r;
    res &= (r.rightBottom.x == 0);
    r.leftTop = leftTop;
    r.rightTop = rightTop;
    r.leftBottom = leftBottom;
    r.rightBottom = rightBottom;

    res &= (r.rightBottom.x == 10);

    if(res != true){
        printf("%s --- NG. set Point doesn't work.\n", __func__);
        return false;
    }

    rightBottom.x = 0;
    res &= (rightBottom.x == 0);
    res &= (r.rightBottom.x == 10);

    if(res != true){
        printf("%s --- NG. change originPoint affects RectClassMember.\n", __func__);
        return false;
    }

    Rect<int> r2 = r;
    Rect<int> r3 = r.clone();
    res &= (r.rightBottom.x == 10);
    res &= (r2.rightBottom.x == 10);
    res &= (r3.rightBottom.x == 10);
    r.rightBottom.x = 0;
    res &= (r.rightBottom.x == 0);
    res &= (r2.rightBottom.x == 10);
    res &= (r3.rightBottom.x == 10);
    
    return res;
}

int main(int argc, char** argv){
    typedef std::tuple<std::string, std::function<bool(void)> > mytuple;

    std::vector< mytuple > test;

    printf("\n");

    test.push_back(mytuple("testCopyOrClonePointNotAffectsOriginObj",testCopyOrClonePointNotAffectsOriginObj));
    test.push_back(mytuple("testCopyOrCloneRectNotAffectsOriginObj",testCopyOrCloneRectNotAffectsOriginObj));

     for(mytuple it : test){
        std::string funcName = std::get<0>(it);
        std::function<bool(void)> func = std::get<1>(it);
        bool res = func();
        if(res){
            printf("\x1b[36m");     /* 前景色をシアンに */
            printf("%s --- ok\n", funcName.c_str());
        }
        else {
            printf("\x1b[31m");     /* 前景色を赤に */
            printf("%s --- NG\n", funcName.c_str());
        }
        
        printf("\x1b[39m");     /* 前景色をデフォルトに戻す */
        printf("\x1b[0m");      /* デフォルトに戻す */
    }
    
    printf("\n");
    return 0;
}
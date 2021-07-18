#include <stdio.h>
#include "Graphics.h"

using namespace suzu;

void testCopyOrClonePointNotAffectsOriginObj(){
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
        return;
    }

    p.x = 3;
    res &= (pequal.x == 2);
    res &= (pclone.x == 2);
    res &= (pcopy.x == 2);
    if(res != true){
        printf("origin affects copy object!\n");
        return;
    }

    printf("%s --- ok\n", __func__);
}

void testCopyOrCloneRectNotAffectsOriginObj(){
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
        return;
    }

    rightBottom.x = 0;
    res &= (rightBottom.x == 0);
    res &= (r.rightBottom.x == 10);

    if(res != true){
        printf("%s --- NG. change originPoint affects RectClassMember.\n", __func__);
        return;
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
    if(res != true){
        printf("%s --- NG. change originRect affects RectClassMember.\n", __func__);
        return;
    }


    printf("%s --- ok\n", __func__);
}

int main(int argc, char** argv){
    printf("\n");
    testCopyOrClonePointNotAffectsOriginObj();
    testCopyOrCloneRectNotAffectsOriginObj();
    printf("\n");
    return 0;
}
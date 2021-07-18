#include <stdio.h>
#include <functional>
#include "CalcRectPosition.h"

using namespace suzu;
constexpr double NEAR_ZERO = 0.0001;

void AllocateMemoryCalledOnlyOneTime(){
    class Mock : public suzu::CalcRectPosition {
        public:
            int allocateParamsMemoryCount;
            int calcParameterCount;
            int calcCount;
            Mock(){
                allocateParamsMemoryCount = 0;
                calcParameterCount = 0;
                calcCount = 0;
            }

            bool _calc(const suzu::DPoint& point, suzu::DPoint& dstPoint){
                this->calcCount++;
                return suzu::CalcRectPosition::calcPosition(point, dstPoint);
            }

        protected:
            virtual bool allocateParamsMemory() override{
                this->allocateParamsMemoryCount++;
                suzu::CalcRectPosition::allocateParamsMemory();
                return true;
            };
            virtual bool calcParameter() override{ 
                this->calcParameterCount++;
                return true;
            };
            virtual bool checkError() override{
                return true;
            }
    };

    Mock mock;
    suzu::DPoint p;
    bool res = true;
    mock._calc(p, p);

    res &= ( mock.allocateParamsMemoryCount == 1);
    res &= ( mock.calcParameterCount == 1);
    res &= ( mock.calcCount == 1);

    mock._calc(p, p);

    res &= ( mock.allocateParamsMemoryCount == 1);
    res &= ( mock.calcParameterCount == 1);
    res &= ( mock.calcCount == 2);

    if( res == false){
        printf("%s --- NG.\n", __func__);
    }

    printf("%s --- ok\n", __func__);
}

void calcPositionTest(){
    suzu::CalcRectPosition p;
    bool isOK = true;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 10);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    DRect dstR;
    dstR.leftTop = suzu::DPoint(0, 0);
    dstR.rightTop = suzu::DPoint(100, 30);
    dstR.leftBottom = suzu::DPoint(30, 100);
    dstR.rightBottom = suzu::DPoint(100, 70);


    isOK &= p.setSrcRect(srcR);
    isOK &= p.setDstRect(dstR);

    DPoint res;
    p.calcPosition(DPoint(10, 10), res);
    isOK &= (abs(res.x - 0) < NEAR_ZERO);
    isOK &= (abs(res.y - 0) < NEAR_ZERO);

    p.calcPosition(DPoint(90, 10), res);
    isOK &= (abs(res.x - 100) < NEAR_ZERO);
    isOK &= (abs(res.y - 30) < NEAR_ZERO);

    p.calcPosition(DPoint(90, 90), res);
    isOK &= (abs(res.x - 100) < NEAR_ZERO);
    isOK &= (abs(res.y - 70) < NEAR_ZERO);
    
    p.calcPosition(DPoint(10, 90), res);
    isOK &= (abs(res.x - 30) < NEAR_ZERO);
    isOK &= (abs(res.y - 100) < NEAR_ZERO);


    if(isOK != true){
        printf("%s --- NG\n", __func__);
        return;
    }

    printf("%s --- ok\n", __func__);

}

void calcInnerRect(){
    suzu::CalcRectPosition p;
    bool isOK = true;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 10);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    DRect dstR;
    dstR.leftTop = suzu::DPoint(0, 0);
    dstR.rightTop = suzu::DPoint(100, 0);
    dstR.leftBottom = suzu::DPoint(0, 100);
    dstR.rightBottom = suzu::DPoint(100, 100);


    p.setSrcRect(srcR);
    p.setDstRect(dstR);

    DPoint res;
    p.calcPosition(DPoint(10, 10), res);
    isOK &= (abs(res.x - 0) < NEAR_ZERO);
    isOK &= (abs(res.y - 0) < NEAR_ZERO);


    p.calcPosition(DPoint(90, 10), res);
    isOK &= (abs(res.x - 100) < NEAR_ZERO);
    isOK &= (abs(res.y - 0) < NEAR_ZERO);


    p.calcPosition(DPoint(90, 90), res);
    isOK &= (abs(res.x - 100) < NEAR_ZERO);
    isOK &= (abs(res.y - 100) < NEAR_ZERO);

    p.calcPosition(DPoint(10, 90), res);
    isOK &= (abs(res.x - 0) < NEAR_ZERO);
    isOK &= (abs(res.y - 100) < NEAR_ZERO);

    if(isOK != true){
        printf("%s --- NG\n", __func__);
        return;
    }

    printf("%s --- ok\n", __func__);

}

void calcOuterRect(){
    suzu::CalcRectPosition p;
    bool isOK = true;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 10);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    DRect dstR;
    dstR.leftTop = suzu::DPoint(0, 0);
    dstR.rightTop = suzu::DPoint(100, 0);
    dstR.leftBottom = suzu::DPoint(0, 100);
    dstR.rightBottom = suzu::DPoint(100, 100);


    p.setSrcRect(dstR);
    p.setDstRect(srcR);

    DPoint res;
    p.calcPosition(DPoint(0, 0), res);
    isOK &= (abs(res.x - 10) < NEAR_ZERO);
    isOK &= (abs(res.y - 10) < NEAR_ZERO);

    p.calcPosition(DPoint(100, 0), res);
    isOK &= (abs(res.x - 90) < NEAR_ZERO);
    isOK &= (abs(res.y - 10) < NEAR_ZERO);

    p.calcPosition(DPoint(100, 100), res);
    isOK &= (abs(res.x - 90) < NEAR_ZERO);
    isOK &= (abs(res.y - 90) < NEAR_ZERO);

    p.calcPosition(DPoint(0, 100), res);
    isOK &= (abs(res.x - 10) < NEAR_ZERO);
    isOK &= (abs(res.y - 90) < NEAR_ZERO);
    
    if(isOK != true){
        printf("%s --- NG\n", __func__);
        return;
    }

    printf("%s --- ok\n", __func__);

}

void setNotRectangleReturnsFalse(){

    suzu::CalcRectPosition p;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 11);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    bool res = p.setSrcRect(srcR);

    if(res != false){
        printf("%s --- NG\n", __func__);
        return;
    }

    printf("%s --- ok\n", __func__);


}

void calcPositionWithNoSetupReturnsFalse(){
    CalcRectPosition p;
    DPoint dst;
    if(true == p.calcPosition(DPoint(0, 0), dst)){
        printf("%s --- NG\n", __func__);
        return;
    };
    printf("%s --- ok\n", __func__);
}

void calcPositionOutOfSrcRectAreaReturnsFalse(){
    suzu::CalcRectPosition p;
    bool isOK = true;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 10);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    DRect dstR;
    dstR.leftTop = suzu::DPoint(0, 0);
    dstR.rightTop = suzu::DPoint(100, 0);
    dstR.leftBottom = suzu::DPoint(0, 100);
    dstR.rightBottom = suzu::DPoint(100, 100);


    p.setSrcRect(srcR);
    p.setDstRect(dstR);

    DPoint dstPoint;

    if(true == p.calcPosition(DPoint(0, 10), dstPoint)){
        printf("%s --- NG\n", __func__);
        return;
    }

    printf("%s --- ok\n", __func__);
    
}

int main(int argc, char** argv){

    printf("\n");

    AllocateMemoryCalledOnlyOneTime();
    calcPositionTest();
    calcInnerRect();
    calcOuterRect();
    setNotRectangleReturnsFalse();
    calcPositionWithNoSetupReturnsFalse();
    calcPositionOutOfSrcRectAreaReturnsFalse();

    printf("\n");

    return 0;
}
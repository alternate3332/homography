#include <stdio.h>
#include <functional>
#include <vector>
#include <tuple>
#include <iostream>
#include <string>
#include "CalcRectPosition.h"

using namespace suzu;
const double NEAR_ZERO = 0.0001;

bool AllocateMemoryCalledOnlyOneTime(){
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

    return res;
}

bool calcPositionTest(){
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


    return isOK;
}

bool calcInnerRect(){
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

    return isOK;
}

bool calcOuterRect(){
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

    p.calcPosition(DPoint(50, 50), res);
    isOK &= (abs(res.x - 50) < NEAR_ZERO);
    isOK &= (abs(res.y - 50) < NEAR_ZERO);
    
    return isOK;
}

bool setNotRectangleReturnsFalse(){

    suzu::CalcRectPosition p;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 11);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.leftBottom = suzu::DPoint(10, 90);
    srcR.rightBottom = suzu::DPoint(90, 90);

    bool res = p.setSrcRect(srcR);

    return res == false;
}

bool calcPositionWithNoSetupReturnsFalse(){
    CalcRectPosition p;
    DPoint dst;
    return false == p.calcPosition(DPoint(0, 0), dst);
}

bool calcPositionOutOfSrcRectAreaReturnsFalse(){
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

    return false == p.calcPosition(DPoint(0, 10), dstPoint);
     
}

int main(int argc, char** argv){

    typedef std::tuple<std::string, std::function<bool(void)> > mytuple;

    std::vector< mytuple > test;

    printf("\n");

    test.push_back(mytuple("AllocateMemoryCalledOnlyOneTime",AllocateMemoryCalledOnlyOneTime));
    test.push_back(mytuple("calcPositionTest",calcPositionTest));
    test.push_back(mytuple("calcInnerRect",calcInnerRect));
    test.push_back(mytuple("calcOuterRect",calcOuterRect));
    test.push_back(mytuple("setNotRectangleReturnsFalse",setNotRectangleReturnsFalse));
    test.push_back(mytuple("calcPositionWithNoSetupReturnsFalse",calcPositionWithNoSetupReturnsFalse));
    test.push_back(mytuple("calcPositionOutOfSrcRectAreaReturnsFalse",calcPositionOutOfSrcRectAreaReturnsFalse));

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
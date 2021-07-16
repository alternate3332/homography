#include <stdio.h>
#include "CalcRectPosition.h"

using namespace suzu;

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
    };

    Mock mock;
    suzu::DPoint p;
    mock._calc(p, p);

    printf("allocateParamsMemoryCount : %d\n", mock.allocateParamsMemoryCount);
    printf("calcParameterCount : %d\n", mock.calcParameterCount);
    printf("calcCount : %d\n", mock.calcCount);

    mock._calc(p, p);

    printf("allocateParamsMemoryCount : %d\n", mock.allocateParamsMemoryCount);
    printf("calcParameterCount : %d\n", mock.calcParameterCount);
    printf("calcCount : %d\n", mock.calcCount);

}

void calcTest(){
    suzu::CalcRectPosition p;
    
    DRect srcR;
    srcR.leftTop = suzu::DPoint(10, 10);
    srcR.rightTop = suzu::DPoint(90, 10);
    srcR.rightBottom = suzu::DPoint(90, 90);
    srcR.leftBottom = suzu::DPoint(10, 90);

    DRect dstR;
    dstR.leftTop = suzu::DPoint(0, 0);
    dstR.rightTop = suzu::DPoint(100, 0);
    dstR.rightBottom = suzu::DPoint(100, 200);
    dstR.leftBottom = suzu::DPoint(0, 200);


    p.setSrcRect(srcR);
    p.setDstRect(dstR);

    DPoint res;
    p.calcPosition(DPoint(10, 10), res);
    printf("(x, y)=(%.2f, %.2f)\n", res.x, res.y);
    p.calcPosition(DPoint(100, 0), res);
    printf("(x, y)=(%.2f, %.2f)\n", res.x, res.y);
    p.calcPosition(DPoint(0, 100), res);
    printf("(x, y)=(%.2f, %.2f)\n", res.x, res.y);
    p.calcPosition(DPoint(100, 100), res);
    printf("(x, y)=(%.2f, %.2f)\n", res.x, res.y);

    p.calcPosition(DPoint(50, 50), res);
    printf("(x, y)=(%.2f, %.2f)\n", res.x, res.y);
}

int main(int argc, char** argv){

    //AllocateMemoryCalledOnlyOneTime();
    calcTest();

    return 0;
}
#include "CalcRectPosition.h"

using namespace suzu;

CalcRectPosition::CalcRectPosition(){
    this->srcRect = DRect();
    this->dstRect = DRect();
}

CalcRectPosition::CalcRectPosition(const DRect& _srcRect, const DRect& _dstRect): srcRect(DRect()), dstRect(DRect()) {
    this->srcRect = _srcRect;
    this->dstRect = _dstRect;
}

void CalcRectPosition::setSrcRect(const DRect& r){
    this->srcRect = r;
    this->releaseParams();
}

void CalcRectPosition::setDstRect(const DRect& r){
    this->dstRect = r;
    this->releaseParams();
}

void CalcRectPosition::releaseParams(){
    this->params = nullptr;
}


bool CalcRectPosition::createParamIfNotPrepared(){

    if(this->params != nullptr){
        return true;
    }

    bool res = this->allocateParamsMemory();
    if(res != true){
        return false;
    }
    
    res = this->calcParameter();
    if(res != true){
        this->releaseParams();
        return false;
    }

    return true;
};
          
bool CalcRectPosition::calcPosition(const DPoint& point, DPoint& dstPoint){
    DPoint p;
    bool res = this->createParamIfNotPrepared();
    if(res != true){
        printf("createParamIfNotPrepared failed. %s\n", __func__);
        return res;
    }

    // calc parameter as 0 ~ 1 range position.
    // so positions also must be normalized.
    const double srcW = (srcRect.rightTop.x - srcRect.leftTop.x);
    const double srcH = (srcRect.leftBottom.y - srcRect.leftTop.y);
    const double shiftX = point.x - srcRect.leftTop.x;
    const double shiftY = point.y - srcRect.leftTop.y;

    const double normalizedX = 1.0 - shiftX / srcW;
    const double normalizedY = shiftY / srcH;

    KeystoneParameters *paramsP = this->params.get();
    const double common = params->g * normalizedX + params->h * normalizedY + 1;

    dstPoint.x = (paramsP->a * normalizedX + paramsP->b * normalizedY + paramsP->c) / common;
    dstPoint.y = (paramsP->d * normalizedX + paramsP->e * normalizedY + paramsP->f) / common;

    return true;
}


bool CalcRectPosition::allocateParamsMemory(){
    try{
        std::unique_ptr<KeystoneParameters> param(new KeystoneParameters());
        this->params = std::move(param);
    } catch(...){
        return false;
    }

    return true;
};

bool CalcRectPosition::calcParameter(){
    double x1, x2, x3, x4, y1, y2, y3, y4;
    const DRect r = this->dstRect;
    const double NEAR_ZERO = 0.0001;
    
    DPoint points[] = {r.rightTop, r.leftTop, r.rightBottom, r.leftBottom}; //
 
    x1 = points[0].x;
    y1 = points[0].y;
    x2 = points[1].x;
    y2 = points[1].y;
    x3 = points[2].x;
    y3 = points[2].y;
    x4 = points[3].x;
    y4 = points[3].y;

    // x2, x4
    if(abs(x2 - x4) < NEAR_ZERO){
        x4 -= NEAR_ZERO;
    }
    // y4, y3
    if(abs(y3 - y4) < NEAR_ZERO){
        y4 -= NEAR_ZERO;
    }
    // x4, x3
    if(abs(x3 - x4) < NEAR_ZERO){
        x4 -= NEAR_ZERO;
    }
    // y4, y2
    if(abs(y2 - y4) < NEAR_ZERO){
        y4 -= NEAR_ZERO;
    }
    double a, b, c, d, e, f, g, h;
    KeystoneParameters* paramsP = this->params.get();
    h = ((x1 - x2 - x3 + x4 )*( y4 - y2 ) - ( y1 - y2 - y3 + y4 )*( x4 - x2 ) ) / ((x4-x2)*(y4-y3)-(x4-x3)*(y4-y2));
    g = (-x1+x2+x3-x4-(x4-x3)*h) / (x4 - x2);
    a = (g+1)*x2 - x1;
    d = (g+1)*y2 - y1;
    b = (h+1)*x3 - x1;
    e = (h+1)*y3 - y1;
    c = x1;
    f = y1;

    paramsP->a = a;
    paramsP->b = b;
    paramsP->c = c;
    paramsP->d = d;
    paramsP->e = e;
    paramsP->f = f;
    paramsP->g = g;
    paramsP->h = h;

    return true;
};
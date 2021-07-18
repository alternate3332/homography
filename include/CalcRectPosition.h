#ifndef __SUZU_CALCRECTPOSITION_H__
#define __SUZU_CALCRECTPOSITION_H__

#include <memory>
#include "Graphics.h"

namespace suzu {
    using DRect = Rect<double>;
    using DPoint = Point<double>;

    class CalcRectPosition {
        public:
            CalcRectPosition();
            bool setSrcRect(const DRect& r);
            bool setDstRect(const DRect& r);
            bool calcPosition(const DPoint& point, DPoint& dstPoint);

            CalcRectPosition(const CalcRectPosition &) = delete;
            CalcRectPosition &operator=(const CalcRectPosition &) = delete;

        protected:
            virtual bool checkError();
            virtual bool isRectangle(const DRect& rect);
            virtual bool isAvailableArea();
            
            virtual bool allocateParamsMemory();
            virtual bool calcParameter();
            virtual void releaseParams();
            virtual bool createParamIfNotPrepared();

        private:
            using KeystoneParameters = struct {
                double a;
                double b;
                double c;
                double d;
                double e;
                double f;
                double g;
                double h;
            };

            std::unique_ptr<KeystoneParameters> params;
            DRect srcRect;
            DRect dstRect;
            DPoint target;

    };
};

#endif
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
            CalcRectPosition(const DRect& _srcRect, const DRect& _dstRect);
            void setSrcRect(const DRect& r);
            void setDstRect(const DRect& r);
            bool calcPosition(const DPoint& point, DPoint& dstPoint);

        protected:
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

    };
};

#endif
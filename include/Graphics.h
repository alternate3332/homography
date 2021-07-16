#ifndef __SUZU_GRAPHICS_H__
#define __SUZU_GRAPHICS_H__

namespace suzu {

    template<typename T>
    class Point{
        public:
            T x;
            T y;

            Point(){
                this->x = 0;
                this->y = 0;
            }

            Point(T x, T y){
                this->x = x;
                this->y = y;
            }

            Point(const Point<T>& p){
                this->x = p.x;
                this->y = p.y;
            }
    };

    template<typename T>
    class Rect{
        public:
            Point<T> leftTop;
            Point<T> rightTop;
            Point<T> rightBottom;
            Point<T> leftBottom;

        Rect(){
            leftTop = Point<T>(0, 0);
            rightTop = Point<T>(0, 0);
            rightBottom = Point<T>(0, 0);
            leftBottom = Point<T>(0, 0);
        }

        Rect(const Rect& r){
            this->leftTop = r.leftTop;
            this->rightBottom = r.rightBottom;
            this->leftBottom = r.leftBottom;
            this->rightTop = r.rightTop;
        }
    };
};

#endif
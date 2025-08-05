#include "CalculateIsPointNearLine2D.h"
#include <cmath>

namespace Graphics
{


    CalculateIsPointNearLine2D::CalculateIsPointNearLine2D()
    {

    }

    CalculateIsPointNearLine2D::~CalculateIsPointNearLine2D()
    {

    }

    bool CalculateIsPointNearLine2D::isNear(QPoint linePt0, QPoint linePt1, QPoint pt, bool extension, double tolerence)
    {
        /// define line function : Ax + By + C = 0
        int A = linePt1.y() - linePt0.y();
        int B = linePt0.x() - linePt1.x();
        int C = linePt1.x() * linePt0.y() - linePt0.x() * linePt1.y();

        /// calculate distance to line
        double distance = abs(A * pt.x() + B * pt.y() + C) / sqrt(A * A + B * B);

        /// is distance is small than tolerence
        if (distance <= tolerence)
        {
            /// not considering extension
            if (!extension)
            {
                /// if point on segment
                double dx = linePt1.x() - linePt0.x();
                double dy = linePt1.y() - linePt0.y();
                double t = ((pt.x() - linePt0.x()) * dx + (pt.y() - linePt0.y()) * dy) / (dx * dx + dy * dy);

                return (t >= 0.0 && t <= 1.0);
            }
            else
                return true;
        }
        return false;
    }

}
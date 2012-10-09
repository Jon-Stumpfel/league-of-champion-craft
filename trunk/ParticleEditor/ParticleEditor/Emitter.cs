using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace ParticleEditor
{
    class Emitter
    {
        private Color ColorStart, ColorEnd;

        private int AlphaStart, AlphaEnd;

        private float Angle, AngleRotation, RotationStart, RotationEnd,
            ScaleStart, ScaleEnd, SpawnMax, SpawnMin, LifeMax, lifeMin, Radius;

        private Vector2D VelStartMin, VelStartMax, VelEndMin,
                VelEndMax, ImgPos, Origin, Width, Height, Point;

    }
}

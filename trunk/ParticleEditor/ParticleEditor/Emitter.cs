using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

enum Shape { LINE, SQUARE, CIRCLE, POINT };

namespace ParticleEditor
{
    class Emitter
    {
        private Color colorStart, colorEnd;

        public Color ColorEnd
        {
            get { return colorEnd; }
            set { colorEnd = value; }
        }

        public Color ColorStart
        {
            get { return colorStart; }
            set { colorStart = value; }
        }

        private int alphaStart, alphaEnd, particleCount, imgHeight, imgWidth;

        public int AlphaStart
        {
            get { return alphaStart; }
            set { alphaStart = value; }
        }

        public int AlphaEnd
        {
            get { return alphaEnd; }
            set { alphaEnd = value; }
        }

        public int ParticleCount
        {
            get { return particleCount; }
            set { particleCount = value; }
        }

        public int ImgHeight
        {
            get { return imgHeight; }
            set { imgHeight = value; }
        }

        public int ImgWidth
        {
            get { return imgWidth; }
            set { imgWidth = value; }
        }

        private float angle, angleRotation, rotationStart, rotationEnd,
            scaleStart, scaleEnd, spawnMax, spawnMin, lifeMax, lifeMin, radius;

        public float Angle
        {
            get { return angle; }
            set { angle = value; }
        }

        public float AngleRotation
        {
            get { return angleRotation; }
            set { angleRotation = value; }
        }

        public float RotationStart
        {
            get { return rotationStart; }
            set { rotationStart = value; }
        }

        public float RotationEnd
        {
            get { return rotationEnd; }
            set { rotationEnd = value; }
        }

        public float ScaleStart
        {
            get { return scaleStart; }
            set { scaleStart = value; }
        }

        public float ScaleEnd
        {
            get { return scaleEnd; }
            set { scaleEnd = value; }
        }

        public float SpawnMax
        {
            get { return spawnMax; }
            set { spawnMax = value; }
        }

        public float SpawnMin
        {
            get { return spawnMin; }
            set { spawnMin = value; }
        }

        public float LifeMax
        {
            get { return lifeMax; }
            set { lifeMax = value; }
        }

        public float LifeMin
        {
            get { return lifeMin; }
            set { lifeMin = value; }
        }

        public float Radius
        {
            get { return radius; }
            set { radius = value; }
        }

        private Vector2D velStartMin, velStartMax, velEndMin,
                velEndMax, imgPos, origin, width, height, point;

        internal Vector2D VelStartMin
        {
            get { return velStartMin; }
            set { velStartMin = value; }
        }

        internal Vector2D VelStartMax
        {
            get { return velStartMax; }
            set { velStartMax = value; }
        }

        internal Vector2D VelEndMin
        {
            get { return velEndMin; }
            set { velEndMin = value; }
        }

        internal Vector2D VelEndMax
        {
            get { return velEndMax; }
            set { velEndMax = value; }
        }

        internal Vector2D ImgPos
        {
            get { return imgPos; }
            set { imgPos = value; }
        }

        internal Vector2D Origin
        {
            get { return origin; }
            set { origin = value; }
        }

        internal Vector2D Width
        {
            get { return width; }
            set { width = value; }
        }

        internal Vector2D Height
        {
            get { return height; }
            set { height = value; }
        }

        internal Vector2D Point
        {
            get { return point; }
            set { point = value; }
        }

        private bool looping;

        public bool Looping
        {
            get { return looping; }
            set { looping = value; }
        }

        private Shape type;

        internal Shape Type
        {
            get { return type; }
            set { type = value; }
        }
    }
}

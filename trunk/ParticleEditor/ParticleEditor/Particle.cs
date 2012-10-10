using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;

namespace ParticleEditor
{
    struct Vector2D
    {
        public float x, y;

        public float Y
        {
            get { return y; }
            set { y = value; }
        }

        public float X
        {
            get { return x; }
            set { x = value; }
        }

        public void Init(float Velx, float Vely)
        {
            x = Velx;
            y = Vely;
        }
    }

    class Particle
    {
        private Color color;

        public Color Color
        {
            get { return color; }
            set { color = value; }
        }

        private float scale, rotation, curLife, maxLife;

        public float MaxLife
        {
            get { return maxLife; }
            set { maxLife = value; }
        }

        public float CurLife
        {
            get { return curLife; }
            set { curLife = value; }
        }

        public float Rotation
        {
            get { return rotation; }
            set { rotation = value; }
        }

        public float Scale
        {
            get { return scale; }
            set { scale = value; }
        }

        private Vector2D velocityStart, velocityEnd, curVelocity;

        internal Vector2D CurVelocity
        {
            get { return curVelocity; }
            set { curVelocity = value; }
        }

        internal Vector2D VelocityEnd
        {
            get { return velocityEnd; }
            set { velocityEnd = value; }
        }

        internal Vector2D VelocityStart
        {
            get { return velocityStart; }
            set { velocityStart = value; }
        }

        Vector2D pos;

        internal Vector2D Pos
        {
            get { return pos; }
            set { pos = value; }
        }

        private Rectangle source;

        public Rectangle Source
        {
            get { return source; }
            set { source = value; }
        }

        public void Update(float fElapsedTime)
        {
            pos.x += curVelocity.x * fElapsedTime;
            pos.y += curVelocity.y * fElapsedTime;

            curLife += fElapsedTime;
        }

        public void Render()
        {
               // HOW USE WRAPPER!!?!
        }
    }
}

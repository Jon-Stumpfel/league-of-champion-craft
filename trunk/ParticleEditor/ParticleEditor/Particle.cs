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
    }

    class Particle
    {
        private Color color;

        public Color Color
        {
            get { return color; }
            set { color = value; }
        }

        private int alpha;

        public int Alpha
        {
            get { return alpha; }
            set { alpha = value; }
        }

        private float scale, rotation, life;

        public float Life
        {
            get { return life; }
            set { life = value; }
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

        private Vector2D velocity;

        internal Vector2D Velocity
        {
            get { return velocity; }
            set { velocity = value; }
        }

        private Rectangle source;

        public Rectangle Source
        {
            get { return source; }
            set { source = value; }
        }
    }
}

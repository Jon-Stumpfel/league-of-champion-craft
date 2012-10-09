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

        private int alpha;

        private float scale, rotation, life;

        private Vector2D velocity;

        private Rectangle source;
    }
}

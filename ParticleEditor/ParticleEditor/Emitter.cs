using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Drawing.Drawing2D;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using System.Diagnostics;
using System.Threading;

enum Shape { LINE, SQUARE, CIRCLE, POINT };

namespace ParticleEditor
{
    class Emitter
    {
        private static Emitter Instance;

        internal static Emitter Instance1
        {
            get 
            {
                if (Instance == null)
                    Instance = new Emitter();
                return Instance; 
            }
        }

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

        private int particleCount, imgHeight, imgWidth;

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

        private bool looping, alive;

        public bool Alive
        {
            get { return alive; }
            set { alive = value; }
        }

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

        private List<Particle> particles = new List<Particle>();

        private int numSpawned;

        public int NumSpawned
        {
            get { return numSpawned; }
            set { numSpawned = value; }
        }

        private float spawnRate, spawnTimer;
        private Stopwatch stopWatch = new Stopwatch();

        public void Run()
        {
            Emitter self = Emitter.Instance1;
            while (alive)
            {
                if (self.stopWatch.IsRunning == false)
                    self.stopWatch.Start();
                float elapsedtime = self.stopWatch.ElapsedTicks;
                if (elapsedtime > 0.1f)
                    elapsedtime = 0.1f;
                self.Update(elapsedtime);
                self.Render();
                self.stopWatch.Restart();
            }
        }

        public void Update(float fElapsedTime)
        {
            if (spawnRate < spawnTimer)
            {
                if( particles.Count > numSpawned )
                    numSpawned++;
                spawnTimer = 0;
                float l = new Random().Next((int)spawnMax * 100, (int)spawnMin * 00000100);
                spawnTimer = l / 100.0f;
            }

            spawnTimer += fElapsedTime;

            for (int i = 0; i < numSpawned; i++ )
            {
                particles[i].Update(fElapsedTime);

                if (particles[i].CurLife >= particles[i].CurLife)
                {
                    particles.Remove(particles[i]);

                    if (particles.Count == 0)
                    {
                        if (looping == true)
                            InitParticle();
                        else
                            alive = false;
                    }

                    i--;
                    numSpawned--;
                    continue;
                }

                float time = particles[i].MaxLife;

                // Color changing over time
                Color oldColor = particles[i].Color;
                float dtA, dtR, dtG, dtB;

                dtA = (float)(colorEnd.A - colorStart.A) / time;
                dtR = (float)(colorEnd.R - colorStart.R) / time;
                dtG = (float)(colorEnd.G - colorStart.G) / time;
                dtB = (float)(colorEnd.B - colorStart.B) / time;
                dtA *= fElapsedTime;
                dtR *= fElapsedTime; 
                dtG *= fElapsedTime;
                dtB *= fElapsedTime;

                Color newColor = Color.FromArgb((int)dtA, (int)dtR, (int)dtG, (int)dtB);
                particles[i].Color = newColor;

                // Rotation changing over time
                float oldRot = particles[i].Rotation;
                float dtRot = (rotationEnd - rotationStart) / time;
                dtRot *= fElapsedTime;
                float newRot = dtRot + oldRot;
                particles[i].Rotation = newRot;

                // Scale changing over time
                float oldScale = particles[i].Scale;
                float dtScale = (scaleEnd - scaleStart) / time;
                dtScale *= fElapsedTime;
                float newScale = dtScale + oldScale;
                particles[i].Scale = newScale;

                // Velocity changing over time
                Vector2D oldVel = particles[i].CurVelocity;
                float dtX = (particles[i].VelocityEnd.x - particles[i].VelocityStart.x) / time;
                float dtY = (particles[i].VelocityEnd.y - particles[i].VelocityStart.y) / time;

                Vector2D newVel = new Vector2D();
                newVel.Init(dtX + oldVel.x, dtY + oldVel.y);
                particles[i].CurVelocity = newVel;
            }
        }

        public void Render()
        {
            for (int i = 0; i < numSpawned; i++)
            {
                particles[i].Render();
            }
        }

        public void InitParticle()
        {
            if( particles.Count != 0 )
                particles.Clear();
            Random rand = new Random();
            rand.Next();
            for (int i = 0; i < particleCount; i++)
            {
                // Sets values to the starting values
                Particle tmp = new Particle();
                tmp.Color = colorStart;
                tmp.Rotation = rotationStart;
                tmp.Scale = scaleStart;
                tmp.Rotation = rotationStart;
                tmp.Source = new Rectangle((int)imgPos.x, (int)imgPos.y, imgHeight, imgWidth);

                // Finds random values
                Vector2D Maxdir = new Vector2D();
                Maxdir.x = float.Parse(Math.Sin((angle + angleRotation) * Math.PI / 180).ToString());
                Maxdir.y = float.Parse(Math.Cos((angle + angleRotation) * Math.PI / 180).ToString());
                Vector2D Mindir = new Vector2D();
                Mindir.x = float.Parse(Math.Sin(angleRotation * Math.PI / 180).ToString());
                Mindir.y = float.Parse(Math.Cos(angleRotation * Math.PI / 180).ToString());

                // Finds the direction of the particle based on the angle of projection
                float dir = (float)rand.Next((int)Mindir.x * 1000, (int)Maxdir.x * 1000);

                // Finds the start velocity
                Vector2D vel;  
                float x = (float)rand.Next((int)velStartMin.x * 100, (int)velStartMax.x *100);
                float y = (float)rand.Next((int)velStartMin.y * 100, (int)velStartMax.y * 100);
                vel.x = (dir / 1000.0f) * (x / 100.0f);
                vel.y = (dir / 1000.0f) * (y / 100.0f);
                tmp.VelocityStart = vel;

                // Finds the end velocity
                x = (float)rand.Next((int)velEndMin.x * 100, (int)velEndMax.x * 100);
                y = (float)rand.Next((int)velEndMin.y * 100, (int)velEndMax.y * 100);
                vel.x = (dir / 1000.0f) * (x / 100.0f);
                vel.y = (dir / 1000.0f) * (y / 100.0f);
                tmp.VelocityEnd = vel;

                tmp.CurVelocity = tmp.VelocityStart;

                float life = (float)rand.Next((int)lifeMin * 100, (int)lifeMax * 100);
                tmp.MaxLife = (life / 100.0f);

                particles.Add(tmp);
            }

            float sr = rand.Next( (int)spawnMin * 100, (int)spawnMax * 100 );
            spawnRate = sr / 100.0f;
            spawnTimer = 0;
        }
    }
}

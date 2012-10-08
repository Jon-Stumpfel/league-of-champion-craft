#include "StdAfx.h"
#include "Emitter.h"

#include "ParticleManager.h"
#include "Particle.h"
#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_Direct3D.h"
#include <ctime>

CEmitter::CEmitter(void)
{
}


CEmitter::~CEmitter(void)
{
}

bool CEmitter::Alive( void )
{
	if( m_vAliveParticles.size() == 0 )
		return false;
	else 
		return true;
}

void CEmitter::Clear( void )
{
	while( m_vAliveParticles.size() != 0 )
	{
		delete m_vAliveParticles[0];
		m_vAliveParticles.erase(m_vAliveParticles.begin());
	}
}

void CEmitter::LoadParticles( PRTCL_TYPE eType, Vec2Df sPos )
{
	srand( unsigned int(time(0)) );
	rand();

	TiXmlDocument doc;

	// Loads the file for the specific particle7
	switch( eType )
	{
	case TEST:
		{
			if( doc.LoadFile( "Assets/Particles/Test.xml" ) == false )
				return;
		}
	};

	m_sEmitPos = sPos;
	m_fSpawnTimer = 0;
	m_nNumSpawned = 0;

	// Populates Emitter with the range of values
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
		return;

	m_vAliveParticles.clear();

	TiXmlElement* pImageData = pRoot->FirstChildElement( "ImageData" );

	m_szPath = pImageData->Attribute( "ImagePath" );
	pImageData->Attribute( "Height", &m_nHeight );
	pImageData->Attribute( "Width", &m_nWidth );
	pImageData->Attribute( "PosX", &m_sImgPos.nPosX );
	pImageData->Attribute( "PosY", &m_sImgPos.nPosY );

	pImageData->Attribute( "NumParticles", &m_nNumParticles );
	pImageData->QueryFloatAttribute( "MinLife", &m_fMinLife );
	pImageData->QueryFloatAttribute( "MaxLife", &m_fMaxLife );

	int tmp;
	pImageData->Attribute( "IsLooping", &tmp);
	if( tmp )
		m_bLooping = true;
	else
		m_bLooping = false;

	float min, max;
	pImageData->QueryFloatAttribute( "MinSpawnRate", &min );
	pImageData->QueryFloatAttribute( "MaxSpawnRate", &max );
	m_nMaxSpawnRate = int(max * 100);
	m_nMinSpawnRate = int(min * 100);

	/*pImageData->Attribute( "SourceBlend", &m_nSourceBlend );
	pImageData->Attribute( "DestBlend", &m_nDestBlend );*/

	pImageData->Attribute( "StartingA", &m_sStartColor.a );
	pImageData->Attribute( "EndingA", &m_sEndColor.a );

	pImageData->Attribute( "StartingR", &m_sStartColor.r );
	pImageData->Attribute( "EndingR", &m_sEndColor.r );

	pImageData->Attribute( "StartingG", &m_sStartColor.g );
	pImageData->Attribute( "EndingG", &m_sEndColor.g );

	pImageData->Attribute( "StartingB", &m_sStartColor.b );
	pImageData->Attribute( "EndingB", &m_sEndColor.b );

	pImageData->QueryFloatAttribute( "StartingRotation", &m_fStartRot );
	pImageData->QueryFloatAttribute( "EndingRotation", &m_fEndRot );
	pImageData->QueryFloatAttribute( "StartingScale", &m_fStartScale );
	pImageData->QueryFloatAttribute( "EndingScale", &m_fEndScale );
	pImageData->QueryFloatAttribute( "MinDirX", &m_sMinDir.fVecX );
	pImageData->QueryFloatAttribute( "MaxDirX", &m_sMaxDir.fVecX );
	pImageData->QueryFloatAttribute( "MinDirY", &m_sMinDir.fVecY );
	pImageData->QueryFloatAttribute( "MaxDirY", &m_sMaxDir.fVecY );

	float s, e;

	pImageData->QueryFloatAttribute( "StartVel", &s );
	pImageData->QueryFloatAttribute( "EndVel", &e );

	m_sStartVel.fVecX = s;
	m_sStartVel.fVecY = s;

	m_sEndVel.fVecX = e;
	m_sEndVel.fVecY = e;

	// tell the graphics manager where the image for each particle is
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	TCHAR conversion[100];

	mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);

	TSTRING file = conversion;

	pGM->LoadImageW( file, _T("Particle"), D3DCOLOR_ARGB(1, 1, 1, 1) );

	m_fSpawnRate = (rand() % (m_nMinSpawnRate - m_nMaxSpawnRate) + 1 + m_nMinSpawnRate)/100.0f;

	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		// Finds the random life time
		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float((rand() % (maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		// Finds a random velocity
		int maxDirX = int(m_sMaxDir.fVecX);
		int maxDirY = int(m_sMaxDir.fVecY);
		int minDirX = int(m_sMinDir.fVecX);
		int minDirY = int(m_sMinDir.fVecY);

		int DirX = rand() % (maxDirX - minDirX + 1) + minDirX;
		int DirY = rand() % (maxDirY - minDirY + 1) + minDirY;

		Vec2Df Dir;
		Dir.fVecX = float(DirX);
		Dir.fVecY = float(DirY);

		Vec2Df start = m_sStartVel;
		start.fVecX *= Dir.fVecX;	
		start.fVecY *= Dir.fVecY;

		RECT src = { m_sImgPos.nPosX, m_sImgPos.nPosY, m_sImgPos.nPosX + m_nWidth, m_sImgPos.nPosY + m_nHeight };

		CParticle* tParticle = new CParticle(m_sEmitPos, Dir, start, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

		m_vAliveParticles.push_back( tParticle );
	}
}

void CEmitter::Render( void )
{
	for( unsigned int i = 0; i < m_nNumSpawned; i++ )
		m_vAliveParticles[i]->Render();
}

void CEmitter::Update( float fElapsedTime )
{
	// Checks to see if it can spawn another particle
	// then adds one to the number spawned
	if( m_fSpawnTimer > m_fSpawnRate )
	{
		if( m_vAliveParticles.size() > m_nNumSpawned )
			m_nNumSpawned++;
		m_fSpawnTimer = 0;
		m_fSpawnRate = (rand() % (m_nMinSpawnRate - m_nMaxSpawnRate) + 1 + m_nMinSpawnRate)/100.0f;
	}

	m_fSpawnTimer += fElapsedTime;

	// loops through the spawned particles 
	for( unsigned int i = 0; i < m_nNumSpawned; i++ )
	{
		// calls the particles update
		m_vAliveParticles[i]->Update( fElapsedTime );

		// If the particles life is 0 it removes it from the alive vector and puts it into the dead vector
		if( m_vAliveParticles[i]->GetCurTime() >=  m_vAliveParticles[i]->GetEndTime() )
		{		
			delete m_vAliveParticles[i];
			m_vAliveParticles.erase(m_vAliveParticles.begin() + i);

			if( m_vAliveParticles.size() == 0 )
			{
				if( m_bLooping )
					Loop();
				else
					Clear();
			}

			i--;
			m_nNumSpawned--;
			continue;
		}

		// total time particle is alive
		float time = m_vAliveParticles[i]->GetEndTime();

		// Changes the color over time
		Color oldColor = m_vAliveParticles[i]->GetColor();
		float dtA, dtR, dtG, dtB;
		// delta(color) / time
		dtA = float((m_sEndColor.a - m_sStartColor.a) / time);
		dtR = float((m_sEndColor.r - m_sStartColor.r) / time);
		dtG = float((m_sEndColor.g - m_sStartColor.g) / time);
		dtB = float((m_sEndColor.b - m_sStartColor.b) / time);
		// translate to update time
		dtA = dtA * fElapsedTime;
		dtR = dtR * fElapsedTime;
		dtG = dtG * fElapsedTime;
		dtB = dtB * fElapsedTime;
		// set the new value
		Color newColor;
		newColor.a = int(oldColor.a + dtA);
		newColor.r = int(oldColor.r + dtR);
		newColor.g = int(oldColor.g + dtG);
		newColor.b = int(oldColor.b + dtB);

		m_vAliveParticles[i]->SetColor( newColor );

		// Changes the rotation over time
		float oldRot = m_vAliveParticles[i]->GetRotation();
		// delta(rotation) / time
		float dtRot = (m_fEndRot - m_fStartRot) / time;
		// set the new value
		float newRot = dtRot + oldRot;
		m_vAliveParticles[i]->SetRotation( newRot );

		// Changes the scale over time
		float oldScale = m_vAliveParticles[i]->GetScale();
		// delta(scale) / time
		float dtScale = (m_fEndScale - m_fStartScale) / time;
		// translate to update time
		dtScale = dtScale * fElapsedTime;
		// set the new value
		float newScale = dtScale + oldScale;
		m_vAliveParticles[i]->SetScale( newScale );

		// Changes the Velocity over time
		Vec2Df oldVel = m_vAliveParticles[i]->GetVel();
		// Change the start velocity to the partciles direction
		float startX = m_sStartVel.fVecX * m_vAliveParticles[i]->GetDir().fVecX;
		float startY = m_sStartVel.fVecY * m_vAliveParticles[i]->GetDir().fVecY;
		// Change the end velocity to the particles direction
		float endX = m_sEndVel.fVecX * m_vAliveParticles[i]->GetDir().fVecX;
		float endY = m_sEndVel.fVecY * m_vAliveParticles[i]->GetDir().fVecY;

		// delta(v) / time
		float dtX = (endX - startX) / time;
		float dtY = (endY - startY) / time;

		// change in time modified by the update time
		dtX = dtX * fElapsedTime;
		dtY = dtY * fElapsedTime;

		// set the new velocity 
		Vec2Df newVel(dtX + oldVel.fVecX, dtY + oldVel.fVecY);
		m_vAliveParticles[i]->SetVel( newVel );
	}
}

void CEmitter::Loop( void )
{
	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		// Finds the random life time
		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float((rand() % (maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		// Finds a random velocity
		int maxDirX = int(m_sMaxDir.fVecX);
		int maxDirY = int(m_sMaxDir.fVecY);
		int minDirX = int(m_sMinDir.fVecX);
		int minDirY = int(m_sMinDir.fVecY);

		int DirX = rand() % (maxDirX - minDirX + 1) + minDirX;
		int DirY = rand() % (maxDirY - minDirY + 1) + minDirY;

		Vec2Df Dir;
		Dir.fVecX = float(DirX);
		Dir.fVecY = float(DirY);

		Vec2Df start = m_sStartVel;
		start.fVecX *= Dir.fVecX;	
		start.fVecY *= Dir.fVecY;

		RECT src = { m_sImgPos.nPosX, m_sImgPos.nPosY, m_sImgPos.nPosX + m_nWidth, m_sImgPos.nPosY + m_nHeight };

		CParticle* tParticle = new CParticle(m_sEmitPos, Dir, start, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

		m_vAliveParticles.push_back( tParticle );
	}
}
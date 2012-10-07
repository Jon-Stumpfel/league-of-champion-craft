#include "StdAfx.h"
#include "Emitter.h"

#include "ParticleManager.h"
#include "Particle.h"
#include "GraphicsManager.h"
#include "SGD Wrappers\CSGD_Direct3D.h"

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

void CEmitter::LoadParticles( PRTCL_TYPE eType, Vec2D sPos )
{
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

	// Populates Emittier with the range of values
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

	pImageData->Attribute( "MaxParticles", &m_nNumParticles );
	pImageData->QueryFloatAttribute( "MinLife", &m_fMinLife );
	pImageData->QueryFloatAttribute( "MaxLife", &m_fMaxLife );

	int tmp;
	pImageData->Attribute( "IsLooping", &tmp);
	if( tmp )
		m_bLooping = true;
	else
		m_bLooping = false;

	pImageData->QueryFloatAttribute( "SpawnRate", &m_fSpawnRate );
	pImageData->Attribute( "SourceBlend", &m_nSourceBlend );
	pImageData->Attribute( "DestBlend", &m_nDestBlend );

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
	pImageData->Attribute( "StartingXVel", &m_sStartVel.nPosX );
	pImageData->Attribute( "EndingXVel", &m_sEndVel.nPosX );
	pImageData->Attribute( "StartingYVel", &m_sStartVel.nPosY );
	pImageData->Attribute( "EndingYVel", &m_sEndVel.nPosY );
	pImageData->Attribute( "MinXVel", &m_sMinVel.nPosX );
	pImageData->Attribute( "MaxXVel", &m_sMaxVel.nPosX );
	pImageData->Attribute( "MinYVel", &m_sMinVel.nPosY );
	pImageData->Attribute( "MaxYVel", &m_sMaxVel.nPosY );
	pImageData->QueryFloatAttribute( "StartingScale", &m_fStartScale );
	pImageData->QueryFloatAttribute( "EndingScale", &m_fEndScale );


	// tell the graphics manager where the image for each particle is
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	TCHAR conversion[100];

	mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);

	TSTRING file = conversion;

	pGM->LoadImageW( file, _T("Particle"), D3DCOLOR_ARGB(1, 1, 1, 1) );

	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		Vec2D vel = m_sStartVel;

		vel.nPosX = rand() % ((m_sMaxVel.nPosX - m_sMinVel.nPosX) + 1) + m_sMinVel.nPosX;
		vel.nPosY = rand() % ((m_sMaxVel.nPosY - m_sMinVel.nPosY) + 1) + m_sMinVel.nPosY;

		vel.nPosX *= m_sStartVel.nPosX;
		vel.nPosY *= m_sStartVel.nPosY;

		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % ((maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		RECT src;
		src.left = m_sImgPos.nPosX;
		src.top = m_sImgPos.nPosY;
		src.bottom = m_nHeight + m_sImgPos.nPosY;
		src.right = m_nWidth + m_sImgPos.nPosX;

		CParticle* tParticle = new CParticle(m_sEmitPos, vel, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

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
	if( m_fSpawnTimer < m_fSpawnRate )
	{
		if( m_vAliveParticles.size() > m_nNumSpawned )
			m_nNumSpawned++;
		m_fSpawnTimer = 0;
	}

	m_fSpawnTimer += fElapsedTime / 10;

	// loops through the spawned particles 
	for( unsigned int i = 0; i < m_nNumSpawned; i++ )
	{
		m_vAliveParticles[i]->Update( fElapsedTime );

		// If the particles life is 0 it removes it from the alive vector and puts it into the dead vector
		if( m_vAliveParticles[i]->GetLife() <= 0 )
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

		// Decrements the particles life by time
		m_vAliveParticles[i]->SetLife( m_vAliveParticles[i]->GetLife() - fElapsedTime );

		// Changes the color over time
		Color oldColor = m_vAliveParticles[i]->GetColor();
		Color perColor;

		if( oldColor.a != 0 )
			perColor.a = int(((m_sEndColor.a - oldColor.a) / oldColor.a));
		else 
			perColor.a = int(((m_sEndColor.a - oldColor.a)));

		if( oldColor.r != 0 )
			perColor.r = int(((m_sEndColor.r - oldColor.r) / oldColor.r));
		else
			perColor.r = int(((m_sEndColor.r - oldColor.r)));

		if( oldColor.g != 0 )
			perColor.g = int(((m_sEndColor.g - oldColor.g) / oldColor.g));
		else
			perColor.g = int(((m_sEndColor.g - oldColor.g)));

		if( oldColor.b != 0 )
			perColor.b = int(((m_sEndColor.b - oldColor.b) / oldColor.b));
		else
			perColor.b = int(((m_sEndColor.b - oldColor.b)));


		Color newColor;
		newColor.a = oldColor.a + (perColor.a * oldColor.a);
		newColor.r = oldColor.r + (perColor.r * oldColor.r);
		newColor.g = oldColor.g + (perColor.g * oldColor.g);
		newColor.b = oldColor.b + (perColor.b * oldColor.b);

		m_vAliveParticles[i]->SetColor( newColor );

		// Changes the rotation over time
		float oldRot = m_vAliveParticles[i]->GetRotation();
		float perRot;
		if( oldRot != 0 )
			perRot = (m_fEndRot - oldRot) / oldRot;
		else
			perRot = (m_fEndRot - oldRot);

		float newRot = oldRot + (perRot * oldRot);
		m_vAliveParticles[i]->SetRotation( newRot );

		// Changes the scale over time
		float oldScale = m_vAliveParticles[i]->GetScale();
		float perScale;
		if( oldScale != 0 )
			perScale = (m_fEndScale - oldScale) / oldScale;
		else 
			perRot = (m_fEndScale - oldScale);

		float newScale;
		newScale = oldScale + (perScale * oldScale);
		m_vAliveParticles[i]->SetScale( newScale );

		// changes the velocity over time
		Vec2D oldVel = m_vAliveParticles[i]->GetVel();
		Vec2D perVel;
		if( oldVel.nPosX != 0 )
			perVel.nPosX = (m_sEndVel.nPosX - oldVel.nPosX) / oldVel.nPosX;
		else
			perVel.nPosX = (m_sEndVel.nPosX - oldVel.nPosX);

		if( oldVel.nPosY != 0 )
			perVel.nPosY = (m_sEndVel.nPosY - oldVel.nPosY) / oldVel.nPosY;
		else
			perVel.nPosY = (m_sEndVel.nPosY - oldVel.nPosY);

		Vec2D newVel;
		newVel.nPosX = oldVel.nPosX + (perVel.nPosX * oldVel.nPosX);
		newVel.nPosY = oldVel.nPosY + (perVel.nPosY * oldVel.nPosY);
		m_vAliveParticles[i]->SetVel( newVel );
	}
}

void CEmitter::Loop( void )
{
	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		Vec2D vel = m_sStartVel;

		vel.nPosX *= rand() % ((m_sMaxVel.nPosX - m_sMinVel.nPosX) + 1) + m_sMinVel.nPosX;
		vel.nPosY *= rand() % ((m_sMaxVel.nPosY - m_sMinVel.nPosY) + 1) + m_sMinVel.nPosY;

		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % ((maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		RECT src;
		src.left = m_sImgPos.nPosX;
		src.top = m_sImgPos.nPosY;
		src.bottom = m_nHeight + m_sImgPos.nPosY;
		src.right = m_nWidth + m_sImgPos.nPosX;

		CParticle* tParticle = new CParticle(m_sEmitPos, vel, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

		m_vAliveParticles.push_back( tParticle );
	}
}
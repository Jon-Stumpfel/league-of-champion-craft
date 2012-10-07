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
	pImageData->QueryFloatAttribute( "StartingXVel", &m_sStartVel.fVecX );
	pImageData->QueryFloatAttribute( "EndingXVel", &m_sEndVel.fVecX );
	pImageData->QueryFloatAttribute( "StartingYVel", &m_sStartVel.fVecY );
	pImageData->QueryFloatAttribute( "EndingYVel", &m_sEndVel.fVecY );
	pImageData->QueryFloatAttribute( "MinXAccel", &m_sMinAccel.fVecX );
	pImageData->QueryFloatAttribute( "MaxXAccel", &m_sMaxAccel.fVecX );
	pImageData->QueryFloatAttribute( "MinYAccel", &m_sMinAccel.fVecY );
	pImageData->QueryFloatAttribute( "MaxYAccel", &m_sMaxAccel.fVecY );
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
		Vec2Df vel = m_sStartVel;
		Vec2Df accel;

		int maxX = int(m_sMaxAccel.fVecX * 100);
		int maxY = int(m_sMaxAccel.fVecY * 100);
		int minX = int(m_sMinAccel.fVecX * 100);
		int minY = int(m_sMinAccel.fVecY * 100);

		float tmpX = float(rand() % ((maxX - minX) + 1) + minX);
		float tmpY = float(rand() % ((maxY - minY) + 1) + minY);

		accel.fVecX = tmpX / 100.0f;
		accel.fVecY = tmpY / 100.0f;

		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % ((maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		RECT src;
		src.left = m_sImgPos.nPosX;
		src.top = m_sImgPos.nPosY;
		src.bottom = m_nHeight + m_sImgPos.nPosY;
		src.right = m_nWidth + m_sImgPos.nPosX;

		CParticle* tParticle = new CParticle(m_sEmitPos, vel, accel, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

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
	}

	m_fSpawnTimer += fElapsedTime;

	// loops through the spawned particles 
	for( unsigned int i = 0; i < m_nNumSpawned; i++ )
	{
		// If the particles life is 0 it removes it from the alive vector and puts it into the dead vector
		if( m_vAliveParticles[i]->GetLife() >=  m_vAliveParticles[i]->GetMaxLife() )
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

		// Changes the color over time
		Color oldColor = m_vAliveParticles[i]->GetColor();
		float perA, perR, perG, perB;

		if( oldColor.a != 0 )
			perA = float((m_sEndColor.a - oldColor.a) / oldColor.a);
		else 
			perA = float((m_sEndColor.a - oldColor.a));

		perA *= fElapsedTime;

		if( oldColor.r != 0 )
			perR = float((m_sEndColor.r - oldColor.r) / oldColor.r);
		else
			perR = float((m_sEndColor.r - oldColor.r));

		perR *= fElapsedTime;

		if( oldColor.g != 0 )
			perG = float((m_sEndColor.g - oldColor.g) / oldColor.g);
		else
			perG = float((m_sEndColor.g - oldColor.g));

		perG *= fElapsedTime * m_vAliveParticles[i]->GetLife();;

		if( oldColor.b != 0 )
			perB = float((m_sEndColor.b - oldColor.b) / oldColor.b);
		else
			perB = float((m_sEndColor.b - oldColor.b));

		perB *= m_vAliveParticles[i]->GetLife();

		Color newColor;
		newColor.a = int(oldColor.a + (perA * oldColor.a));
		newColor.r = int(oldColor.r + (perR * oldColor.r));
		newColor.g = int(oldColor.g + (perG * oldColor.g));
		newColor.b = int(oldColor.b + (perB * oldColor.b));

		m_vAliveParticles[i]->SetColor( newColor );

		// Changes the rotation over time
		float oldRot = m_vAliveParticles[i]->GetRotation();
		float perRot;
		if( oldRot != 0 )
			perRot = (m_fEndRot - oldRot) / oldRot;
		else
			perRot = (m_fEndRot - oldRot);

		perRot *= m_vAliveParticles[i]->GetLife();

		float newRot = oldRot + (perRot * oldRot);
		m_vAliveParticles[i]->SetRotation( newRot );

		// Changes the scale over time
		float oldScale = m_vAliveParticles[i]->GetScale();
		float perScale;
		if( oldScale != 0 )
			perScale = (m_fEndScale - oldScale) / oldScale;
		else 
			perScale = (m_fEndScale - oldScale);

		perScale *= m_vAliveParticles[i]->GetLife();

		float newScale;
		newScale = oldScale + (perScale * oldScale);
		m_vAliveParticles[i]->SetScale( newScale );

		//// changes the velocity over time
		//Vec2Df oldVel = m_vAliveParticles[i]->GetVel();
		//Vec2Df newVel;

		//newVel.fVecX = oldVel.fVecX + (m_sEndVel.fVecX - m_sStartVel.fVecX) / ( m_vAliveParticles[i]->GetMaxLife() - 0 );
		//newVel.fVecY = oldVel.fVecY + (m_sEndVel.fVecY - m_sStartVel.fVecY) / ( m_vAliveParticles[i]->GetMaxLife() - 0 );

		//m_vAliveParticles[i]->SetVel( newVel );

		// calls the particles update
		m_vAliveParticles[i]->Update( fElapsedTime );
	}
}

void CEmitter::Loop( void )
{
	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		Vec2Df vel = m_sStartVel;
		Vec2Df accel;

		int maxX = int(m_sMaxAccel.fVecX * 100);
		int maxY = int(m_sMaxAccel.fVecY * 100);
		int minX = int(m_sMinAccel.fVecX * 100);
		int minY = int(m_sMinAccel.fVecY * 100);

		float tmpX = float(rand() % ((maxX - minX) + 1) + minX);
		float tmpY = float(rand() % ((maxY - minY) + 1) + minY);

		accel.fVecX = tmpX / 100.0f;
		accel.fVecY = tmpY / 100.0f;

		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % ((maxLife - minLife) + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		RECT src;
		src.left = m_sImgPos.nPosX;
		src.top = m_sImgPos.nPosY;
		src.bottom = m_nHeight + m_sImgPos.nPosY;
		src.right = m_nWidth + m_sImgPos.nPosX;

		CParticle* tParticle = new CParticle(m_sEmitPos, vel, accel, m_fStartScale, life, m_sStartColor, m_fStartRot, src );

		m_vAliveParticles.push_back( tParticle );
	}
}
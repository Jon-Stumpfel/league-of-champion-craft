#include "StdAfx.h"
#include "Emitter.h"

#include "ParticleManager.h"
#include "Particle.h"
#include "GraphicsManager.h"  
#include "SGD Wrappers\CSGD_Direct3D.h"
#include <ctime>

CEmitter::CEmitter(void)
{
	srand( unsigned int(time(0)) );
	rand();
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

			m_sSource.left = 0;
			m_sSource.top = 0;
			m_sSource.right = 128;
			m_sSource.bottom = 128;
		}
		break;

	case TESTSECOND:
		{
			//if( doc.LoadFile( "Assets/Particles/othertest.xml" ) == false )
				return;

			m_sSource.left = 0;
			m_sSource.top = 0;
			m_sSource.right = 128;
			m_sSource.bottom = 128;
		}
		break;
	case PT_FIRE:
		{
			if( doc.LoadFile( "Assets/Particles/fire.xml" ) == false )
				return;
			m_sSource.left = 0;
			m_sSource.top = 0;
			m_sSource.right = 128;
			m_sSource.bottom = 128;
		}
		break;
	case PT_CARTOGRAPHY:
		{
			if( doc.LoadFile( "Assets/Particles/cartography.xml" ) == false )
				return;
			m_sSource.left = 0;
			m_sSource.top = 0;
			m_sSource.right = 128;
			m_sSource.bottom = 128;

		}
		break;
	};

	m_sEmitPos = sPos;
	m_fSpawnTimer = 0;
	m_nNumSpawned = 0;

	// Populates Emitter with the range of values
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
		return;

	m_vAliveParticles.clear();

	pRoot->Attribute( "Height", &m_nHeight );
	pRoot->Attribute( "Width", &m_nWidth );
	pRoot->Attribute( "NumParticles", &m_nNumParticles );
	pRoot->QueryFloatAttribute( "LifeMin", &m_fMinLife );
	pRoot->QueryFloatAttribute( "LifeMax", &m_fMaxLife );

	int tmp;
	pRoot->Attribute("Looping", &tmp);
	if( tmp > 0 )
		m_bLooping = true;
	else
		m_bLooping = false;

	float min, max;
	pRoot->QueryFloatAttribute( "SpawnMin", &min );
	pRoot->QueryFloatAttribute( "SpawnMax", &max );
	m_nMaxSpawnRate = int(max * 100);
	m_nMinSpawnRate = int(min * 100);

	pRoot->Attribute( "ColorStartA", &m_sStartColor.a );
	pRoot->Attribute( "ColorEndA", &m_sEndColor.a );
	pRoot->Attribute( "ColorStartR", &m_sStartColor.r );
	pRoot->Attribute( "ColorEndR", &m_sEndColor.r );
	pRoot->Attribute( "ColorStartG", &m_sStartColor.g );
	pRoot->Attribute( "ColorEndG", &m_sEndColor.g );
	pRoot->Attribute( "ColorStartB", &m_sStartColor.b );
	pRoot->Attribute( "ColorEndB", &m_sEndColor.b );

	float startRot, endRot;
	pRoot->QueryFloatAttribute( "RotStart", &startRot );
	pRoot->QueryFloatAttribute( "RotEnd", &endRot );
	pRoot->QueryFloatAttribute( "ScaleStart", &m_fStartScale );
	pRoot->QueryFloatAttribute( "ScaleEnd", &m_fEndScale );

	m_fStartRot = float(startRot * 3.1415926 / 180);
	m_fEndRot = float(endRot * 3.1415926 / 180);

	Vec2D sMax, sMin, eMax, eMin;

	pRoot->Attribute( "VelStartMaxX", &sMax.nPosX );
	pRoot->Attribute( "VelStartMaxY", &sMax.nPosY );
	pRoot->Attribute( "VelStartMinX", &sMin.nPosX );
	pRoot->Attribute( "VelStartMinY", &sMin.nPosY );

	m_sStartVelMax.fVecX = (float)sMax.nPosX;
	m_sStartVelMax.fVecY = (float)sMax.nPosY;

	m_sStartVelMin.fVecX = (float)sMin.nPosX;
	m_sStartVelMin.fVecY = (float)sMin.nPosY;

	pRoot->Attribute( "VelEndMaxX", &eMax.nPosX );
	pRoot->Attribute( "VelEndMaxY", &eMax.nPosY );
	pRoot->Attribute( "VelEndMinX", &eMin.nPosX );
	pRoot->Attribute( "VelEndMinY", &eMin.nPosY );

	m_sEndVelMax.fVecX = (float)eMax.nPosX;
	m_sEndVelMax.fVecY = (float)eMax.nPosY;
	m_sEndVelMin.fVecX = (float)eMin.nPosX;	
	m_sEndVelMin.fVecY = (float)eMin.nPosY;

	m_szPath = pRoot->Attribute( "Image" );

	int i = 0;
	pRoot->Attribute("Shape", &i);
	if( i == 0 )
		m_eType = DOT;
	else if( i == 1 )
		m_eType = CIRCLE;
	else if( i == 2 )
		m_eType = SQUARE;
	else
		m_eType = LINE;

	// tell the graphics manager where the image for each particle is
	CGraphicsManager* pGM = CGraphicsManager::GetInstance();
	m_fSpawnRate = (rand() % ((m_nMinSpawnRate - m_nMaxSpawnRate) + 1) + m_nMinSpawnRate)/100.0f;

	switch( eType )
	{
	case TEST:
		{
			TCHAR conversion[100];	
			mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);
			TSTRING file = conversion;
			pGM->LoadImageW(_T("Assets/Particles/") + file, _T("Test"), D3DCOLOR_ARGB(255, 255, 255, 255) );
			m_nImgID = pGM->GetID(_T("Test"));
		}
		break;

	case TESTSECOND:
		{
			TCHAR conversion[100];	
			mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);
			TSTRING file = conversion;
			pGM->LoadImageW( _T("Assets/Particles/") + file, _T("Test2"), D3DCOLOR_ARGB(255, 255, 255, 255) );
			m_nImgID = pGM->GetID(_T("Test2"));
		}
		break;
	case PT_FIRE:
		{
			TCHAR conversion[100];	
			mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);
			TSTRING file = conversion;
			pGM->LoadImageW( _T("Assets/Particles/") + file, _T("fire"), D3DCOLOR_ARGB(255, 255, 255, 255) );
			m_nImgID = pGM->GetID(_T("fire"));
		}
		break;
	case PT_CARTOGRAPHY:
		{
			TCHAR conversion[100];	
			mbstowcs_s(nullptr, conversion, m_szPath, _TRUNCATE);
			TSTRING file = conversion;
			pGM->LoadImageW( _T("Assets/Particles/") + file, _T("cartography"), D3DCOLOR_ARGB(255, 255, 255, 255) );
			m_nImgID = pGM->GetID(_T("cartography"));
		}

		break;
	}

	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		Vec2D Pos;
		if( m_eType == DOT )
			Pos = m_sEmitPos;
		else if( m_eType == CIRCLE )
		{
			Pos.nPosX = m_sEmitPos.nPosX + (rand() % (int)Radius + 1);
			Pos.nPosY = m_sEmitPos.nPosY + (rand() % (int)Radius + 1);
		}
		else if( m_eType == SQUARE )	
		{
			Pos.nPosX = (m_sEmitPos.nPosX-m_nWidth/2) + (rand() % (int)m_nWidth+1);
			Pos.nPosY = (m_sEmitPos.nPosY-m_nHeight/2) + (rand() % (int)m_nHeight+1);
		}
		else if( m_eType == LINE )
		{
			if( m_sPoint.nPosX > m_sPoint2.nPosX)
				Pos.nPosX = (rand() % (m_sPoint.nPosX - m_sPoint2.nPosX + 1));
			else
				Pos.nPosX = (rand() % (m_sPoint2.nPosX - m_sPoint.nPosX + 1));

			if( m_sPoint.nPosY > m_sPoint2.nPosY)
				Pos.nPosY = (rand() % (m_sPoint.nPosY - m_sPoint2.nPosY + 1));
			else
				Pos.nPosY = (rand() % (m_sPoint2.nPosY - m_sPoint.nPosY + 1));
		}

		// Finds the random life time
		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % (maxLife - minLife + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		Vec2Df start;
		start.fVecX = float((rand() % int((m_sStartVelMax.fVecX - m_sStartVelMin.fVecX)+1) + m_sStartVelMin.fVecX));
		start.fVecY = float((rand() % int((m_sStartVelMax.fVecY - m_sStartVelMin.fVecY)+1) + m_sStartVelMin.fVecY));

		Vec2Df end;
		end.fVecX = float((rand() % int((m_sEndVelMax.fVecX - m_sEndVelMin.fVecX)+1) + m_sEndVelMin.fVecX));
		end.fVecY = float((rand() % int((m_sEndVelMax.fVecY - m_sEndVelMin.fVecY)+1) + m_sEndVelMin.fVecY));

		CParticle* tParticle = new CParticle(Pos, end, start, m_fStartScale, life, m_sStartColor, m_fStartRot, m_sSource, m_nImgID);

		m_vAliveParticles.push_back( tParticle );
	}
	m_nNumSpawned = 1;
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
		while (m_fSpawnTimer > m_fSpawnRate)
		{
			if( m_vAliveParticles.size() > m_nNumSpawned )
				m_nNumSpawned++;
			else
				break;
			m_fSpawnTimer -= m_fSpawnRate;
		}

		m_fSpawnTimer = 0;
		m_fSpawnRate = (rand() % (m_nMinSpawnRate - m_nMaxSpawnRate + 1) + m_nMinSpawnRate)/100.0f;
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
		dtRot = dtRot * fElapsedTime;
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
	}
}

void CEmitter::Loop( void )
{
	// Populates the list of AliveParticles
	for( int i = 0; i < m_nNumParticles; i++ )
	{
		Vec2D Pos;
		if( m_eType == DOT )
			Pos = m_sEmitPos;
		else if( m_eType == CIRCLE )
		{
			Pos.nPosX = m_sEmitPos.nPosX + (rand() % (int)Radius + 1);
			Pos.nPosY = m_sEmitPos.nPosY + (rand() % (int)Radius + 1);
		}
		else if( m_eType == SQUARE )	
		{
			Pos.nPosX = (m_sEmitPos.nPosX-m_nWidth/2) + (rand() % (int)m_nWidth+1);
			Pos.nPosY = (m_sEmitPos.nPosY-m_nHeight/2) + (rand() % (int)m_nHeight+1);
		}
		else if( m_eType == LINE )
		{
			if( m_sPoint.nPosX > m_sPoint2.nPosX)
				Pos.nPosX = (rand() % (m_sPoint.nPosX - m_sPoint2.nPosX + 1));
			else
				Pos.nPosX = (rand() % (m_sPoint2.nPosX - m_sPoint.nPosX + 1));

			if( m_sPoint.nPosY > m_sPoint2.nPosY)
				Pos.nPosY = (rand() % (m_sPoint.nPosY - m_sPoint2.nPosY + 1));
			else
				Pos.nPosY = (rand() % (m_sPoint2.nPosY - m_sPoint.nPosY + 1));
		}

		// Finds the random life time
		int maxLife = int(m_fMaxLife * 100);
		int minLife = int(m_fMinLife * 100);

		float tmp = float(rand() % (maxLife - minLife + 1) + minLife);
		
		float life = float(tmp / 100.0f);

		Vec2Df start;
		start.fVecX = float((rand() % int((m_sStartVelMax.fVecX - m_sStartVelMin.fVecX)+1) + m_sStartVelMin.fVecX));
		start.fVecY = float((rand() % int((m_sStartVelMax.fVecY - m_sStartVelMin.fVecY)+1) + m_sStartVelMin.fVecY));

		Vec2Df end;
		end.fVecX = float((rand() % int((m_sEndVelMax.fVecX - m_sEndVelMin.fVecX)+1) + m_sEndVelMin.fVecX));
		end.fVecY = float((rand() % int((m_sEndVelMax.fVecY - m_sEndVelMin.fVecY)+1) + m_sEndVelMin.fVecY));

		CParticle* tParticle = new CParticle(Pos, end, start, m_fStartScale, life, m_sStartColor, m_fStartRot, m_sSource, m_nImgID);

		m_vAliveParticles.push_back( tParticle );
	}
	m_nNumSpawned = 1;
}
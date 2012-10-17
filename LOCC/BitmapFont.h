#pragma once
#include "StdAfx.h"
class CBitmapFont
{
private:
	// Cell Algorithm
	int		m_nCharWidth;		// 32
	int		m_nCharHeight;		// 32
	int		jcs_nImageID;
	bool	jcs_bOnlyUppercase;	// true
	CSGD_TextureManager* pTM;
	RECT rSource;
public:
	CBitmapFont()
	{
		rSource.left = rSource.top = rSource.right = rSource.bottom = 0;
		m_nCharWidth = 32;	
		m_nCharHeight = 32;
		pTM = CSGD_TextureManager::GetInstance();
		jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\Deutsch_gothic(whited).png"));
	}
	~CBitmapFont()
	{

	}
	RECT CellAlgorithm( int id )
	{
		switch (id)
		{
		case 65:
			{
				rSource.left = 17;
				rSource.top = 82;
				rSource.right = 56;
				rSource.bottom = 129;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 66:
			{
				rSource.left = 89;
				rSource.top = 80;
				rSource.right = 127;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 67:
			{
				rSource.left = 158;
				rSource.top = 83;
				rSource.right = 193;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 68:
			{
				rSource.left = 225;
				rSource.top = 80;
				rSource.right = 265;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 69:
			{
				rSource.left = 296;
				rSource.top = 83;
				rSource.right = 329;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 70:
			{
				rSource.left = 362;
				rSource.top = 83;
				rSource.right = 396;
				rSource.bottom = 128;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 71:
			{
				rSource.left = 428;
				rSource.top = 83;
				rSource.right = 463;
				rSource.bottom = 128;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 72:
			{
				rSource.left = 498;
				rSource.top = 83;
				rSource.right = 532;
				rSource.bottom = 131;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 73:
			{
				rSource.left = 565;
				rSource.top = 83;
				rSource.right = 583;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 74:
			{
				rSource.left = 617;
				rSource.top = 83;
				rSource.right = 643;
				rSource.bottom = 134;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 75:
			{
				rSource.left = 675;
				rSource.top = 83;
				rSource.right = 708;
				rSource.bottom = 130;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 76:
			{
				rSource.left = 740;
				rSource.top = 83;
				rSource.right = 774;
				rSource.bottom = 128;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 77:
			{
				rSource.left = 806;
				rSource.top = 83;
				rSource.right = 849;
				rSource.bottom = 128;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 78:
			{
				rSource.left = 882;
				rSource.top = 83;
				rSource.right = 916;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 79:
			{
				rSource.left = 950;
				rSource.top = 83;
				rSource.right = 986;
				rSource.bottom = 127;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 80:
			{
				rSource.left = 17;
				rSource.top = 241;
				rSource.right = 54;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 81:
			{
				rSource.left = 88;
				rSource.top = 241;
				rSource.right = 126;
				rSource.bottom = 295;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 82:
			{
				rSource.left = 157;
				rSource.top = 240;
				rSource.right = 197;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 83:
			{
				rSource.left = 230;
				rSource.top = 241;
				rSource.right = 266;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 84:
			{
				rSource.left = 298;
				rSource.top = 241;
				rSource.right = 333;
				rSource.bottom = 295;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 85:
			{
				rSource.left = 365;
				rSource.top = 241;
				rSource.right = 400;
				rSource.bottom = 287;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 86:
			{
				rSource.left = 432;
				rSource.top = 240;
				rSource.right = 467;
				rSource.bottom = 285;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 87:
			{
				rSource.left = 500;
				rSource.top = 240;
				rSource.right = 547;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 88:
			{
				rSource.left = 579;
				rSource.top = 241;
				rSource.right = 619;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 89:
			{
				rSource.left = 651;
				rSource.top = 241;
				rSource.right = 692;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 90:
			{
				rSource.left = 723;
				rSource.top = 241;
				rSource.right = 755;
				rSource.bottom = 286;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 97:
			{
				rSource.left = 17;
				rSource.top = 424;
				rSource.right = 36;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 98:
			{
				rSource.left = 69;
				rSource.top = 424;
				rSource.right = 91;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 99:
			{
				rSource.left = 123;
				rSource.top = 424;
				rSource.right = 140;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 100:
			{
				rSource.left = 
				rSource.top = 424;
				rSource.right = 
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		}
		return rSource;
	}
	void Print(		const char*	szText,		int nX, int nY,
					float fScale,			DWORD dwColor )
	{
		// Iterate through the string 1 character at a time
		int nLength = strlen( szText );

		for( int i = 0; i < nLength; i++ )
		{
			// Get char out of the string
			char ch = szText[ i ];

			// Check for whitespace
			if( ch == ' ' )
			{
				//float Scale = fScale*100;
				nX += 10;
				continue;
			}
			// Calculate the tile id for this character
			int id = ch;
			// Get the source rect using the Cell Algorithm
			RECT rTile = CellAlgorithm( id );
			pTM->Draw( jcs_nImageID, nX, nY, fScale, fScale, &rTile,
						0.0f, 0.0f, 0.0f, dwColor );
			float Scale = fScale*100;
			nX += m_nCharWidth * (int)Scale/100;
		}
	}
};
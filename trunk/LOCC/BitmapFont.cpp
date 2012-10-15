#include "StdAfx.h"
#include "BitmapFont.h"

CBitmapFont::CBitmapFont(void)
{
	
}


CBitmapFont::~CBitmapFont(void)
{
}

void CBitmapFont::Print(const char* szText, int nX, int nY, float fScale, 
						DWORD dwColor )
{
	// Keep track of the starting x position (for newlines)
	int nColStart = nX;

	// Iterate through the string 1 character at a time
	int nLength = strlen( szText );

	for( int i = 0; i < nLength; i++ )
	{
		// Get char out of the string
		char ch = szText[ i ];


		// Check for whitespace
		if( ch == ' ' )
		{
			nX += m_nCharWidth * (int)fScale;
			continue;
		}
		else if( ch == '\n' )
		{
			nX = nColStart;
			nY += m_nCharHeight * (int)fScale;
			continue;
		}


		// Convert to uppercase?
		if( m_bOnlyUppercase == true )
			ch = toupper( ch );


		// Calculate the tile id for this character
		int id = ch - m_szFirstChar;


		// Get the source rect using the Cell Algorithm
		RECT rTile = CellAlgorithm( id );

		// Draw!
		CSGD_TextureManager::GetInstance()->Draw( m_nImageID, nX, nY, fScale, 
			fScale, &rTile, 0.0f, 0.0f, 0.0f, dwColor );


		// Move to the next location on screen
		nX += m_nCharWidth * (int)fScale;
	}
}

void CBitmapFont::Initialize( void )
{

}

RECT CBitmapFont::CellAlgorithm( int id )
{
	RECT rSource;
	int nCellWidth = 32;
	int nCellHeight = 32;
	rSource.left	= (id % m_nNumCols) * nCellWidth;
	rSource.top		= (id / m_nNumCols) * nCellHeight;

	rSource.right	= rSource.left	+ nCellWidth;
	rSource.bottom	= rSource.top	+ nCellHeight;

	return rSource;
}
#pragma once
#include "StdAfx.h"
class CBitmapFont
{
private:
	// Cell Algorithm
	int		jcs_nCharWidth;		// 32
	int		jcs_nCharHeight;		// 32
	int		jcs_nNumRows;			// 6
	int		jcs_nNumCols;			// 10

	int		jcs_nImageID;
	char	jcs_cFirstChar;		// ' '
	bool	jcs_bOnlyUppercase;	// true
	int		nCellWidth;
	int		nCellHeight;
	CSGD_TextureManager* pTM;
	RECT rSource;
public:
	CBitmapFont()
	{
		rSource.left = rSource.top = rSource.right = rSource.bottom = 0;
		nCellWidth = 32;
		nCellHeight = 32;
		jcs_nCharWidth = 32;	
		jcs_nCharHeight = 32;
		jcs_nNumRows = 6;	
		jcs_nNumCols = 10;	
		jcs_cFirstChar = ' ';
		pTM = CSGD_TextureManager::GetInstance();
		jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\Deutsch_gothic(whited).png"));
	}
	~CBitmapFont()
	{

	}
	RECT CellAlgorithm( int id )
	{
		//assert( id >= 0 && id < nNumCols * nNumRows && "CellAlgorithm - id out of range!" );

		/*
		rSource.left	= (id % jcs_nNumCols) * nCellWidth;
		rSource.top		= (id / jcs_nNumCols) * nCellHeight;

		rSource.right	= rSource.left	+ nCellWidth;
		rSource.bottom	= rSource.top	+ nCellHeight;*/
		switch (id)
		{
		case 65:
			{
			rSource.left = 16;
			rSource.top = 83;
			rSource.right = 58;
			rSource.bottom = 128;
			}
		case 66:
			{

			}
		}
		return rSource;
	}
	void Print(		const char*	szText,		int nX, int nY,
					float fScale,			DWORD dwColor )
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
				nX += jcs_nCharWidth * fScale;
				continue;
			}
			else if( ch == '\n' )
			{
				nX = nColStart;
				nY += jcs_nCharHeight * fScale;
				continue;
			}


			// Convert to uppercase?
			if( jcs_bOnlyUppercase == true )
				ch = toupper( ch );


			// Calculate the tile id for this character
			int id = ch;


			// Get the source rect using the Cell Algorithm
			RECT rTile = CellAlgorithm( id );

			// Draw!
			pTM->Draw( jcs_nImageID, nX, nY, fScale, fScale, &rTile,
						0.0f, 0.0f, 0.0f, dwColor );
			
			// Move to the next location on screen
			nX += jcs_nCharWidth * fScale + 10;
		}

	}
};
#pragma once

class CBitmapFont
{

public:

	CBitmapFont(void);
	~CBitmapFont(void);

	void Print( char szText, int nX, int nY, float fScale, DWORD dwColor );
	void Initialize( void );

private:

	int m_nWidthArr;
	int m_nHeightArr;
	int m_nNumRows;
	int m_nNumCols;
	int m_nImageID;

	char m_szFirstChar;

	RECT CellAlgorithm( int nID );

};


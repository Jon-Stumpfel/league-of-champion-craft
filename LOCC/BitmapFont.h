#pragma once
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
		jcs_nImageID = pTM->LoadTexture(_T("Assets\\Menus\\Bitmap Font.png"));
	}
	~CBitmapFont()
	{

	}
	RECT CellAlgorithm( int id )
	{
		switch (id)
		{
		case 44:
			{
				rSource.left = 518;
				rSource.top = 903;
				rSource.right = 529;
				rSource.bottom = 951;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 45:
			{
				rSource.left = 436;
				rSource.top = 788;
				rSource.right = 453;
				rSource.bottom = 814;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 47:
			{
				rSource.left = 545;
				rSource.top = 780;
				rSource.right = 573;
				rSource.bottom = 818;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 48:
			{
				rSource.left = 15;
				rSource.top = 627;
				rSource.right = 42;
				rSource.bottom = 665;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 49:
			{
				rSource.left = 76;
				rSource.top = 627;
				rSource.right = 87;
				rSource.bottom = 665;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 50:
			{
				rSource.left = 120;
				rSource.top = 627;
				rSource.right = 147;
				rSource.bottom = 665;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 51:
			{
				rSource.left = 180;
				rSource.top = 627;
				rSource.right = 208;
				rSource.bottom = 665;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 52:
			{
				rSource.left = 212;
				rSource.top = 618;
				rSource.right = 240;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 53:
			{
				rSource.left = 266;
				rSource.top = 618;
				rSource.right = 285;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 54:
			{
				rSource.left = 311;
				rSource.top = 618;
				rSource.right = 337;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 55:
			{
				rSource.left = 362;
				rSource.top = 618;
				rSource.right = 383;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 56:
			{
				rSource.left = 408;
				rSource.top = 618;
				rSource.right = 434;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 57:
			{
				rSource.left = 459;
				rSource.top = 618;
				rSource.right = 484;
				rSource.bottom = 656;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 58:
			{
				rSource.left = 426;
				rSource.top = 909;
				rSource.right = 434;
				rSource.bottom = 933;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 65:
			{
				rSource.left = 15;
				rSource.top = 69;
				rSource.right = 56;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 66:
			{
				rSource.left = 82;
				rSource.top = 69;
				rSource.right = 114;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 67:
			{
				rSource.left = 140;
				rSource.top = 68;
				rSource.right = 173;
				rSource.bottom = 111;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 68:
			{
				rSource.left = 199;
				rSource.top = 69;
				rSource.right = 233;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 69:
			{
				rSource.left = 261;
				rSource.top = 69;
				rSource.right = 294;
				rSource.bottom = 111;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 70:
			{
				rSource.left = 320;
				rSource.top = 69;
				rSource.right = 350;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 71:
			{
				rSource.left = 376;
				rSource.top = 68;
				rSource.right = 407;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 72:
			{
				rSource.left = 433;
				rSource.top = 66;
				rSource.right = 466;
				rSource.bottom = 111;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 73:
			{
				rSource.left = 492;
				rSource.top = 69;
				rSource.right = 514;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 74:
			{
				rSource.left = 540;
				rSource.top = 69;
				rSource.right = 569;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 75:
			{
				rSource.left = 595;
				rSource.top = 68;
				rSource.right = 631;
				rSource.bottom = 112;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 76:
			{
				rSource.left = 657;
				rSource.top = 68;
				rSource.right = 686;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 77:
			{
				rSource.left = 714;
				rSource.top = 69;
				rSource.right = 760;
				rSource.bottom = 106;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 78:
			{
				rSource.left = 14;
				rSource.top = 196;
				rSource.right = 47;
				rSource.bottom = 239;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 79:
			{
				rSource.left = 75;
				rSource.top = 196;
				rSource.right = 108;
				rSource.bottom = 233;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 80:
			{
				rSource.left = 134;
				rSource.top = 196;
				rSource.right = 166;
				rSource.bottom = 233;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 81:
			{
				rSource.left = 193;
				rSource.top = 196;
				rSource.right = 231;
				rSource.bottom = 237;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 82:
			{
				rSource.left = 257;
				rSource.top = 196;
				rSource.right = 293;
				rSource.bottom = 240;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 83:
			{
				rSource.left = 319;
				rSource.top = 196;
				rSource.right = 348;
				rSource.bottom = 241;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 84:
			{
				rSource.left = 373;
				rSource.top = 196;
				rSource.right = 403;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 85:
			{
				rSource.left = 429;
				rSource.top = 196;
				rSource.right = 460;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 86:
			{
				rSource.left = 487;
				rSource.top = 196;
				rSource.right = 524;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 87:
			{
				rSource.left = 550;
				rSource.top = 196;
				rSource.right = 594;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 88:
			{
				rSource.left = 620;
				rSource.top = 196;
				rSource.right = 657;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 89:
			{
				rSource.left = 683;
				rSource.top = 196;
				rSource.right = 713;
				rSource.bottom = 236;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 90:
			{
				rSource.left = 739;
				rSource.top = 196;
				rSource.right = 767;
				rSource.bottom = 234;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 92:
			{
				rSource.left = 626;
				rSource.top = 897;
				rSource.right = 645;
				rSource.bottom = 938;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 97:
			{
				rSource.left = 14;
				rSource.top = 343;
				rSource.right = 35;
				rSource.bottom = 381;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 98:
			{
				rSource.left = 69;
				rSource.top = 422;
				rSource.right = 91;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 99:
			{
				rSource.left = 123;
				rSource.top = 422;
				rSource.right = 140;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 100:
			{
				rSource.left = 173;
				rSource.top = 422;
				rSource.right = 194;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 101:
			{
				rSource.left = 228;
				rSource.top = 422;
				rSource.right = 245;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 102:
			{
				rSource.left = 277;
				rSource.top = 422;
				rSource.right = 292;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 103:
			{
				rSource.left = 324;
				rSource.top = 422;
				rSource.right = 348;
				rSource.bottom = 481;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 104:
			{
				rSource.left = 380;
				rSource.top = 422;
				rSource.right = 401;
				rSource.bottom = 474;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 105:
			{
				rSource.left = 433;
				rSource.top = 422;
				rSource.right = 445;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 106:
			{
				rSource.left = 477;
				rSource.top = 422;
				rSource.right = 488;
				rSource.bottom = 478;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 107:
			{
				rSource.left = 520;
				rSource.top = 422;
				rSource.right = 540;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 108:
			{
				rSource.left = 573;
				rSource.top = 422;
				rSource.right = 582;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 109:
			{
				rSource.left = 614;
				rSource.top = 422;
				rSource.right = 645;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 110:
			{
				rSource.left = 677;
				rSource.top = 422;
				rSource.right = 698;
				rSource.bottom = 470;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 111:
			{
				rSource.left = 732;
				rSource.top = 422;
				rSource.right = 752;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 112:
			{
				rSource.left = 786;
				rSource.top = 422;
				rSource.right = 811;
				rSource.bottom = 478;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 113:
			{
				rSource.left = 842;
				rSource.top = 422;
				rSource.right = 863;
				rSource.bottom = 477;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 114:
			{
				rSource.left = 895;
				rSource.top = 422;
				rSource.right = 913;
				rSource.bottom = 469;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 115:
			{
				rSource.left = 946;
				rSource.top = 422;
				rSource.right = 963;
				rSource.bottom = 470;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 116:
			{
				rSource.left = 17;
				rSource.top = 580;
				rSource.right = 30;
				rSource.bottom = 628;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 117:
			{
				rSource.left = 64;
				rSource.top = 580;
				rSource.right = 85;
				rSource.bottom = 628;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 118:
			{
				rSource.left = 119;
				rSource.top = 580;
				rSource.right = 137;
				rSource.bottom = 628;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 119:
			{
				rSource.left = 170;
				rSource.top = 580;
				rSource.right = 198;
				rSource.bottom = 628;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 120:
			{
				rSource.left = 232;
				rSource.top = 580;
				rSource.right = 250;
				rSource.bottom = 628;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 121:
			{
				rSource.left = 284;
				rSource.top = 580;
				rSource.right = 305;
				rSource.bottom = 640;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 122:
			{
				rSource.left = 337;
				rSource.top = 580;
				rSource.right = 358;
				rSource.bottom = 628;
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
			nX += (int)(m_nCharWidth * fScale) + 2;
		}
	}
};
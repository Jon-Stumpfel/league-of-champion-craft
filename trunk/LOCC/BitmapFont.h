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
		case 33:
			{
				rSource.left = 68;
				rSource.top = 1036;
				rSource.right = 75;
				rSource.bottom = 1075;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 39:
			{
				rSource.left = 181;
				rSource.top = 909;
				rSource.right = 188;
				rSource.bottom = 920;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
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
				rSource.left = 18;
				rSource.top = 628;
				rSource.right = 52;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 49:
			{
				rSource.left = 94;
				rSource.top = 628;
				rSource.right = 108;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 50:
			{
				rSource.left = 147;
				rSource.top = 628;
				rSource.right = 182;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 51:
			{
				rSource.left = 222;
				rSource.top = 628;
				rSource.right = 256;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 52:
			{
				rSource.left = 296;
				rSource.top = 628;
				rSource.right = 331;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 53:
			{
				rSource.left = 370;
				rSource.top = 628;
				rSource.right = 405;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 54:
			{
				rSource.left = 444;
				rSource.top = 628;
				rSource.right = 480;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 55:
			{
				rSource.left = 518;
				rSource.top = 628;
				rSource.right = 554;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 56:
			{
				rSource.left = 594;
				rSource.top = 628;
				rSource.right = 628;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 57:
			{
				rSource.left = 668;
				rSource.top = 628;
				rSource.right = 702;
				rSource.bottom = 666;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 58:
			{
				rSource.left = 805;
				rSource.top = 910;
				rSource.right = 815;
				rSource.bottom = 955;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 65:
			{
				rSource.left = 20;
				rSource.top = 64;
				rSource.right = 54;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 66:
			{
				rSource.left = 93;
				rSource.top = 64;
				rSource.right = 128;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 67:
			{
				rSource.left = 168;
				rSource.top = 64;
				rSource.right = 202;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 68:
			{
				rSource.left = 242;
				rSource.top = 64;
				rSource.right = 277;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 69:
			{
				rSource.left = 316;
				rSource.top = 64;
				rSource.right = 351;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 70:
			{
				rSource.left = 390;
				rSource.top = 64;
				rSource.right = 425;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 71:
			{
				rSource.left = 464;
				rSource.top = 64;
				rSource.right = 498;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 72:
			{
				rSource.left = 539;
				rSource.top = 64;
				rSource.right = 574;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 73:
			{
				rSource.left = 614;
				rSource.top = 64;
				rSource.right = 622;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 74:
			{
				rSource.left = 662;
				rSource.top = 64;
				rSource.right = 690;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 75:
			{
				rSource.left = 730;
				rSource.top = 64;
				rSource.right = 765;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 76:
			{
				rSource.left = 804;
				rSource.top = 64;
				rSource.right = 832;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 77:
			{
				rSource.left = 872;
				rSource.top = 64;
				rSource.right = 920;
				rSource.bottom = 104;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 78:
			{
				rSource.left = 18;
				rSource.top = 192;
				rSource.right = 61;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 79:
			{
				rSource.left = 100;
				rSource.top = 192;
				rSource.right = 134;
				rSource.bottom = 231;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 80:
			{
				rSource.left = 174;
				rSource.top = 192;
				rSource.right = 208;
				rSource.bottom = 231;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 81:
			{
				rSource.left = 248;
				rSource.top = 192;
				rSource.right = 284;
				rSource.bottom = 236;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 82:
			{
				rSource.left = 322;
				rSource.top = 192;
				rSource.right = 357;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 83:
			{
				rSource.left = 396;
				rSource.top = 192;
				rSource.right = 431;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 84:
			{
				rSource.left = 470;
				rSource.top = 192;
				rSource.right = 506;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 85:
			{
				rSource.left = 544;
				rSource.top = 192;
				rSource.right = 581;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 86:
			{
				rSource.left = 620;
				rSource.top = 192;
				rSource.right = 654;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 87:
			{
				rSource.left = 694;
				rSource.top = 192;
				rSource.right = 743;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 88:
			{
				rSource.left = 782;
				rSource.top = 192;
				rSource.right = 817;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 89:
			{
				rSource.left = 856;
				rSource.top = 192;
				rSource.right = 890;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 90:
			{
				rSource.left = 930;
				rSource.top = 192;
				rSource.right = 966;
				rSource.bottom = 232;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 92:
			{
				rSource.left = 115;
				rSource.top = 1036;
				rSource.right = 150;
				rSource.bottom = 1076;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 97:
			{
				rSource.left = 19;
				rSource.top = 344;
				rSource.right = 52;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 98:
			{
				rSource.left = 93;
				rSource.top = 344;
				rSource.right = 128;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 99:
			{
				rSource.left = 168;
				rSource.top = 344;
				rSource.right = 202;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 100:
			{
				rSource.left = 242;
				rSource.top = 344;
				rSource.right = 276;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 101:
			{
				rSource.left = 316;
				rSource.top = 344;
				rSource.right = 350;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 102:
			{
				rSource.left = 391;
				rSource.top = 344;
				rSource.right = 418;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 103:
			{
				rSource.left = 459;
				rSource.top = 344;
				rSource.right = 493;
				rSource.bottom = 396;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 104:
			{
				rSource.left = 532;
				rSource.top = 344;
				rSource.right = 568;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 105:
			{
				rSource.left = 607;
				rSource.top = 344;
				rSource.right = 616;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 106:
			{
				rSource.left = 654;
				rSource.top = 344;
				rSource.right = 670;
				rSource.bottom = 396;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 107:
			{
				rSource.left = 710;
				rSource.top = 344;
				rSource.right = 746;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 108:
			{
				rSource.left = 784;
				rSource.top = 344;
				rSource.right = 792;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 109:
			{
				rSource.left = 834;
				rSource.top = 344;
				rSource.right = 881;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 110:
			{
				rSource.left = 920;
				rSource.top = 344;
				rSource.right = 956;
				rSource.bottom = 384;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 111:
			{
				rSource.left = 18;
				rSource.top = 474;
				rSource.right = 53;
				rSource.bottom = 512;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 112:
			{
				rSource.left = 94;
				rSource.top = 474;
				rSource.right = 128;
				rSource.bottom = 524;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 113:
			{
				rSource.left = 168;
				rSource.top = 474;
				rSource.right = 202;
				rSource.bottom = 522;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 114:
			{
				rSource.left = 241;
				rSource.top = 474;
				rSource.right = 270;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 115:
			{
				rSource.left = 310;
				rSource.top = 474;
				rSource.right = 345;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 116:
			{
				rSource.left = 384;
				rSource.top = 474;
				rSource.right = 413;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 117:
			{
				rSource.left = 452;
				rSource.top = 474;
				rSource.right = 488;
				rSource.bottom = 512;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 118:
			{
				rSource.left = 527;
				rSource.top = 474;
				rSource.right = 561;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 119:
			{
				rSource.left = 600;
				rSource.top = 474;
				rSource.right = 649;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 120:
			{
				rSource.left = 689;
				rSource.top = 474;
				rSource.right = 724;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 121:
			{
				rSource.left = 763;
				rSource.top = 474;
				rSource.right = 798;
				rSource.bottom = 524;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		case 122:
			{
				rSource.left = 838;
				rSource.top = 474;
				rSource.right = 872;
				rSource.bottom = 514;
				m_nCharWidth = rSource.right - rSource.left;
				m_nCharHeight = rSource.bottom - rSource.top;
				break;
			}
		}
		return rSource;
	}
	void Print(		const char*	szText,		int nX, int nY,
					float fScale,			DWORD dwColor, int nMaxWidth = -1 )
	{
		// Iterate through the string 1 character at a time
		int nLength = strlen( szText );
		int nMovedWidth = 0;
		int nStoredX = nX;

		std::stringstream ss(szText);
		std::string buffer;
		vector<std::string> words;
		int nWordToDraw = 0;
		while (ss >> buffer)
		{
			words.push_back(buffer);
		}

		for (int i = 0; i < words.size(); ++i)
		{
			int jLength = strlen(words[i].c_str());
			int nWordLength = 0;
			if (nMaxWidth != -1)
			{
				for (int nI = 0; nI < jLength; ++nI)
				{
					RECT rTile = CellAlgorithm(words[i].c_str()[nI]);
					nWordLength += (int)(m_nCharWidth * fScale) + 2;
				}
				if (nWordLength + nMovedWidth > nMaxWidth)
				{
					nY += m_nCharHeight * fScale;
					nX = nStoredX;
					nMovedWidth = 0;
				}
			}
			for (int j = 0; j < jLength; ++j)
			{
				char ch = words[i].c_str()[j];

				int id = ch;
				RECT rTile = CellAlgorithm(id);
				D3DXCOLOR black = dwColor;
				black.r = black.g = black.b = 0;
				pTM->Draw( jcs_nImageID, nX + 2, nY + 2, fScale, fScale, &rTile,
							0.0f, 0.0f, 0.0f,black );
				pTM->Draw( jcs_nImageID, nX, nY, fScale, fScale, &rTile,
							0.0f, 0.0f, 0.0f, dwColor );
				float Scale = fScale*100;
				int nMovedAmount = (int)(m_nCharWidth * fScale) + 2;
				nX += (int)(m_nCharWidth * fScale) + 2;
				if (nMaxWidth != -1)
				{
					nMovedWidth += nMovedAmount;
					if (nMovedWidth >= nMaxWidth)
					{
						nY += m_nCharHeight * fScale;
						nX = nStoredX;
						nMovedWidth = 0;
					}	
				}
			}
			nX += 10;
		}

		//for( int i = 0; i < nLength; i++ )
		//{
		//	// Get char out of the string
		//	char ch = szText[ i ];

		//	// Check for whitespace
		//	if( ch == ' ' )
		//	{
		//		//float Scale = fScale*100;
		//		nX += 10;
		//		continue;
		//	}
		//	// Calculate the tile id for this character
		//	int id = ch;
		//	// Get the source rect using the Cell Algorithm
		//	RECT rTile = CellAlgorithm( id );
		//	D3DXCOLOR black = dwColor;
		//	black.r = black.g = black.b = 0;
		//	pTM->Draw( jcs_nImageID, nX + 2, nY + 2, fScale, fScale, &rTile,
		//				0.0f, 0.0f, 0.0f,black );
		//	pTM->Draw( jcs_nImageID, nX, nY, fScale, fScale, &rTile,
		//				0.0f, 0.0f, 0.0f, dwColor );
		//	float Scale = fScale*100;
		//	int nMovedAmount = (int)(m_nCharWidth * fScale) + 2;
		//	nX += (int)(m_nCharWidth * fScale) + 2;
		//	
		//	if (nMaxWidth != -1)
		//	{
		//		nMovedWidth += nMovedAmount;
		//		if (nMovedWidth >= nMaxWidth)
		//		{
		//			nY += m_nCharHeight * fScale;
		//			nX = nStoredX;
		//			nMovedWidth = 0;
		//		}
		//	}
		//}
	}
};
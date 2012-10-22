#pragma once

class CTile;

class CAbility
{

private:
public:
	std::string m_strLuaFile;
	std::string m_strParticleFile;
	std::string m_strName;
	std::string m_strDescription;

	std::vector< Vec2D > m_vPattern;

	int m_nAPCost;
	int m_nCooldown;
	int m_nRange;
	int m_nNumTargets;
	int m_nIconID;
	int m_nSoundID;
	int m_nDamage;		// negative = heal / positive = damage / 0 = debuff/buff 
	GAME_PHASE m_nPhase;
	PRTCL_TYPE m_nParticle;

	TSTRING m_szInterfaceIcon;

	SPELL_TYPE m_eType;

	bool m_bIsAttack;
	bool m_bIsMove; // SPECIFICALLY if this is the Move "spell"

public:

	CAbility(void);
	CAbility(vector<Vec2D> vPattern, int nAP, int nCD, int nRange,
				int nTarget, GAME_PHASE Phase, bool bAttack, string luaFile, string particleFile, string name, int ID);
	~CAbility(void);

	void SetType(SPELL_TYPE st) { m_eType = st;}
	SPELL_TYPE GetType(void) { return m_eType;}
	int GetApCost( void ) const { return m_nAPCost; }
	int GetCoolDown( void ) const { return m_nCooldown; }
	int GetRange( void ) const { return m_nRange; }
	int GetTargets( void ) const { return m_nNumTargets; }
	GAME_PHASE GetPhase( void ) const { return m_nPhase; }
	TSTRING GetIcon( void ) const { return m_szInterfaceIcon; }
	bool GetIfAttack( void ) const { return m_bIsAttack; }
	bool GetIfMove( void ) const { return m_bIsMove; }
	std::vector< Vec2D > GetPattern( void ) const { return m_vPattern; }
	Vec2D GetPatternPos( int i ) const { return m_vPattern[i]; }
	std::string GetName( void ) const { return m_strName; }
	std::string GetLua( void ) const { return m_strLuaFile; }
	std::string GetParticleFile( void ) const { return m_strParticleFile; }
	PRTCL_TYPE GetParticleType( void ) const { return m_nParticle; }
	int GetSound( void ) const { return m_nSoundID; }
	int GetDamage( void ) const { return m_nDamage; }
	std::string GetDescription( void ) const { return m_strDescription; }
	int GetIconID( void ) const { return m_nIconID; }

	void SetIcon( TSTRING icon ) { m_szInterfaceIcon = icon; }
	void SetIsMove( bool bMove ) { m_bIsMove = bMove; }
	void SetParticleFile( std::string part ) { m_strParticleFile = part; }
	void SetParticleType( PRTCL_TYPE type ) { m_nParticle = type; }
	void SetSound( int ID ) { m_nSoundID = ID; }
	void SetDamage( int damage ) { m_nDamage = damage; }
	void SetDescription( std::string desc ) { m_strDescription = desc; }
	void SetIconID( int id ) { m_nIconID = id; }
};


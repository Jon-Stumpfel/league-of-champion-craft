#pragma once
class StringTable
{
public:
	std::string GetString(std::string tempstring, bool ability = false);
	static StringTable* GetInstance();
	void SetLanguage(bool IsItModernEnglish);
	static void DeleteInstance(void);
	bool GetIsItModern() {return IsItModern;}
private:
	StringTable(void);
	~StringTable(void);
	StringTable(const StringTable&);
	StringTable* operator=(StringTable&);
	std::vector<std::string> modernenglish;
	std::vector<std::string> yeoldeanglish;
	bool IsItModern;
	static StringTable* s_Instance;
};


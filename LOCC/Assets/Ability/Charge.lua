function OnUse( )
	
damage = 6;
	for i = 1, table.getn(tUnitData) do
		tUnitData[i].health = tUnitData[i].health - damage;
		damage = damage + 2;
	end

end
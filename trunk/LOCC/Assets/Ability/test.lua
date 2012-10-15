function OnUse (...)

	for i = 1, table.getn(tUnitData) do
		tUnitData[i].health = tUnitData[i].health - 10;
	end
	
	return tUnitData;

end
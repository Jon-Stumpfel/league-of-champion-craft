function OnUse (...)

	for i = 1, table.getn(tUnitData) do
		tUnitData[i].Health = tUnitData[i].Health - 10;
	end
	
	return tUnitData;

end
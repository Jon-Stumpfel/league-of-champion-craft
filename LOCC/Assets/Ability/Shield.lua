function OnUse ()
	for i = 1, table.getn(tUnitData) do
		tUnitData[i].shielded = 1;
	end
end
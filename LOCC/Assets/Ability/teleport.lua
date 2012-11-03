function OnUse( )

	for i = 1, table.getn(tUnitData) do
		Teleport(tUnitData[i].uniqueID);
	end

end
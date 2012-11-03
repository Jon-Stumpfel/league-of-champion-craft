function OnUse( )

	for i = 1, table.getn(tUnitData) do
		Sacrifice(tUnitData[i].uniqueID);
	end

end
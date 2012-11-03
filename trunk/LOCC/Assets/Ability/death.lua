function OnUse( )

	for i = 1, table.getn(tUnitData) do
		Death(tUnitData[i].uniqueID);
	end

end
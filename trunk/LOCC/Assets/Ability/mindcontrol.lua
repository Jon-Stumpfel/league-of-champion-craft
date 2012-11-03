function OnUse( )

	for i = 1, table.getn(tUnitData) do
		MindControl(tUnitData[i].uniqueID);
	end

end
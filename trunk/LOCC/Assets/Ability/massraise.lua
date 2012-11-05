function OnUse( )

	GetAbilityPattern(1);
	for i = 1, table.getn(tPattern) do

		RaiseDead(tPattern[i].posX, tPattern[i].posY)

	end

end

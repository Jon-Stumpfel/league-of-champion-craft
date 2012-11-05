function OnUse ()

	GetAbilityPattern(2);
	for i = 1, table.getn(tPattern) do
		Encase(tPattern[i].posX, tPattern[i].posY);
	end

end
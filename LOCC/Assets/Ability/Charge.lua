function OnUse( )
damage = 6;
	for i = 1, table.getn(tUnitData) do
		DoDamage(tUnitData[i].uniqueID, damage);
		pixelX, pixelY = TranslateToPixel(tUnitData[i].posX, tUnitData[i].posY);
		AddText("" .. damage, pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);
		damage = damage + 2;
	end

end
function OnUse ()
	for i = 1, table.getn(tUnitData) do

	damage = DoDamage(tUnitData[i].uniqueID, 6);
	pixelX, pixelY = TranslateToPixel(tUnitData[i].posX, tUnitData[i].posY);
	AddText("" .. damage, pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);

	end
end
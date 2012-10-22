function OnUse ()


	for i = 1, table.getn(tUnitData) do
		DoDamage(tUnitData[i].uniqueID, 15);
		pixelX, pixelY = TranslateToPixel(tUnitData[i].posX, tUnitData[i].posY);
		AddText("15", pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);
	end
end
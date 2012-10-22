function OnUse ()

	for i = 1, table.getn(tUnitData) do
		tUnitData[i].health = tUnitData[i].health + 8;
		pixelX, pixelY = TranslateToPixel(tUnitData[i].posX, tUnitData[i].posY);
		AddText("8", pixelX, pixelY, 0, -40, 3, 0.4, 0, 255, 0);
	end

end
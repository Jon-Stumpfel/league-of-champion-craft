function OnUse ()

	for i = 1, table.getn(tUnitData) do
		FireWep( tUnitData[i].nUniqueID);
		pixelX, pixelY = TranslateToPixel(tUnitData[i].posX, tUnitData[i].posY);
		AddText("Damage Up", pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);
	end
end
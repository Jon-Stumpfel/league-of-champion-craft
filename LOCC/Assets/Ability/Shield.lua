function OnUse ()
	for i = 1, table.getn(tUnitData) do
		Shield(tUnitData[i].uniqueID);
		pixelX, pixelY = TranslateToPixel(tUnitData[1].posX, tUnitData[1].posY);
		AddText("Shielded!", pixelX, pixelY, 0, -40, 3, 0.4, 50, 50, 255)
	end
end
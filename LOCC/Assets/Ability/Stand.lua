function OnUse()

	for i = 1, table.getn(tUnitData) do
		StandGround(tUnitData[i].uniqueID);
		pixelX, pixelY = TranslateToPixel(tUnitData[1].posX, tUnitData[1].posY);
		AddText("Ground Standed!", pixelX, pixelY, 0, -40, 3, 0.4, 50, 50, 255)
	end

end
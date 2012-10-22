function OnUse()

		Speed(tUnitData[1].uniqueID);
		pixelX, pixelY = TranslateToPixel(tUnitData[1].posX, tUnitData[1].posY);
		AddText("Speed Up!", pixelX, pixelY, 0, -40, 3, 0.4, 20, 20, 255);
		
end
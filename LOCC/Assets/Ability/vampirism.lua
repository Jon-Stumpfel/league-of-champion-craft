function OnUse ()

	FindTeam(tUnitData[1].uniqueID);
	for i = 1, table.getn(tAffected) do
		Vamp(tAffected[i].uniqueID);
		pixelX, pixelY = TranslateToPixel(tAffected[i].posX, tAffected[i].posY);
		AddText("Vampirised", pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);
	end
end

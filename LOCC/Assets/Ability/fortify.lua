function OnUse( )

	FindTeam(tUnitData[1].uniqueID);

	for i = 1, table.getn(tAffected) do
		Fortify(tAffected[i].uniqueID);
		pixelX, pixelY = TranslateToPixel(tAffected[i].posX, tAffected[i].posY);
		AddText("Fortified", pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);
	end

end
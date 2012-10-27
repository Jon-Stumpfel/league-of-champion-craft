function OnUse( )

	Chaining(tUnitData[1].uniqueID);
	damage = DoDamage(tUnitData[1].uniqueID, 9 );
	pixelX, pixelY = TranslateToPixel(tUnitData[1].posX, tUnitData[1].posY);
	AddText( "" .. damage, pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);

	for i = 1, table.getn(tAffected)  do

		damage = DoDamage(tAffected[i].uniqueID, 9);
		pixelX, pixelY = TranslateToPixel(tAffected[i].posX, tAffected[i].posY);
		AddText( "" .. damage, pixelX, pixelY, 0, -40, 3, 0.4, 255, 0, 0);

	do

end
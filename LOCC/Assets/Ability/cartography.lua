function OnUse()
  SetFreeMove(tUnitData[1].uniqueID);
 pixelX, pixelY = TranslateToPixel(tUnitData[1].posX, tUnitData[1].posY);
 AddText("Cartography", pixelX, pixelY, 10, -30, 3, 0.4, 30, 255, 30);
end
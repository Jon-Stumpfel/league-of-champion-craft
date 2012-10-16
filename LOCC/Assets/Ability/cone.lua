function OnUse()
 

 --print ("Test Table Input");

 tUnitData[3].health = tUnitData[3].health - 10;
 for lolwut = 2, table.getn(tUnitData) do
  --print ("Unit " .. ", x: " .. tUnitData[i].posX .. ", y: " .. tUnitData[i].posY .. ", hp: " .. tUnitData[i].health .. ", speed: " .. tUnitData[i].speed);
	tUnitData[lolwut].health = tUnitData[lolwut].health - 10;
 end	
 
end
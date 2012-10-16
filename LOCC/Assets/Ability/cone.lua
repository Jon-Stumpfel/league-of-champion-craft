function OnUse()
 

 --print ("Test Table Input");

	for i = 1, table.getn(tUnitData)	do
		tUnitData[i].health = tUnitData[i].health - 10;
	end
 
end
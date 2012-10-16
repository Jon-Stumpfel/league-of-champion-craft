
function OnUse()
	

	--print ("Test Table Input");
	
	--tUnitData[1].health = 5;
	--tUnitData[2].health = 7;
	--tUnitData[2].health = 9;

	for i = 1, table.getn(tUnitData)	do
		tUnitData[i].health = tUnitData[i].health - 10;
	end
	
end
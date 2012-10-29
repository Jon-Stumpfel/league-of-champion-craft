function Analyze()

	AddText("Analyzing...".. unitID, 100, 100, 0, -40, 3, 0.4, 20, 20, 255);

end

function Move()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));
	totdistance = distancex + distancey;

	pixelX, pixelY = TranslateToPixel(localX, localY);
	
	isFleeing = GetFleeing(unitID);
	if (isFleeing == true) then
		Flee();
	else
		if (totdistance > 1) then
			MoveToNearestEnemy()
		end
	end
end


function MoveToNearestEnemy()
	IssueOrder("move", targetX, targetY);
end


function Attack()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);	

	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));
	totdistance = distancex + distancey;
	
	-- Check for nearby dudes
	numNearby = 0;
	unit1 = FindUnitByTile(localX +1, localY);
	if (unit1 ~= -1) then
		numNearby = numNearby + 1;
	end
	
	unit2 = FindUnitByTile(localX -1, localY);
	if (unit2 ~= -1) then
		numNearby = numNearby + 1;
	end
	
	unit3 = FindUnitByTile(localX, localY +1 );
	if (unit3 ~= -1) then
		numNearby = numNearby + 1;
	end
	
	unit4 = FindUnitByTile(localX, localY - 1);
	if (unit4 ~= -1) then
		numNearby = numNearby + 1;
	end

	
	if (numNearby >= 3) then
		StandGround()
	end
	
	if (totdistance == 1) then
		AttackNearest();
	end
end

function StandGround()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 3);
	IssueOrder("selectunit", unitID);
end

function AttackNearest()
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 2);
	IssueOrder("selectunit", nearestID);
end
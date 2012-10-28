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
	AddText("Hero Move...", pixelX, pixelY, 0, -40, 5, 0.4, 20, 255, 20);	
	
	
	if (totdistance > 1) then
		MoveToNearestEnemy()
	end
end


function MoveToNearestEnemy()
	IssueOrder("move", targetX, targetY);
end


function Attack()

	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	
	AddText("Hero Attack...", pixelX, pixelY, 0, -40, 5, 0.4, 20, 255, 20);	

	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));
	totdistance = distancex + distancey;
	
	if (totDistance == 1) then
		AttackNearest()
	end
end

function AttackNearest()
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 2);
	IssueOrder("selectunit", nearestID);
end
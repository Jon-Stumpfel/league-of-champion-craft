function Analyze()

	AddText("Analyzing...".. unitID, 100, 100, 0, -40, 3, 0.4, 20, 20, 255);

end


function Move()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	
	isFleeing = GetFleeing(unitID);
	if (isFleeing == true) then
		Flee();
	else		
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));
	totdistance = distancex + distancey;


		if (totdistance > 1) then
			MoveToNearestEnemy()
		end
	end
end

function Flee()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	AddText("Fleeing...!", pixelX, pixelY, 0, -10, 6, 0.4, 255, 20, 20);
	championID = FindChampion(unitID);
	targetX, targetY = GetUnitPosition(championID);	
	IssueOrder("move", targetX, targetY);
end


function MoveToNearestEnemy()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	AddText("Moving To Nearest...", pixelX, pixelY, 0, -10, 6, 0.4, 20, 255, 20);
	IssueOrder("move", targetX, targetY);
end

function Attack()
	
end
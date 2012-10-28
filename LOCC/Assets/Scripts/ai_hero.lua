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

	if (totdistance > 1) then
		MoveToNearestEnemy()
	end
end


function MoveToNearestEnemy()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	AddText("Moving To Nearest...", pixelX, pixelY, 0, -10, 6, 0.4, 20, 255, 20);
	IssueOrder("move", targetX, targetY);
end


function Attack()
end
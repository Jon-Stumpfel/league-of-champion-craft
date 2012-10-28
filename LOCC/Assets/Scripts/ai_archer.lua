function Analyze()

	AddText("Analyzing...".. unitID, 100, 100, 0, -40, 3, 0.4, 20, 20, 255);

end

function Move()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	
	-- lets check if we are fleeing before we do anything
	isFleeing = GetFleeing(unitID);
	if (isFleeing == true) then
		Flee();
	else
		distancex = math.abs((targetX - localX));
		distancey = math.abs((targetY - localY));
		totdistance = distancex + distancey;

		if (totdistance > 3) then
			MoveToNearestEnemy()
		elseif (totdistance == 1) then
			Skirmish()
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

function Skirmish()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	AddText("Skirmishing...", pixelX, pixelY, 0, -10, 6, 0.4, 255, 20, 20);
	IssueOrder("skirmish", unitID);

end

function MoveToNearestEnemy()
	IssueOrder("move", targetX, targetY);
end



function Attack()
	
end
function Analyze()

	AddText("Analyzing...".. unitID, 100, 100, 0, -40, 3, 0.4, 20, 20, 255);

end

function Move()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	
	pixelX, pixelY = TranslateToPixel(localX, localY);
	-- lets check if we are fleeing before we do anything
	isFleeing = GetFleeing(unitID);
	if (isFleeing == true) then
		Flee();
	else
	
		-- Priority is to capture mines or mills
		numMills = GetMillsOwned(unitID);
		numMines = GetMinesOwned(unitID);
		moved = 0;
		if (numMills < 1) then
			resourceX, resourceY = FindNearestResource(unitID, 1);
			resourcedistX = math.abs((resourceX - localX));
			resourcedistY = math.abs((resourceY - localY));
			resourceTotDist = resourcedistX + resourcedistY;
			if (resourceTotDist ~= 0) then
				IssueOrder("move", resourceX, resourceY);
				moved = 1;
			end
		end
		distancex = math.abs((targetX - localX));
		distancey = math.abs((targetY - localY));
		totdistance = distancex + distancey;

		if (moved ~= 1) then
			if (totdistance > 3) then
				MoveToNearestEnemy()
			elseif (totdistance == 1) then
				Skirmish()
			end
		end
	end
end

function Flee()
	championID = FindChampion(unitID);
	targetX, targetY = GetUnitPosition(championID);	
	IssueOrder("move", targetX, targetY);
end

function Skirmish()

	IssueOrder("skirmish", unitID);

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
	
	tilesMoved = GetTilesMoved(unitID);
	enemyHealth = GetHealth(nearestID);
	if (totdistance > 3) then
		IssueOrder("deselectall");
	elseif ((tilesMoved == 0) and(enemyHealth < 12)) then
		Volley()
	else
		AttackNearest()
	end

end

function Volley()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);	
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 3);
	IssueOrder("selectunit", nearestID);
end

function AttackNearest()
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 2);
	IssueOrder("selectunit", nearestID);
end
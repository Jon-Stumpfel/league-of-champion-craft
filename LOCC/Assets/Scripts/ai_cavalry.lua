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
	championID = FindChampion(unitID);
	targetX, targetY = GetUnitPosition(championID);	
	IssueOrder("move", targetX, targetY);
end


function MoveToNearestEnemy()
	IssueOrder("move", targetX, targetY);
end

function Attack()
	AttackNearest()
end

function AttackNearest()
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 2);
	IssueOrder("selectunit", nearestID);
end
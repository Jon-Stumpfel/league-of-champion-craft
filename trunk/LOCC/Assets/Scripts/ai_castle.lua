function Analyze()

	AddText("Analyzing...".. unitID, 100, 100, 0, -40, 3, 0.4, 20, 20, 255);

end


function Move()
	--MoveToNearestEnemy()
end

function MoveToNearestEnemy()
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	IssueOrder("move", targetX, targetY);
end



function Attack()
	
end
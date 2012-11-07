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

	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);

	nearestID = FindNearest(unitID);

	targetX, targetY = GetUnitPosition(nearestID);

	localX, localY = GetUnitPosition(unitID);

	directionx = (targetX - localX);
	directiony = (targetY - localY);	
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));

	totdistance = distancex + distancey;

	doCharge = false;
	chargeDirection = -1;
	-- Check if it is appropriate to charge, I.E we can hit 2 people
	-- Not checking if we are charging friendlies...oh well! BERSERKER
	--AddText("Do Charge?..." .. doCharge, pixelX, pixelY, 40, 0, 5, 0.4, 20, 255, 20);
	if (directionx == 1) then
		secondUnitID = FindUnitByTile(targetX + 1, targetY);

		if (secondUnitID ~= -1) then
			doCharge = true;
			chargeDirection = 1;
		end
	elseif (directionx == -1) then
		secondUnitID = FindUnitByTile(targetX - 1, targetY);
		if (secondUnitID ~= -1) then
			doCharge = true;
			chargeDirection = 2;
		end
	elseif (directiony == 1) then
		secondUnitID = FindUnitByTile(targetX, targetY + 1);
		if (secondUnitID ~= -1) then
			doCharge = true;
			chargeDirection = 3;
		end
	elseif (directiony == -1) then
		secondUnitID = FindUnitByTile(targetX, targetY - 1);
		if (secondUnitID ~= -1) then
			doCharge = true;
			chargeDirection = 4;
		end	
	end

	if (totdistance == 1) then
		if (doCharge == true) then
			Charge();
		else
			AttackNearest();
		end
	end
end

function Charge()
	localX, localY = GetUnitPosition(unitID);
	pixelX, pixelY = TranslateToPixel(localX, localY);

	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 3);
	
	deltaX = 0;
	deltaY = 0;
	
	if (chargeDirection == 1) then
		deltaX = 1;
		deltaY = 0;
	elseif (chargeDirection == 2) then
		deltaX = -1;
		deltaY = 0;
	elseif (chargeDirection == 3) then
		deltaY = 1;
		deltaX = 0;
	elseif (chargeDirection == 4) then
		deltaY = -1;
		deltaX = 0;
	end
	
	for i = 1, 4 do
		IssueOrder("selecttile", localX + (i*deltaX), localY + (i*deltaY));
	end
	
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
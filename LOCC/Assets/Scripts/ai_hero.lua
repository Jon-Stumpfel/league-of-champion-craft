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

	-- First and foremost, cast rally if there are more than 2 or more friendlies in range, not including myself
	numFriendlies = 0;

	testID = FindUnitByTile(localX - 2, localY);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end
	testID = FindUnitByTile(localX - 1, localY);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX + 1, localY);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX + 2, localY);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX - 1, localY - 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end
	testID = FindUnitByTile(localX, localY - 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX + 1, localY - 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX, localY - 2);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX - 1, localY + 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end
	testID = FindUnitByTile(localX, localY + 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX + 1, localY + 1);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end	
	testID = FindUnitByTile(localX, localY + 2);
	if (testID ~= -1) then
		if (GetPlayerID(testID) == GetPlayerID(unitID)) then
			numFriendlies = numFriendlies + 1;
		end
	end		

	if (numFriendlies >= 3) then
		Rally()
	end
	
	-- Lets see if anyone needs to be healed
	AddText("Total Distance:  " .. totdistance, pixelX, pixelY, 0, 40, 5, 0.4, 20, 255, 20);
	
	if (totdistance > 1) then
		MoveToNearestEnemy()
	end
end

function Rally()
	AddText("Rallying..! ", pixelX, pixelY, 0, -40, 5, 0.4, 255, 20, 20);
	IssueOrder("selectspell", 2);

end

function MoveToNearestEnemy()
	AddText("Move To Nearest ", pixelX, pixelY, -40, 0, 5, 0.4, 20, 255, 20);
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
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
	
	-- Priority based spell casting? Maybe!
	-- Start with heal. Hurt friendlies that are fleeing are high priority. Check in range
	-- We assume the hero has 
	
	
	
	if (totdistance == 1) then
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
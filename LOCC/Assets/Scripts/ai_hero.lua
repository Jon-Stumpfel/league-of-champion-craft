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
	
	-- Rally logic!
	nRallyID = HasSpell(unitID, 17);
	if (nRallyID ~= -1) then
		rallyCooldown = GetSpellCooldown(unitID, nRallyID);
		if (rallyCooldown == 0) then
			-- copy code goes here
			GetFriendlyUnitsInRange(unitID, 2);
			numFriendlies = table.getn(unitData);
			if (numFriendlies >= 2) then
				Rally(nRallyID + 1)
			end
		end
	end

	
	-- Healing logic!
	nHealID = HasSpell(unitID, 7);
	if (nHealID ~= -1) then
		healCooldown = GetSpellCooldown(unitID, nRallyID);
		if (healCooldown == 0) then
			GetFriendlyUnitsInRange(unitID, 3);
		
			lowestHP = 99999999;
			lowestHPunitID = -1;		
			for i = 1, table.getn(unitData) do
				unitHealth = GetHealth(unitData[1].uniqueID);	
				if (unitHealth < lowestHP) then
					lowestHP = unitHealth;
					lowestHPunitID = unitData[i].uniqueID;
				end
			end	
			if (GetHealth(lowestHPunitID) <= GetMaxHealth(lowestHPunitID) - 6) then
				Heal(nHealID + 1, lowestHPunitID);
			end	
		end
		
	end
	
	if (totdistance > 1) then
		MoveToNearestEnemy()
	end
end
function Heal(healID, lowestHPunitID)

	IssueOrder("selectspell", healID);
	IssueOrder("selectunit", lowestHPunitID);

end
function Rally(nRallyID)
	IssueOrder("selectspell", nRallyID);

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
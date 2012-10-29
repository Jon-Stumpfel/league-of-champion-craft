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
	
	-- Rally logic: If within range of at least 2 friendlies, and more friendlies than enemies
	nRallyID = HasSpell(unitID, 17);
	if (nRallyID ~= -1) then
		rallyCooldown = GetSpellCooldown(unitID, nRallyID);
		if (rallyCooldown == 0) then
			-- copy code goes here
			GetFriendlyUnitsInRange(unitID, 2);
			GetEnemyUnitsInRange(unitID, 2);
			numEnemies = table.getn(enemyUnitData);
			numFriendlies = table.getn(unitData);		
			if (numFriendlies >= 2 and (numEnemies < numFriendlies)) then
				Rally(nRallyID + 1)
			end
		end
	end

	-- Healing logic: Find nearest wounded friendly (including myself) and heal.
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

	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	localX, localY = GetUnitPosition(unitID);
	distancex = math.abs((targetX - localX));
	distancey = math.abs((targetY - localY));
	totdistance = distancex + distancey;
	
	-- Priority based spell casting? Maybe!
	-- Start with heal. Hurt friendlies that are fleeing are high priority. Check in range
	-- We assume the hero has 
	
	hasAttacked = 0;
	
	-- Magic Missile logic: If no one in melee, shoot lowest HP unit in range
	magicID = HasSpell(unitID, 24);	
	if (magicID ~= -1 and totdistance ~= 1) then

		magicCooldown = GetSpellCooldown(unitID, magicID);	
		if (magicCooldown == 0) then
			GetEnemyUnitsInRange(unitID, 3);
			
			lowestHP = 999;
			lowestHPunitID = -1;	
			
			for i = 1, table.getn(enemyUnitData) do
				unitHP = GetHealth(enemyUnitData[i].uniqueID);
				if (unitHP < lowestHP) then
					lowestHP = unitHP;
					lowestHPunitID = enemyUnitData[i].uniqueID;
				end
			end		
			MagicMissile(magicID + 1, lowestHPunitID);
			hasAttacked = 1;
		end
	end
	
	
	
	if (totdistance == 1 and hasAttacked == 0) then

		-- Cleave logic: If enemy has an adjacent, cleave!
		cleaveID = HasSpell(unitID, 37);
		if (cleaveID ~= -1) then
			cleaveCooldown = GetSpellCooldown(unitID, cleaveID);
			if (cleaveCooldown == 0) then
				-- Lets see if we should hit some dudes
				directionx = (targetX - localX);
				directiony = (targetY - localY);	
				numHit = 0;
				if (directiony == -1) then
					numHit = 0;
					unit1 = FindUnitByTile(targetX - 1, targetY );
					unit2 = FindUnitByTile(targetX + 1, targetY );
					if (unit1 ~= -1) then
						numHit = numHit + 1;
					end
					if (unit2 ~= -1) then
						numHit = numHit + 1;
					end
				elseif (directiony == 1) then
					numHit = 0;
					unit1 = FindUnitByTile(targetX - 1, targetY );
					unit2 = FindUnitByTile(targetX + 1, targetY );
					if (unit1 ~= -1) then
						numHit = numHit + 1;
					end
					if (unit2 ~= -1) then
						numHit = numHit + 1;
					end			
				elseif (directionx == -1) then
					numHit = 0;
					unit1 = FindUnitByTile(targetX, targetY - 1);
					unit2 = FindUnitByTile(targetX, targetY + 1 );
					if (unit1 ~= -1) then
						numHit = numHit + 1;
					end
					if (unit2 ~= -1) then
						numHit = numHit + 1;
					end			
				elseif (directionx == 1) then
					numHit = 0;
					unit1 = FindUnitByTile(targetX, targetY - 1);
					unit2 = FindUnitByTile(targetX, targetY + 1 );
					if (unit1 ~= -1) then
						numHit = numHit + 1;
					end
					if (unit2 ~= -1) then
						numHit = numHit + 1;
					end	
				end
			

				
				Cleave(cleaveID + 1, nearestID);
				hasAttacked = 1;
			end
		end
		
		if (hasAttacked == 0) then
			AttackNearest()
		end
	end
end

function Cleave(cleaveID, targetID)
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectspell", cleaveID);
	IssueOrder("selectunit", targetID);
end
function MagicMissile(magicID, lowestHPunitID)
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectspell", magicID);
	IssueOrder("selectunit", lowestHPunitID);
end
function AttackNearest()
	nearestID = FindNearest(unitID);
	targetX, targetY = GetUnitPosition(nearestID);
	
	IssueOrder("deselectall");
	IssueOrder("selectunit", unitID);
	IssueOrder("selectability", 2);
	IssueOrder("selectunit", nearestID);
end
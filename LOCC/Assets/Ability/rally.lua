function OnUse()
  for i = 1, table.getn(tUnitData) do
  Rally(tUnitData[i].uniqueID);
  end
end
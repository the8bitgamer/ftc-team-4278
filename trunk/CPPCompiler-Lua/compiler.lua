lineList = {}
importList = {}

function addNewFile(fileName)
	file = io.open(fileName,"r")
	if file == nil then
		print("Error! Could not open file " .. fileName .. "; are you sure it exists?");
		os.exit(13);
	end
	while true do
		local line = file:read("*l")
		if line == nil then break end
		table.insert(lineList,line)
	end
end

function printTable(t)
	for i,v in pairs(t) do
		print(i,v)
	end
end

function findImports()
	newImports = {}

	for i,v in ipairs(lineList) do
		if string.find(v, "#import") ~= nil then
			table.insert(importList, v)
			table.insert(newImports, string.sub(v, 9))
			table.remove(lineList, i)
			verifyNoDuplicates(importList)
		end
	end

	return newImports;
end

function verifyNoDuplicates(t)
	for i,v in pairs(t) do
		local ct = 0;
		for q,z in pairs(t) do
			if z == v then ct = ct + 1 end
		end

		if ct > 1 then
			print("Error! Duplicate or recursive include: " .. v)
			os.exit(12)
		end
	end
end

function main()
	readIn = true
	addNewFile(arg[1])

	while true do
		printTable(lineList); print("\n\n")
		newImports = findImports()
		if #newImports == 0 then break end
		for i,v in ipairs(newImports) do
			addNewFile(v)
		end
	end
end

main()

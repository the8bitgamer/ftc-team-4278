lineList = {}
importList = {}
functionList = {}
globalVarList = {}

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

function removeWhitespaceLines(t)
	for i,v in ipairs(t) do
		local removeLine = true
		for j=0,#v do
			if v:sub(j,j) ~= "\t" and v:sub(j,j) ~= " " and v:sub(j,j) ~= "" then
				removeLine = false
			end
		end
		if removeLine then table.remove(t, i) end
	end
end

function wordList(str)
	local words = {}
	for word in str:gmatch("%w+") do table.insert(words,word) end
	return words
end

function parseClass(startLine)
	local words = wordList(lineList[startLine])
	local className = words[2]

	endLine = -1
	parensCount = 0
	for i=startLine,#lineList do
		for j=1,#lineList[i] do
			if string.sub(lineList[i],j,j) == "{" then parensCount = parensCount + 1; firstFound = true; end
			if string.sub(lineList[i],j,j) == "}" then parensCount = parensCount - 1 end
			--print(string.sub(lineList[i],j,j), parensCount)
		end
		if parensCount == 0 and firstFound == true then endLine = i; break; end
	end
	--startLine is class entry
	--endLine is class exit

	local typedefList = {}
	local staticList = {}

	for i=startLine,endLine do
		local words = wordList(lineList[i])
		if(words[1] == "int") then
			if(#words > 2) then
				print("Assignment not allowed, or invalid instruction: please use initializer on line " .. i .."! " .. lineList[i])
				os.exit()
			end
			typedefList[#typedefList+1] = words[1] .. " " .. words[2] .. ";"
		end

		if(words[1] == "static") then
			if(#words > 3) then
				print("Assignment not allowed, or invalid instruction: please use initializer on line " .. i .."! " .. lineList[i])
				os.exit()
			end
			staticList[#staticList+1] = words[1] .. " " .. words[2] .. " " .. className .. "_" .. words[3] .. ";"
		end
	end

	printTable(typedefList)
	printTable(staticList)
end

function parseCode()
	for i,v in ipairs(lineList) do
		local words = wordList(v)
		if words[1] == "class" then parseClass(i) end
	end
end

function main()
	readIn = true
	addNewFile(arg[1])

	while true do
		newImports = findImports()
		if #newImports == 0 then break end
		for i,v in ipairs(newImports) do
			addNewFile(v)
		end
	end
	print("Imported the following files (besides the main file):")
	printTable(importList)
	print("")

	removeWhitespaceLines(lineList)
	print("Working with the following operational code:")
	printTable(lineList)

	parseCode()
end

main()

local csv = require("csv") 

local curCsv = nil

function openFile(path)
    local file = csv.open(path)
    curCsv = {}

    for line in file:lines() do
        local columns = {}
        for i, v in ipairs(line) do
            columns[i] = v
        end    
        table.insert(curCsv, columns)
    end
end

function getField(col, row) 
    tex.print(curCsv[row][col])
end

function tabularFromRange(first_col, first_row, second_col, second_row, lineEnd) 
    lineEnd = lineEnd or "\\hline"
    
    for i, row in ipairs(curCsv) do
        if (i >= first_row and i <= second_row) then
            local line = "";
            for j, col in ipairs(row) do
                if(j >= first_col and j<= second_col) then
                    if(j ~= second_col) then
                        line = line .. (tostring(col) or col) .. " & "
                    else
                        line = line .. (tostring(col) or col) .. " \\\\" .. lineEnd
                    end
                end
            end
            tex.print(line)
        end
    end
end

-- openFile("../dimensionamento.csv")
-- getRange(1, 7, 8, 10)
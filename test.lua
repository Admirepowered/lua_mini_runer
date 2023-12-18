local curl = require "lcurl.safe"
local json = require "cjson.safe"
function request_curl(url,header,method,postdata,timeout1)
if timeout1 == nil then
timeout1=20
end

data = ""
if 	method == "POST" then 
	local c = curl.easy{
        url = url,
        post = 1,
        postfields = postdata,
        httpheader = header,
        timeout = timeout1,
        ssl_verifyhost = 0,
        ssl_verifypeer = 0,
        proxy = "",
        writefunction = function(buffer)
            data = data .. buffer
            return #buffer
        end,
	}
	local _, e = c:perform()
	c:close()
	if e then
		return nil
    end
	return data
elseif method == "HEADER" then
	if postdata=="" then
	follw=0
	else
	follw=1
	end
    local c = curl.easy {
        url = url,
        followlocation = follw,
        header = 1,
		--returntransfer = 1,
        nobody = 1,
        httpheader = header,
        timeout = timeout1,
        proxy = "",
        writefunction = function(buffer)
            data = data .. buffer
            return #buffer
        end,
		headerfunction = function(buffer)
            data = data .. buffer
            return #buffer
        end
    }
	--c:setopt(curl.OPT_HEADERFUNCTION, headerfunction)
    local _, e = c:perform()
    c:close()
	
    if e then
        return nil
    end
    return data
else
	local c = curl.easy{
	url = url,
	followlocation = 1,
	httpheader = header,
	timeout = timeout1,
	proxy = "",
	writefunction = function(buffer)
		data = data .. buffer
		return #buffer
	end,
	}
	local _, e = c:perform()
	c:close()
	if e then
		return nil
    end
	return data
end

end


function test()
--local a =io.read()
local url ="http://pan.baidu.com/api/filemetas"
local header = { "User-Agent: Mozilla" }
local data = request_curl(url,header)
local j = json.decode(data)
if j==nil then 
	return "error data"
end
return j.request_id
--return data
end

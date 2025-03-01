-- core script class
local LTBScript = {}
local LTBScript_mt = { __index = LTBScript }

-- inits script base clasee
function LTBScript.Constructor(entity)
    local self = setmetatable({}, LTBScript_mt)
    self.Entity = entity
    return self
end

-- destroy entity with id
function LTBScript.Destroy(entity)
    ApiDestroy(entity)
end

function LTBScript.Testing1(x,y)
    ApiTesting(self.Entity, x, y)
end

-- inits script class
function Initializer()
    -- script class 
    local ScriptKlass = {}
    local ScriptKlass_mt = { __index = ScriptKlass }
    setmetatable(ScriptKlass, { __index = LTBScript })
    
    -- constructor
    function ScriptKlass.Constructor(entity)
        local obj = LTBScript.Constructor(entity)
        self = setmetatable(obj, ScriptKlass_mt)    
        return self
    end
    
    -- apply force to rigidbody
    function ScriptKlass:ApplyForce(force)
        ApiApplyForce(self.Entity, force)
    end
    
    -- destroy self
    function ScriptKlass:Destroy()
        ApiDestroy(self.Entity)
    end

    -- test
    function ScriptKlass:GetX()        
        return ApiGetPositionX(self.Entity)
    end

    function ScriptKlass:Testing(pos)        
        ApiTesting(self.Entity, pos)
    end

     -- get data
    function ScriptKlass:Get(type)
        if type == TRANSFORM then
            return ApiGetTransform(self.Entity)
        end        
        print("invalid type:", type);
        return {}
    end
    
    -- export class
    return ScriptKlass
end

-- export module
return LTBScript

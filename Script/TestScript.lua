-- call once to init script
function TestScript.OnStart(self)
    self.Transform = self:Get(TRANSFORM)    
    self.GetX = self:GetX()
    -- self.Testing = self:Testing()
    print("script started!")
end

function TestScript.TestFunc()
    print("test func")
end

-- update every frame
function TestScript.OnUpdate(self, dt)    
    -- move entity to the left
    if Inputs.IsKeyPressed(Inputs.KEY_A) then
        -- self:ApplyForce(Vec3.new(-100.0, 0.0, 0.0));
        print("KEY_A")
        self.Transform.Translation.x = self.Transform.Translation.x + 5
        print("transx", self.Transform.Translation.x)
        -- self:GetX() = 100;
    end    

    if(Inputs.IsKeyPressed(Inputs.KEY_T)) then
        self:TestFunc()
    end
    -- print("2x testing", self.Testing)    
    -- print("2x pos ", self.GetX)
    -- print("testing agin:", self:Testing1())
    if Inputs.IsKeyPressed(Inputs.KEY_SPACE) then
        print("SPACE")
        pos = Vector2.new()
        pos.x = 300
        pos.y = 200
        self:Testing(pos)        
    end
    
    -- move entity to the right
    if Inputs.IsKeyDown(Inputs.KEY_D) then
        print("KEY_D")
        self.GetX = self.GetX + 2;
    end

    -- scale object every frame
    self.Transform.Scale.y = self.Transform.Scale.y + dt;
end 

-- call when key down
function TestScript.OnResize(self, width, height)
    print("resize: ", width, height)
end

-- call when mouse is down
function TestScript.OnKeyDown(self, button)
    print("Keydown: ", button)
end

-- call when colliding
-- function TestScript.OnCollision(self, other)
--     print("collision:", self.Entity, "->", other)
--     self:Destroy(other);
-- end

-- call when key down
function TestScript.OnKeyPressed(self, key)
    print("keypressed: ", key)
end

-- call when entity is detroyed
function TestScript.OnDestroy(self)
    print("destroyed:", self.Entity)
end


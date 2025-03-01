-- call once on init
function test2.OnStart(self)
    print("test2 started")
end

-- update every frame
function test2.OnUpdate(self, dt)
    -- move entity to the left
    if Inputs.IsKey(Inputs.KEY_A) then
        self:ApplyForce(Vec3.new(-100.0, 0.0, 0.0));
    end
    
    -- move entity to the right
    if Inputs.IsKey(Inputs.KEY_D) then
        self:ApplyForce(Vec3.new(100.0, 0.0, 0.0));
    end

    -- scale object every frame
    self.Transform.Scale.y = self.Transform.Scale.y + dt;
end 

-- call when key down
function test2.OnKeyDown(self, key)
    print("keydown: ", key)
    print("Reload")
end
﻿-- automatically generated by the FlatBuffers compiler, do not modify

-- namespace: Sample

local flatbuffers = require('flatbuffers')

local Vec3 = {} -- the module
local Vec3_mt = {} -- the class metatable

function Vec3.New()
    local o = {}
    setmetatable(o, {__index = Vec3_mt})
    return o
end
function Vec3_mt:Init(buf, pos)
    self.view = flatbuffers.view.New(buf, pos)
end
function Vec3_mt:X()
    return self.view:Get(flatbuffers.N.Float32, self.view.pos + 0)
end
function Vec3_mt:Y()
    return self.view:Get(flatbuffers.N.Float32, self.view.pos + 4)
end
function Vec3_mt:Z()
    return self.view:Get(flatbuffers.N.Float32, self.view.pos + 8)
end
function Vec3.CreateVec3(builder, x, y, z)
    builder:Prep(4, 12)
    builder:PrependFloat32(z)
    builder:PrependFloat32(y)
    builder:PrependFloat32(x)
    return builder:Offset()
end

return Vec3 -- return the module
﻿--[[ Galaxy

  Automatically generated by the FlatBuffers compiler, do not modify.
  Or modify. I'm a message, not a cop.

  flatc version: 23.5.9

  Declared by  : //basic.fbs
  Rooting type : Universe (//basic.fbs)

--]]

local flatbuffers = require('flatbuffers')

local Galaxy = {}
local mt = {}

function Galaxy.New()
  local o = {}
  setmetatable(o, {__index = mt})
  return o
end

function mt:Init(buf, pos)
  self.view = flatbuffers.view.New(buf, pos)
end

function mt:NumStars()
  local o = self.view:Offset(4)
  if o ~= 0 then
    return self.view:Get(flatbuffers.N.Int64, self.view.pos + o)
  end
  return 0
end

function Galaxy.Start(builder)
  builder:StartObject(1)
end

function Galaxy.AddNumStars(builder, numStars)
  builder:PrependInt64Slot(0, numStars, 0)
end

function Galaxy.End(builder)
  return builder:EndObject()
end

return Galaxy
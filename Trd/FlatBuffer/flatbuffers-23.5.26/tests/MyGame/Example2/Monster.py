﻿# automatically generated by the FlatBuffers compiler, do not modify

# namespace: Example2

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Monster(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Monster()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsMonster(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    @classmethod
    def MonsterBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x4D\x4F\x4E\x53", size_prefixed=size_prefixed)

    # Monster
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

def MonsterStart(builder):
    builder.StartObject(0)

def Start(builder):
    MonsterStart(builder)

def MonsterEnd(builder):
    return builder.EndObject()

def End(builder):
    return MonsterEnd(builder)


class MonsterT(object):

    # MonsterT
    def __init__(self):
        pass

    @classmethod
    def InitFromBuf(cls, buf, pos):
        monster = Monster()
        monster.Init(buf, pos)
        return cls.InitFromObj(monster)

    @classmethod
    def InitFromPackedBuf(cls, buf, pos=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, pos)
        return cls.InitFromBuf(buf, pos+n)

    @classmethod
    def InitFromObj(cls, monster):
        x = MonsterT()
        x._UnPack(monster)
        return x

    # MonsterT
    def _UnPack(self, monster):
        if monster is None:
            return

    # MonsterT
    def Pack(self, builder):
        MonsterStart(builder)
        monster = MonsterEnd(builder)
        return monster

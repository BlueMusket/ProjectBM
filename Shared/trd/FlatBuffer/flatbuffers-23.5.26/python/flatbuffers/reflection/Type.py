﻿# automatically generated by the FlatBuffers compiler, do not modify

# namespace: reflection

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Type(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Type()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsType(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    @classmethod
    def TypeBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x42\x46\x42\x53", size_prefixed=size_prefixed)

    # Type
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Type
    def BaseType(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int8Flags, o + self._tab.Pos)
        return 0

    # Type
    def Element(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int8Flags, o + self._tab.Pos)
        return 0

    # Type
    def Index(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int32Flags, o + self._tab.Pos)
        return -1

    # Type
    def FixedLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint16Flags, o + self._tab.Pos)
        return 0

    # The size (octets) of the `base_type` field.
    # Type
    def BaseSize(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(12))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, o + self._tab.Pos)
        return 4

    # The size (octets) of the `element` field, if present.
    # Type
    def ElementSize(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(14))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Uint32Flags, o + self._tab.Pos)
        return 0

def TypeStart(builder):
    builder.StartObject(6)

def Start(builder):
    TypeStart(builder)

def TypeAddBaseType(builder, baseType):
    builder.PrependInt8Slot(0, baseType, 0)

def AddBaseType(builder, baseType):
    TypeAddBaseType(builder, baseType)

def TypeAddElement(builder, element):
    builder.PrependInt8Slot(1, element, 0)

def AddElement(builder, element):
    TypeAddElement(builder, element)

def TypeAddIndex(builder, index):
    builder.PrependInt32Slot(2, index, -1)

def AddIndex(builder, index):
    TypeAddIndex(builder, index)

def TypeAddFixedLength(builder, fixedLength):
    builder.PrependUint16Slot(3, fixedLength, 0)

def AddFixedLength(builder, fixedLength):
    TypeAddFixedLength(builder, fixedLength)

def TypeAddBaseSize(builder, baseSize):
    builder.PrependUint32Slot(4, baseSize, 4)

def AddBaseSize(builder, baseSize):
    TypeAddBaseSize(builder, baseSize)

def TypeAddElementSize(builder, elementSize):
    builder.PrependUint32Slot(5, elementSize, 0)

def AddElementSize(builder, elementSize):
    TypeAddElementSize(builder, elementSize)

def TypeEnd(builder):
    return builder.EndObject()

def End(builder):
    return TypeEnd(builder)

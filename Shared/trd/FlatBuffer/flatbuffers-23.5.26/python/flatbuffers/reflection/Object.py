﻿# automatically generated by the FlatBuffers compiler, do not modify

# namespace: reflection

import flatbuffers
from flatbuffers.compat import import_numpy
np = import_numpy()

class Object(object):
    __slots__ = ['_tab']

    @classmethod
    def GetRootAs(cls, buf, offset=0):
        n = flatbuffers.encode.Get(flatbuffers.packer.uoffset, buf, offset)
        x = Object()
        x.Init(buf, n + offset)
        return x

    @classmethod
    def GetRootAsObject(cls, buf, offset=0):
        """This method is deprecated. Please switch to GetRootAs."""
        return cls.GetRootAs(buf, offset)
    @classmethod
    def ObjectBufferHasIdentifier(cls, buf, offset, size_prefixed=False):
        return flatbuffers.util.BufferHasIdentifier(buf, offset, b"\x42\x46\x42\x53", size_prefixed=size_prefixed)

    # Object
    def Init(self, buf, pos):
        self._tab = flatbuffers.table.Table(buf, pos)

    # Object
    def Name(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(4))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

    # Object
    def Fields(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from reflection.Field import Field
            obj = Field()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Object
    def FieldsLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Object
    def FieldsIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(6))
        return o == 0

    # Object
    def IsStruct(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(8))
        if o != 0:
            return bool(self._tab.Get(flatbuffers.number_types.BoolFlags, o + self._tab.Pos))
        return False

    # Object
    def Minalign(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(10))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int32Flags, o + self._tab.Pos)
        return 0

    # Object
    def Bytesize(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(12))
        if o != 0:
            return self._tab.Get(flatbuffers.number_types.Int32Flags, o + self._tab.Pos)
        return 0

    # Object
    def Attributes(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(14))
        if o != 0:
            x = self._tab.Vector(o)
            x += flatbuffers.number_types.UOffsetTFlags.py_type(j) * 4
            x = self._tab.Indirect(x)
            from reflection.KeyValue import KeyValue
            obj = KeyValue()
            obj.Init(self._tab.Bytes, x)
            return obj
        return None

    # Object
    def AttributesLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(14))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Object
    def AttributesIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(14))
        return o == 0

    # Object
    def Documentation(self, j):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(16))
        if o != 0:
            a = self._tab.Vector(o)
            return self._tab.String(a + flatbuffers.number_types.UOffsetTFlags.py_type(j * 4))
        return ""

    # Object
    def DocumentationLength(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(16))
        if o != 0:
            return self._tab.VectorLen(o)
        return 0

    # Object
    def DocumentationIsNone(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(16))
        return o == 0

    # File that this Object is declared in.
    # Object
    def DeclarationFile(self):
        o = flatbuffers.number_types.UOffsetTFlags.py_type(self._tab.Offset(18))
        if o != 0:
            return self._tab.String(o + self._tab.Pos)
        return None

def ObjectStart(builder):
    builder.StartObject(8)

def Start(builder):
    ObjectStart(builder)

def ObjectAddName(builder, name):
    builder.PrependUOffsetTRelativeSlot(0, flatbuffers.number_types.UOffsetTFlags.py_type(name), 0)

def AddName(builder, name):
    ObjectAddName(builder, name)

def ObjectAddFields(builder, fields):
    builder.PrependUOffsetTRelativeSlot(1, flatbuffers.number_types.UOffsetTFlags.py_type(fields), 0)

def AddFields(builder, fields):
    ObjectAddFields(builder, fields)

def ObjectStartFieldsVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def StartFieldsVector(builder, numElems: int) -> int:
    return ObjectStartFieldsVector(builder, numElems)

def ObjectAddIsStruct(builder, isStruct):
    builder.PrependBoolSlot(2, isStruct, 0)

def AddIsStruct(builder, isStruct):
    ObjectAddIsStruct(builder, isStruct)

def ObjectAddMinalign(builder, minalign):
    builder.PrependInt32Slot(3, minalign, 0)

def AddMinalign(builder, minalign):
    ObjectAddMinalign(builder, minalign)

def ObjectAddBytesize(builder, bytesize):
    builder.PrependInt32Slot(4, bytesize, 0)

def AddBytesize(builder, bytesize):
    ObjectAddBytesize(builder, bytesize)

def ObjectAddAttributes(builder, attributes):
    builder.PrependUOffsetTRelativeSlot(5, flatbuffers.number_types.UOffsetTFlags.py_type(attributes), 0)

def AddAttributes(builder, attributes):
    ObjectAddAttributes(builder, attributes)

def ObjectStartAttributesVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def StartAttributesVector(builder, numElems: int) -> int:
    return ObjectStartAttributesVector(builder, numElems)

def ObjectAddDocumentation(builder, documentation):
    builder.PrependUOffsetTRelativeSlot(6, flatbuffers.number_types.UOffsetTFlags.py_type(documentation), 0)

def AddDocumentation(builder, documentation):
    ObjectAddDocumentation(builder, documentation)

def ObjectStartDocumentationVector(builder, numElems):
    return builder.StartVector(4, numElems, 4)

def StartDocumentationVector(builder, numElems: int) -> int:
    return ObjectStartDocumentationVector(builder, numElems)

def ObjectAddDeclarationFile(builder, declarationFile):
    builder.PrependUOffsetTRelativeSlot(7, flatbuffers.number_types.UOffsetTFlags.py_type(declarationFile), 0)

def AddDeclarationFile(builder, declarationFile):
    ObjectAddDeclarationFile(builder, declarationFile)

def ObjectEnd(builder):
    return builder.EndObject()

def End(builder):
    return ObjectEnd(builder)

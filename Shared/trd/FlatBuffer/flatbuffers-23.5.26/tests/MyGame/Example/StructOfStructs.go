﻿// Code generated by the FlatBuffers compiler. DO NOT EDIT.

package Example

import (
	flatbuffers "github.com/google/flatbuffers/go"
)

type StructOfStructsT struct {
	A *AbilityT `json:"a"`
	B *TestT `json:"b"`
	C *AbilityT `json:"c"`
}

func (t *StructOfStructsT) Pack(builder *flatbuffers.Builder) flatbuffers.UOffsetT {
	if t == nil {
		return 0
	}
	return CreateStructOfStructs(builder, t.A.Id, t.A.Distance, t.B.A, t.B.B, t.C.Id, t.C.Distance)
}
func (rcv *StructOfStructs) UnPackTo(t *StructOfStructsT) {
	t.A = rcv.A(nil).UnPack()
	t.B = rcv.B(nil).UnPack()
	t.C = rcv.C(nil).UnPack()
}

func (rcv *StructOfStructs) UnPack() *StructOfStructsT {
	if rcv == nil {
		return nil
	}
	t := &StructOfStructsT{}
	rcv.UnPackTo(t)
	return t
}

type StructOfStructs struct {
	_tab flatbuffers.Struct
}

func (rcv *StructOfStructs) Init(buf []byte, i flatbuffers.UOffsetT) {
	rcv._tab.Bytes = buf
	rcv._tab.Pos = i
}

func (rcv *StructOfStructs) Table() flatbuffers.Table {
	return rcv._tab.Table
}

func (rcv *StructOfStructs) A(obj *Ability) *Ability {
	if obj == nil {
		obj = new(Ability)
	}
	obj.Init(rcv._tab.Bytes, rcv._tab.Pos+0)
	return obj
}
func (rcv *StructOfStructs) B(obj *Test) *Test {
	if obj == nil {
		obj = new(Test)
	}
	obj.Init(rcv._tab.Bytes, rcv._tab.Pos+8)
	return obj
}
func (rcv *StructOfStructs) C(obj *Ability) *Ability {
	if obj == nil {
		obj = new(Ability)
	}
	obj.Init(rcv._tab.Bytes, rcv._tab.Pos+12)
	return obj
}

func CreateStructOfStructs(builder *flatbuffers.Builder, a_id uint32, a_distance uint32, b_a int16, b_b int8, c_id uint32, c_distance uint32) flatbuffers.UOffsetT {
	builder.Prep(4, 20)
	builder.Prep(4, 8)
	builder.PrependUint32(c_distance)
	builder.PrependUint32(c_id)
	builder.Prep(2, 4)
	builder.Pad(1)
	builder.PrependInt8(b_b)
	builder.PrependInt16(b_a)
	builder.Prep(4, 8)
	builder.PrependUint32(a_distance)
	builder.PrependUint32(a_id)
	return builder.Offset()
}

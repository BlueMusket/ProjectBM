﻿// Code generated by the FlatBuffers compiler. DO NOT EDIT.

package NamespaceB

import "strconv"

type EnumInNestedNS int8

const (
	EnumInNestedNSA EnumInNestedNS = 0
	EnumInNestedNSB EnumInNestedNS = 1
	EnumInNestedNSC EnumInNestedNS = 2
)

var EnumNamesEnumInNestedNS = map[EnumInNestedNS]string{
	EnumInNestedNSA: "A",
	EnumInNestedNSB: "B",
	EnumInNestedNSC: "C",
}

var EnumValuesEnumInNestedNS = map[string]EnumInNestedNS{
	"A": EnumInNestedNSA,
	"B": EnumInNestedNSB,
	"C": EnumInNestedNSC,
}

func (v EnumInNestedNS) String() string {
	if s, ok := EnumNamesEnumInNestedNS[v]; ok {
		return s
	}
	return "EnumInNestedNS(" + strconv.FormatInt(int64(v), 10) + ")"
}

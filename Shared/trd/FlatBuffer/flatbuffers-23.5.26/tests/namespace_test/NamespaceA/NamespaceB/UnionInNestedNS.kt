﻿// automatically generated by the FlatBuffers compiler, do not modify

package NamespaceA.NamespaceB

@Suppress("unused")
@ExperimentalUnsignedTypes
class UnionInNestedNS private constructor() {
    companion object {
        const val NONE: UByte = 0u
        const val TableInNestedNS: UByte = 1u
        val names : Array<String> = arrayOf("NONE", "TableInNestedNS")
        fun name(e: Int) : String = names[e]
    }
}
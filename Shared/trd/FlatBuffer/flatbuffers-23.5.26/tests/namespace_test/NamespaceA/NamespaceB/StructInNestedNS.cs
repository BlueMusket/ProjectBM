﻿// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace NamespaceA.NamespaceB
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct StructInNestedNS : IFlatbufferObject
{
  private Struct __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public void __init(int _i, ByteBuffer _bb) { __p = new Struct(_i, _bb); }
  public StructInNestedNS __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public int A { get { return __p.bb.GetInt(__p.bb_pos + 0); } }
  public void MutateA(int a) { __p.bb.PutInt(__p.bb_pos + 0, a); }
  public int B { get { return __p.bb.GetInt(__p.bb_pos + 4); } }
  public void MutateB(int b) { __p.bb.PutInt(__p.bb_pos + 4, b); }

  public static Offset<NamespaceA.NamespaceB.StructInNestedNS> CreateStructInNestedNS(FlatBufferBuilder builder, int A, int B) {
    builder.Prep(4, 8);
    builder.PutInt(B);
    builder.PutInt(A);
    return new Offset<NamespaceA.NamespaceB.StructInNestedNS>(builder.Offset);
  }
  public StructInNestedNST UnPack() {
    var _o = new StructInNestedNST();
    this.UnPackTo(_o);
    return _o;
  }
  public void UnPackTo(StructInNestedNST _o) {
    _o.A = this.A;
    _o.B = this.B;
  }
  public static Offset<NamespaceA.NamespaceB.StructInNestedNS> Pack(FlatBufferBuilder builder, StructInNestedNST _o) {
    if (_o == null) return default(Offset<NamespaceA.NamespaceB.StructInNestedNS>);
    return CreateStructInNestedNS(
      builder,
      _o.A,
      _o.B);
  }
}

public class StructInNestedNST
{
  [Newtonsoft.Json.JsonProperty("a")]
  public int A { get; set; }
  [Newtonsoft.Json.JsonProperty("b")]
  public int B { get; set; }

  public StructInNestedNST() {
    this.A = 0;
    this.B = 0;
  }
}


}
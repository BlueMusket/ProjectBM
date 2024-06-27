﻿// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace NamespaceA.NamespaceB
{

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct ColorTestTable : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static ColorTestTable GetRootAsColorTestTable(ByteBuffer _bb) { return GetRootAsColorTestTable(_bb, new ColorTestTable()); }
  public static ColorTestTable GetRootAsColorTestTable(ByteBuffer _bb, ColorTestTable obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public ColorTestTable __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public global::NamespaceB.Color Color { get { int o = __p.__offset(4); return o != 0 ? (global::NamespaceB.Color)__p.bb.GetSbyte(o + __p.bb_pos) : global::NamespaceB.Color.Blue; } }
  public bool MutateColor(global::NamespaceB.Color color) { int o = __p.__offset(4); if (o != 0) { __p.bb.PutSbyte(o + __p.bb_pos, (sbyte)color); return true; } else { return false; } }

  public static Offset<global::NamespaceA.NamespaceB.ColorTestTable> CreateColorTestTable(FlatBufferBuilder builder,
      global::NamespaceB.Color color = global::NamespaceB.Color.Blue) {
    builder.StartTable(1);
    ColorTestTable.AddColor(builder, color);
    return ColorTestTable.EndColorTestTable(builder);
  }

  public static void StartColorTestTable(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddColor(FlatBufferBuilder builder, global::NamespaceB.Color color) { builder.AddSbyte(0, (sbyte)color, 2); }
  public static Offset<global::NamespaceA.NamespaceB.ColorTestTable> EndColorTestTable(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<global::NamespaceA.NamespaceB.ColorTestTable>(o);
  }
  public ColorTestTableT UnPack() {
    var _o = new ColorTestTableT();
    this.UnPackTo(_o);
    return _o;
  }
  public void UnPackTo(ColorTestTableT _o) {
    _o.Color = this.Color;
  }
  public static Offset<global::NamespaceA.NamespaceB.ColorTestTable> Pack(FlatBufferBuilder builder, ColorTestTableT _o) {
    if (_o == null) return default(Offset<global::NamespaceA.NamespaceB.ColorTestTable>);
    return CreateColorTestTable(
      builder,
      _o.Color);
  }
}

public class ColorTestTableT
{
  [Newtonsoft.Json.JsonProperty("color")]
  public global::NamespaceB.Color Color { get; set; }

  public ColorTestTableT() {
    this.Color = global::NamespaceB.Color.Blue;
  }
}


static public class ColorTestTableVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*Color*/, 1 /*global::NamespaceB.Color*/, 1, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

}

﻿// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

using global::System;
using global::System.Collections.Generic;
using global::Google.FlatBuffers;

public struct Galaxy : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static void ValidateVersion() { FlatBufferConstants.FLATBUFFERS_23_5_26(); }
  public static Galaxy GetRootAsGalaxy(ByteBuffer _bb) { return GetRootAsGalaxy(_bb, new Galaxy()); }
  public static Galaxy GetRootAsGalaxy(ByteBuffer _bb, Galaxy obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p = new Table(_i, _bb); }
  public Galaxy __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public long NumStars { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetLong(o + __p.bb_pos) : (long)0; } }

  public static Offset<Galaxy> CreateGalaxy(FlatBufferBuilder builder,
      long num_stars = 0) {
    builder.StartTable(1);
    Galaxy.AddNumStars(builder, num_stars);
    return Galaxy.EndGalaxy(builder);
  }

  public static void StartGalaxy(FlatBufferBuilder builder) { builder.StartTable(1); }
  public static void AddNumStars(FlatBufferBuilder builder, long numStars) { builder.AddLong(0, numStars, 0); }
  public static Offset<Galaxy> EndGalaxy(FlatBufferBuilder builder) {
    int o = builder.EndTable();
    return new Offset<Galaxy>(o);
  }
}


static public class GalaxyVerify
{
  static public bool Verify(Google.FlatBuffers.Verifier verifier, uint tablePos)
  {
    return verifier.VerifyTableStart(tablePos)
      && verifier.VerifyField(tablePos, 4 /*NumStars*/, 8 /*long*/, 8, false)
      && verifier.VerifyTableEnd(tablePos);
  }
}

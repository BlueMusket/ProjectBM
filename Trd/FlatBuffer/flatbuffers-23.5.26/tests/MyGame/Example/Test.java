﻿// automatically generated by the FlatBuffers compiler, do not modify

package MyGame.Example;

import com.google.flatbuffers.BaseVector;
import com.google.flatbuffers.BooleanVector;
import com.google.flatbuffers.ByteVector;
import com.google.flatbuffers.Constants;
import com.google.flatbuffers.DoubleVector;
import com.google.flatbuffers.FlatBufferBuilder;
import com.google.flatbuffers.FloatVector;
import com.google.flatbuffers.IntVector;
import com.google.flatbuffers.LongVector;
import com.google.flatbuffers.ShortVector;
import com.google.flatbuffers.StringVector;
import com.google.flatbuffers.Struct;
import com.google.flatbuffers.Table;
import com.google.flatbuffers.UnionVector;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;

@SuppressWarnings("unused")
public final class Test extends Struct {
  public void __init(int _i, ByteBuffer _bb) { __reset(_i, _bb); }
  public Test __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public short a() { return bb.getShort(bb_pos + 0); }
  public void mutateA(short a) { bb.putShort(bb_pos + 0, a); }
  public byte b() { return bb.get(bb_pos + 2); }
  public void mutateB(byte b) { bb.put(bb_pos + 2, b); }

  public static int createTest(FlatBufferBuilder builder, short a, byte b) {
    builder.prep(2, 4);
    builder.pad(1);
    builder.putByte(b);
    builder.putShort(a);
    return builder.offset();
  }

  public static final class Vector extends BaseVector {
    public Vector __assign(int _vector, int _element_size, ByteBuffer _bb) { __reset(_vector, _element_size, _bb); return this; }

    public Test get(int j) { return get(new Test(), j); }
    public Test get(Test obj, int j) {  return obj.__assign(__element(j), bb); }
  }
  public TestT unpack() {
    TestT _o = new TestT();
    unpackTo(_o);
    return _o;
  }
  public void unpackTo(TestT _o) {
    short _oA = a();
    _o.setA(_oA);
    byte _oB = b();
    _o.setB(_oB);
  }
  public static int pack(FlatBufferBuilder builder, TestT _o) {
    if (_o == null) return 0;
    return createTest(
      builder,
      _o.getA(),
      _o.getB());
  }
}


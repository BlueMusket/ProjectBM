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

public class Vec3T {
  private float x;
  private float y;
  private float z;
  private double test1;
  private int test2;
  private MyGame.Example.TestT test3;

  public float getX() { return x; }

  public void setX(float x) { this.x = x; }

  public float getY() { return y; }

  public void setY(float y) { this.y = y; }

  public float getZ() { return z; }

  public void setZ(float z) { this.z = z; }

  public double getTest1() { return test1; }

  public void setTest1(double test1) { this.test1 = test1; }

  public int getTest2() { return test2; }

  public void setTest2(int test2) { this.test2 = test2; }

  public MyGame.Example.TestT getTest3() { return test3; }

  public void setTest3(MyGame.Example.TestT test3) { this.test3 = test3; }


  public Vec3T() {
    this.x = 0.0f;
    this.y = 0.0f;
    this.z = 0.0f;
    this.test1 = 0.0;
    this.test2 = 0;
    this.test3 = new MyGame.Example.TestT();
  }
}


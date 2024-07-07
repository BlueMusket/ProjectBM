﻿// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class FallingTub implements flatbuffers.IUnpackableObject<FallingTubT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):FallingTub {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

weight():number {
  return this.bb!.readInt32(this.bb_pos);
}

mutate_weight(value:number):boolean {
  this.bb!.writeInt32(this.bb_pos + 0, value);
  return true;
}

static getFullyQualifiedName():string {
  return 'FallingTub';
}

static sizeOf():number {
  return 4;
}

static createFallingTub(builder:flatbuffers.Builder, weight: number):flatbuffers.Offset {
  builder.prep(4, 4);
  builder.writeInt32(weight);
  return builder.offset();
}


unpack(): FallingTubT {
  return new FallingTubT(
    this.weight()
  );
}


unpackTo(_o: FallingTubT): void {
  _o.weight = this.weight();
}
}

export class FallingTubT implements flatbuffers.IGeneratedObject {
constructor(
  public weight: number = 0
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  return FallingTub.createFallingTub(builder,
    this.weight
  );
}
}
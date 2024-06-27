﻿// automatically generated by the FlatBuffers compiler, do not modify

import * as flatbuffers from 'flatbuffers';



export class HandFan implements flatbuffers.IUnpackableObject<HandFanT> {
  bb: flatbuffers.ByteBuffer|null = null;
  bb_pos = 0;
  __init(i:number, bb:flatbuffers.ByteBuffer):HandFan {
  this.bb_pos = i;
  this.bb = bb;
  return this;
}

static getRootAsHandFan(bb:flatbuffers.ByteBuffer, obj?:HandFan):HandFan {
  return (obj || new HandFan()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

static getSizePrefixedRootAsHandFan(bb:flatbuffers.ByteBuffer, obj?:HandFan):HandFan {
  bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
  return (obj || new HandFan()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
}

length():number {
  const offset = this.bb!.__offset(this.bb_pos, 4);
  return offset ? this.bb!.readInt32(this.bb_pos + offset) : 0;
}

mutate_length(value:number):boolean {
  const offset = this.bb!.__offset(this.bb_pos, 4);

  if (offset === 0) {
    return false;
  }

  this.bb!.writeInt32(this.bb_pos + offset, value);
  return true;
}

static getFullyQualifiedName():string {
  return 'HandFan';
}

static startHandFan(builder:flatbuffers.Builder) {
  builder.startObject(1);
}

static addLength(builder:flatbuffers.Builder, length:number) {
  builder.addFieldInt32(0, length, 0);
}

static endHandFan(builder:flatbuffers.Builder):flatbuffers.Offset {
  const offset = builder.endObject();
  return offset;
}

static createHandFan(builder:flatbuffers.Builder, length:number):flatbuffers.Offset {
  HandFan.startHandFan(builder);
  HandFan.addLength(builder, length);
  return HandFan.endHandFan(builder);
}

unpack(): HandFanT {
  return new HandFanT(
    this.length()
  );
}


unpackTo(_o: HandFanT): void {
  _o.length = this.length();
}
}

export class HandFanT implements flatbuffers.IGeneratedObject {
constructor(
  public length: number = 0
){}


pack(builder:flatbuffers.Builder): flatbuffers.Offset {
  return HandFan.createHandFan(builder,
    this.length
  );
}
}

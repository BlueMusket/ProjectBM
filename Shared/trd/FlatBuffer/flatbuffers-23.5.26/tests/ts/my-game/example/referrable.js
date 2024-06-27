﻿// automatically generated by the FlatBuffers compiler, do not modify
import * as flatbuffers from 'flatbuffers';
export class Referrable {
    constructor() {
        this.bb = null;
        this.bb_pos = 0;
    }
    __init(i, bb) {
        this.bb_pos = i;
        this.bb = bb;
        return this;
    }
    static getRootAsReferrable(bb, obj) {
        return (obj || new Referrable()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
    }
    static getSizePrefixedRootAsReferrable(bb, obj) {
        bb.setPosition(bb.position() + flatbuffers.SIZE_PREFIX_LENGTH);
        return (obj || new Referrable()).__init(bb.readInt32(bb.position()) + bb.position(), bb);
    }
    id() {
        const offset = this.bb.__offset(this.bb_pos, 4);
        return offset ? this.bb.readUint64(this.bb_pos + offset) : BigInt('0');
    }
    mutate_id(value) {
        const offset = this.bb.__offset(this.bb_pos, 4);
        if (offset === 0) {
            return false;
        }
        this.bb.writeUint64(this.bb_pos + offset, value);
        return true;
    }
    static getFullyQualifiedName() {
        return 'MyGame.Example.Referrable';
    }
    static startReferrable(builder) {
        builder.startObject(1);
    }
    static addId(builder, id) {
        builder.addFieldInt64(0, id, BigInt('0'));
    }
    static endReferrable(builder) {
        const offset = builder.endObject();
        return offset;
    }
    static createReferrable(builder, id) {
        Referrable.startReferrable(builder);
        Referrable.addId(builder, id);
        return Referrable.endReferrable(builder);
    }
    serialize() {
        return this.bb.bytes();
    }
    static deserialize(buffer) {
        return Referrable.getRootAsReferrable(new flatbuffers.ByteBuffer(buffer));
    }
    unpack() {
        return new ReferrableT(this.id());
    }
    unpackTo(_o) {
        _o.id = this.id();
    }
}
export class ReferrableT {
    constructor(id = BigInt('0')) {
        this.id = id;
    }
    pack(builder) {
        return Referrable.createReferrable(builder, this.id);
    }
}

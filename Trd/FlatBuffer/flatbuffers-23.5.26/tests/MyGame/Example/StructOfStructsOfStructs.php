﻿<?php
// automatically generated by the FlatBuffers compiler, do not modify

namespace MyGame\Example;

use \Google\FlatBuffers\Struct;
use \Google\FlatBuffers\Table;
use \Google\FlatBuffers\ByteBuffer;
use \Google\FlatBuffers\FlatBufferBuilder;

class StructOfStructsOfStructs extends Struct
{
    /**
     * @param int $_i offset
     * @param ByteBuffer $_bb
     * @return StructOfStructsOfStructs
     **/
    public function init($_i, ByteBuffer $_bb)
    {
        $this->bb_pos = $_i;
        $this->bb = $_bb;
        return $this;
    }

    /**
     * @return StructOfStructs
     */
    public function getA()
    {
        $obj = new StructOfStructs();
        $obj->init($this->bb_pos + 0, $this->bb);
        return $obj;
    }


    /**
     * @return int offset
     */
    public static function createStructOfStructsOfStructs(FlatBufferBuilder $builder, $a_a_id, $a_a_distance, $a_b_a, $a_b_b, $a_c_id, $a_c_distance)
    {
        $builder->prep(4, 20);
        $builder->prep(4, 20);
        $builder->prep(4, 8);
        $builder->putUint($a_c_distance);
        $builder->putUint($a_c_id);
        $builder->prep(2, 4);
        $builder->pad(1);
        $builder->putSbyte($a_b_b);
        $builder->putShort($a_b_a);
        $builder->prep(4, 8);
        $builder->putUint($a_a_distance);
        $builder->putUint($a_a_id);
        return $builder->offset();
    }
}

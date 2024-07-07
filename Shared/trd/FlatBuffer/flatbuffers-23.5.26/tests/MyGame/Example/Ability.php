﻿<?php
// automatically generated by the FlatBuffers compiler, do not modify

namespace MyGame\Example;

use \Google\FlatBuffers\Struct;
use \Google\FlatBuffers\Table;
use \Google\FlatBuffers\ByteBuffer;
use \Google\FlatBuffers\FlatBufferBuilder;

class Ability extends Struct
{
    /**
     * @param int $_i offset
     * @param ByteBuffer $_bb
     * @return Ability
     **/
    public function init($_i, ByteBuffer $_bb)
    {
        $this->bb_pos = $_i;
        $this->bb = $_bb;
        return $this;
    }

    /**
     * @return uint
     */
    public function GetId()
    {
        return $this->bb->getUint($this->bb_pos + 0);
    }

    /**
     * @return uint
     */
    public function GetDistance()
    {
        return $this->bb->getUint($this->bb_pos + 4);
    }


    /**
     * @return int offset
     */
    public static function createAbility(FlatBufferBuilder $builder, $id, $distance)
    {
        $builder->prep(4, 8);
        $builder->putUint($distance);
        $builder->putUint($id);
        return $builder->offset();
    }
}
﻿<?php
// automatically generated by the FlatBuffers compiler, do not modify

namespace MyGame\Example2;

use \Google\FlatBuffers\Struct;
use \Google\FlatBuffers\Table;
use \Google\FlatBuffers\ByteBuffer;
use \Google\FlatBuffers\FlatBufferBuilder;

class Monster extends Table
{
    /**
     * @param ByteBuffer $bb
     * @return Monster
     */
    public static function getRootAsMonster(ByteBuffer $bb)
    {
        $obj = new Monster();
        return ($obj->init($bb->getInt($bb->getPosition()) + $bb->getPosition(), $bb));
    }

    public static function MonsterIdentifier()
    {
        return "MONS";
    }

    public static function MonsterBufferHasIdentifier(ByteBuffer $buf)
    {
        return self::__has_identifier($buf, self::MonsterIdentifier());
    }

    public static function MonsterExtension()
    {
        return "mon";
    }

    /**
     * @param int $_i offset
     * @param ByteBuffer $_bb
     * @return Monster
     **/
    public function init($_i, ByteBuffer $_bb)
    {
        $this->bb_pos = $_i;
        $this->bb = $_bb;
        return $this;
    }

    /**
     * @param FlatBufferBuilder $builder
     * @return void
     */
    public static function startMonster(FlatBufferBuilder $builder)
    {
        $builder->StartObject(0);
    }

    /**
     * @param FlatBufferBuilder $builder
     * @return Monster
     */
    public static function createMonster(FlatBufferBuilder $builder, )
    {
        $builder->startObject(0);
        $o = $builder->endObject();
        return $o;
    }

    /**
     * @param FlatBufferBuilder $builder
     * @return int table offset
     */
    public static function endMonster(FlatBufferBuilder $builder)
    {
        $o = $builder->endObject();
        return $o;
    }
}
﻿<?php
// automatically generated by the FlatBuffers compiler, do not modify

class Character
{
    const NONE = 0;
    const MuLan = 1;
    const Rapunzel = 2;
    const Belle = 3;
    const BookFan = 4;
    const Other = 5;
    const Unused = 6;

    private static $names = array(
        Character::NONE=>"NONE",
        Character::MuLan=>"MuLan",
        Character::Rapunzel=>"Rapunzel",
        Character::Belle=>"Belle",
        Character::BookFan=>"BookFan",
        Character::Other=>"Other",
        Character::Unused=>"Unused",
    );

    public static function Name($e)
    {
        if (!isset(self::$names[$e])) {
            throw new \Exception();
        }
        return self::$names[$e];
    }
}

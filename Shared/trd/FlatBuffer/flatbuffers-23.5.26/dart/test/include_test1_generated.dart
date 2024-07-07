﻿// automatically generated by the FlatBuffers compiler, do not modify
// ignore_for_file: unused_import, unused_field, unused_element, unused_local_variable

import 'dart:typed_data' show Uint8List;
import 'package:flat_buffers/flat_buffers.dart' as fb;


import './include_test2_my_game.other_name_space_generated.dart' as my_game_other_name_space;

class TableA {
  TableA._(this._bc, this._bcOffset);
  factory TableA(List<int> bytes) {
    final rootRef = fb.BufferContext.fromBytes(bytes);
    return reader.read(rootRef, 0);
  }

  static const fb.Reader<TableA> reader = _TableAReader();

  final fb.BufferContext _bc;
  final int _bcOffset;

  my_game_other_name_space.TableB? get b => my_game_other_name_space.TableB.reader.vTableGetNullable(_bc, _bcOffset, 4);

  @override
  String toString() {
    return 'TableA{b: ${b}}';
  }

  TableAT unpack() => TableAT(
      b: b?.unpack());

  static int pack(fb.Builder fbBuilder, TableAT? object) {
    if (object == null) return 0;
    return object.pack(fbBuilder);
  }
}

class TableAT implements fb.Packable {
  my_game_other_name_space.TableBT? b;

  TableAT({
      this.b});

  @override
  int pack(fb.Builder fbBuilder) {
    final int? bOffset = b?.pack(fbBuilder);
    fbBuilder.startTable(1);
    fbBuilder.addOffset(0, bOffset);
    return fbBuilder.endTable();
  }

  @override
  String toString() {
    return 'TableAT{b: ${b}}';
  }
}

class _TableAReader extends fb.TableReader<TableA> {
  const _TableAReader();

  @override
  TableA createObject(fb.BufferContext bc, int offset) => 
    TableA._(bc, offset);
}

class TableABuilder {
  TableABuilder(this.fbBuilder);

  final fb.Builder fbBuilder;

  void begin() {
    fbBuilder.startTable(1);
  }

  int addBOffset(int? offset) {
    fbBuilder.addOffset(0, offset);
    return fbBuilder.offset;
  }

  int finish() {
    return fbBuilder.endTable();
  }
}

class TableAObjectBuilder extends fb.ObjectBuilder {
  final my_game_other_name_space.TableBObjectBuilder? _b;

  TableAObjectBuilder({
    my_game_other_name_space.TableBObjectBuilder? b,
  })
      : _b = b;

  /// Finish building, and store into the [fbBuilder].
  @override
  int finish(fb.Builder fbBuilder) {
    final int? bOffset = _b?.getOrCreateOffset(fbBuilder);
    fbBuilder.startTable(1);
    fbBuilder.addOffset(0, bOffset);
    return fbBuilder.endTable();
  }

  /// Convenience method to serialize to byte list.
  @override
  Uint8List toBytes([String? fileIdentifier]) {
    final fbBuilder = fb.Builder(deduplicateTables: false);
    fbBuilder.finish(finish(fbBuilder), fileIdentifier);
    return fbBuilder.buffer;
  }
}
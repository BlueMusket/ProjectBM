﻿// automatically generated by the FlatBuffers compiler, do not modify
// @generated
extern crate alloc;
extern crate flatbuffers;
use alloc::boxed::Box;
use alloc::string::{String, ToString};
use alloc::vec::Vec;
use core::mem;
use core::cmp::Ordering;
use self::flatbuffers::{EndianScalar, Follow};
use super::*;
// struct NestedStruct, aligned to 8
#[repr(transparent)]
#[derive(Clone, Copy, PartialEq)]
pub struct NestedStruct(pub [u8; 32]);
impl Default for NestedStruct { 
  fn default() -> Self { 
    Self([0; 32])
  }
}
impl core::fmt::Debug for NestedStruct {
  fn fmt(&self, f: &mut core::fmt::Formatter) -> core::fmt::Result {
    f.debug_struct("NestedStruct")
      .field("a", &self.a())
      .field("b", &self.b())
      .field("c", &self.c())
      .field("d", &self.d())
      .finish()
  }
}

impl flatbuffers::SimpleToVerifyInSlice for NestedStruct {}
impl<'a> flatbuffers::Follow<'a> for NestedStruct {
  type Inner = &'a NestedStruct;
  #[inline]
  unsafe fn follow(buf: &'a [u8], loc: usize) -> Self::Inner {
    <&'a NestedStruct>::follow(buf, loc)
  }
}
impl<'a> flatbuffers::Follow<'a> for &'a NestedStruct {
  type Inner = &'a NestedStruct;
  #[inline]
  unsafe fn follow(buf: &'a [u8], loc: usize) -> Self::Inner {
    flatbuffers::follow_cast_ref::<NestedStruct>(buf, loc)
  }
}
impl<'b> flatbuffers::Push for NestedStruct {
    type Output = NestedStruct;
    #[inline]
    unsafe fn push(&self, dst: &mut [u8], _written_len: usize) {
        let src = ::core::slice::from_raw_parts(self as *const NestedStruct as *const u8, Self::size());
        dst.copy_from_slice(src);
    }
}

impl<'a> flatbuffers::Verifiable for NestedStruct {
  #[inline]
  fn run_verifier(
    v: &mut flatbuffers::Verifier, pos: usize
  ) -> Result<(), flatbuffers::InvalidFlatbuffer> {
    use self::flatbuffers::Verifiable;
    v.in_buffer::<Self>(pos)
  }
}

impl<'a> NestedStruct {
  #[allow(clippy::too_many_arguments)]
  pub fn new(
    a: &[i32; 2],
    b: TestEnum,
    c: &[TestEnum; 2],
    d: &[i64; 2],
  ) -> Self {
    let mut s = Self([0; 32]);
    s.set_a(a);
    s.set_b(b);
    s.set_c(c);
    s.set_d(d);
    s
  }

  pub const fn get_fully_qualified_name() -> &'static str {
    "MyGame.Example.NestedStruct"
  }

  pub fn a(&'a self) -> flatbuffers::Array<'a, i32, 2> {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe { flatbuffers::Array::follow(&self.0, 0) }
  }

  pub fn set_a(&mut self, items: &[i32; 2]) {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe { flatbuffers::emplace_scalar_array(&mut self.0, 0, items) };
  }

  pub fn b(&self) -> TestEnum {
    let mut mem = core::mem::MaybeUninit::<<TestEnum as EndianScalar>::Scalar>::uninit();
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid value in this slot
    EndianScalar::from_little_endian(unsafe {
      core::ptr::copy_nonoverlapping(
        self.0[8..].as_ptr(),
        mem.as_mut_ptr() as *mut u8,
        core::mem::size_of::<<TestEnum as EndianScalar>::Scalar>(),
      );
      mem.assume_init()
    })
  }

  pub fn set_b(&mut self, x: TestEnum) {
    let x_le = x.to_little_endian();
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid value in this slot
    unsafe {
      core::ptr::copy_nonoverlapping(
        &x_le as *const _ as *const u8,
        self.0[8..].as_mut_ptr(),
        core::mem::size_of::<<TestEnum as EndianScalar>::Scalar>(),
      );
    }
  }

  pub fn c(&'a self) -> flatbuffers::Array<'a, TestEnum, 2> {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe { flatbuffers::Array::follow(&self.0, 9) }
  }

  pub fn set_c(&mut self, x: &[TestEnum; 2]) {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe {
      core::ptr::copy(
        x.as_ptr() as *const u8,
        self.0.as_mut_ptr().add(9),
        2,
      );
    }
  }

  pub fn d(&'a self) -> flatbuffers::Array<'a, i64, 2> {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe { flatbuffers::Array::follow(&self.0, 16) }
  }

  pub fn set_d(&mut self, items: &[i64; 2]) {
    // Safety:
    // Created from a valid Table for this object
    // Which contains a valid array in this slot
    unsafe { flatbuffers::emplace_scalar_array(&mut self.0, 16, items) };
  }

  pub fn unpack(&self) -> NestedStructT {
    NestedStructT {
      a: self.a().into(),
      b: self.b(),
      c: self.c().into(),
      d: self.d().into(),
    }
  }
}

#[derive(Debug, Clone, PartialEq, Default)]
pub struct NestedStructT {
  pub a: [i32; 2],
  pub b: TestEnum,
  pub c: [TestEnum; 2],
  pub d: [i64; 2],
}
impl NestedStructT {
  pub fn pack(&self) -> NestedStruct {
    NestedStruct::new(
      &self.a,
      self.b,
      &self.c,
      &self.d,
    )
  }
}


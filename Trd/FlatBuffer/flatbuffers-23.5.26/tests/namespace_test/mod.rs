﻿// Automatically generated by the Flatbuffers compiler. Do not modify.
// @generated
pub mod namespace_a {
  use super::*;
  pub mod namespace_b {
    use super::*;
    mod union_in_nested_ns_generated;
    pub use self::union_in_nested_ns_generated::*;
    mod enum_in_nested_ns_generated;
    pub use self::enum_in_nested_ns_generated::*;
    mod table_in_nested_ns_generated;
    pub use self::table_in_nested_ns_generated::*;
    mod struct_in_nested_ns_generated;
    pub use self::struct_in_nested_ns_generated::*;
  } // namespace_b
  mod table_in_first_ns_generated;
  pub use self::table_in_first_ns_generated::*;
  mod second_table_in_a_generated;
  pub use self::second_table_in_a_generated::*;
} // namespace_a
pub mod namespace_c {
  use super::*;
  mod table_in_c_generated;
  pub use self::table_in_c_generated::*;
} // namespace_c
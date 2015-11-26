// Copyright (c) 2015 Dr. Colin Hirsch
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_TYPE_HH
#define TAOCPP_JSON_INCLUDE_TYPE_HH

namespace tao
{
   namespace json
   {
      enum class type : uint8_t
      {
         NULL_,
         BOOL_,
         INT64,
         DOUBLE,
         STRING,
         ARRAY,
         OBJECT
      };

      inline bool needs_destroy( const type t )
      {
         switch ( t ) {
            case type::STRING:
            case type::ARRAY:
            case type::OBJECT:
               return true;
            default:
               return false;
         }
      }

      inline const char * to_string( const type t )
      {
         switch ( t ) {
            case type::NULL_:
               return "null";
            case type::BOOL_:
               return "bool";
            case type::INT64:
               return "int64";
            case type::DOUBLE:
               return "double";
            case type::STRING:
               return "string";
            case type::ARRAY:
               return "array";
            case type::OBJECT:
               return "object";
         }
         return "unknown";
      }

      struct empty_array_t {};
      struct empty_object_t {};

      static constexpr empty_array_t empty_array = empty_array_t();
      static constexpr empty_object_t empty_object = empty_object_t();

   } // json

} // tao

#endif

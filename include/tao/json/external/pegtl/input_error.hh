// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAOCPP_JSON_EMBEDDED_PEGTL_INPUT_ERROR_HH
#define TAOCPP_JSON_EMBEDDED_PEGTL_INPUT_ERROR_HH

#include <sstream>
#include <stdexcept>

namespace tao_json_pegtl
{
   struct input_error
         : std::runtime_error
   {
      input_error( const std::string & message, const int errorno )
            : std::runtime_error( message ),
              errorno( errorno )
      { }

      int errorno;
   };

#define TAOCPP_JSON_EMBEDDED_PEGTL_THROW_INPUT_ERROR( MESSAGE )                              \
   do {                                                                 \
      const int errorno = errno;                                        \
      std::ostringstream oss;                                           \
      oss << "pegtl: " << MESSAGE << " errno " << errorno;              \
      throw tao_json_pegtl::input_error( oss.str(), errorno );                   \
   } while ( false )

} // tao_json_pegtl

#endif

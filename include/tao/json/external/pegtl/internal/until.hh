// Copyright (c) 2014-2015 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/ColinH/PEGTL/

#ifndef TAOCPP_JSON_EMBEDDED_PEGTL_INTERNAL_UNTIL_HH
#define TAOCPP_JSON_EMBEDDED_PEGTL_INTERNAL_UNTIL_HH

#include "skip_control.hh"
#include "bytes.hh"
#include "rule_conjunction.hh"

namespace tao_json_pegtl
{
   namespace internal
   {
      template< typename Cond, typename ... Rules > struct until;

      template< typename Cond, typename ... Rules >
      struct skip_control< until< Cond, Rules ... > > : std::true_type {};

      template< typename Cond >
      struct until< Cond >
      {
         using analyze_t = analysis::generic< analysis::rule_type::UNTIL, Cond, bytes< 1 > >;

         template< apply_mode A, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            auto m = in.mark();

            while ( ! Control< Cond >::template match< A, Action, Control >( in, st ... ) ) {
               if ( ! in.bump_if() ) {
                  return false;
               }
            }
            m.success();
            return true;
         }
      };

      template< typename Cond, typename ... Rules >
      struct until
      {
         using analyze_t = analysis::generic< analysis::rule_type::UNTIL, Cond, Rules ... >;

         template< apply_mode A, template< typename ... > class Action, template< typename ... > class Control, typename Input, typename ... States >
         static bool match( Input & in, States && ... st )
         {
            auto m = in.mark();

            while ( ! Control< Cond >::template match< A, Action, Control >( in, st ... ) ) {
               if ( in.empty() || ! rule_conjunction< Rules ... >::template match< A, Action, Control >( in, st ... ) ) {
                  return false;
               }
            }
            m.success();
            return true;
         }
      };

   } // internal

} // tao_json_pegtl

#endif

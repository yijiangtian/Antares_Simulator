/*
** This file is part of libyuni, a cross-platform C++ framework (http://libyuni.org).
**
** This Source Code Form is subject to the terms of the Mozilla Public License
** v.2.0. If a copy of the MPL was not distributed with this file, You can
** obtain one at http://mozilla.org/MPL/2.0/.
**
** github: https://github.com/libyuni/libyuni/
** gitlab: https://gitlab.com/libyuni/libyuni/ (mirror)
*/
#ifndef __CPP_PARSER_JSON_TABLE_HXX__
#define __CPP_PARSER_JSON_TABLE_HXX__

// Generated by grammar-converter

#include <yuni/yuni.h>

namespace Grammar
{
namespace Private
{
namespace JSON
{
struct GrammarInfos
{
    //! Initial DFA state
    const uint initialDFAState;
    //! Initial LALR state
    const uint initialLALRState;

    //! Symbols
    const struct
    {
        const uint count;
        const Symbols::Entry* table;
    } symbols;
    //! Charsets
    const struct
    {
        const uint count;
        const Charset::Entry* table;
    } charsets;
    //! Productions
    const struct
    {
        const uint count;
        const Productions::Entry* table;
    } productions;
    //! DFA states
    const struct
    {
        const uint count;
        const DFA::Entry* table;
    } dfa;
    //! LALR states
    const struct
    {
        const uint count;
        const LALR::Entry* table;
    } lalr;
};

static const GrammarInfos grammar = {
  // initial states
  0, // initial DFA state
  0, // initial LALR state

  // symbols
  {
    Symbols::count,
    Symbols::table,
  },
  // charsets
  {
    Charset::count,
    Charset::table,
  },
  // productions
  {
    Productions::count,
    Productions::table,
  },
  // dfa
  {
    DFA::count,
    DFA::table,
  },
  // lalr
  {
    LALR::count,
    LALR::table,
  },
};

} // namespace JSON
} // namespace Private
} // namespace Grammar

#endif // __CPP_PARSER_JSON_TABLE_HXX__

/*
** Copyright 2007-2018 RTE
** Authors: Antares_Simulator Team
**
** This file is part of Antares_Simulator.
**
** Antares_Simulator is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** There are special exceptions to the terms and conditions of the
** license as they are applied to this software. View the full text of
** the exceptions in file COPYING.txt in the directory of this software
** distribution
**
** Antares_Simulator is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Antares_Simulator. If not, see <http://www.gnu.org/licenses/>.
**
** SPDX-License-Identifier: licenceRef-GPL3_WITH_RTE-Exceptions
*/
#ifndef __ANTARES_LIBS_STUDY_ACTION_TEXT_HXX__
#define __ANTARES_LIBS_STUDY_ACTION_TEXT_HXX__

namespace Antares
{
namespace Action
{
template<bool AutoExpandT>
template<class StringT>
inline Text<AutoExpandT>::Text(const StringT& text)
{
    pInfos.caption = text;
}

template<bool AutoExpandT>
inline Text<AutoExpandT>::~Text()
{
}

template<bool AutoExpandT>
inline bool Text<AutoExpandT>::prepareWL(Context&)
{
    pInfos.state = stNothingToDo;
    return true;
}

template<bool AutoExpandT>
inline bool Text<AutoExpandT>::performWL(Context&)
{
    return true;
}

template<bool AutoExpandT>
inline bool Text<AutoExpandT>::bold() const
{
    return true;
}

template<bool AutoExpandT>
inline bool Text<AutoExpandT>::autoExpand() const
{
    return AutoExpandT;
}

template<bool AutoExpandT>
inline bool Text<AutoExpandT>::canDoSomething() const
{
    return false;
}

} // namespace Action
} // namespace Antares

#endif // __ANTARES_LIBS_STUDY_ACTION_TEXT_HXX__

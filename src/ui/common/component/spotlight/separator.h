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
#ifndef __ANTARES_UI_COMMON_COMPONENT_SPOTLIGHT_SPOTLIGHT_SEPARATOR_H__
#define __ANTARES_UI_COMMON_COMPONENT_SPOTLIGHT_SPOTLIGHT_SEPARATOR_H__

class Separator final : public IItem
{
public:
    //! Ptr
    typedef Yuni::SmartPtr<Separator> Ptr;
    //! Vector of items
    typedef std::vector<Ptr> Vector;
    //! Vector Ptr
    typedef Yuni::SmartPtr<Vector> VectorPtr;

public:
    //! \name Constructor & Destructor
    //@{
    /*!
    ** \brief Default constructor
    */
    Separator();
    //! Destructor
    virtual ~Separator();
    //@}

    virtual bool canBeSelected() const
    {
        return false;
    }

    virtual void draw(wxDC& dc,
                      uint itemHeight,
                      wxRect& bounds,
                      bool selected,
                      const SearchToken::VectorPtr& tokens) const;

}; // class Separator

#endif // __ANTARES_UI_COMMON_COMPONENT_SPOTLIGHT_SPOTLIGHT_SEPARATOR_H__

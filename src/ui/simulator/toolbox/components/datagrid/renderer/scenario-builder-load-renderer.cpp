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

#include "scenario-builder-load-renderer.h"


using namespace Yuni;


namespace Antares
{
namespace Component
{
namespace Datagrid
{
namespace Renderer
{

	loadScBuilderRenderer::loadScBuilderRenderer() : ScBuilderRendererBase() {}

	loadScBuilderRenderer::~loadScBuilderRenderer() {}

	bool loadScBuilderRenderer::cellValue(int x, int y, const Yuni::String& value)
	{
		if (!(!study) && !(!pRules) && (uint)x < study->parameters.nbYears)
		{
			uint d = fromStringToInt(value);

			if ((uint)y < study->areas.size())
			{
				assert((uint)y < pRules->load.overlay().width);
				assert((uint)x < pRules->load.overlay().height);
				pRules->load.overlay().entry[y][x] = d;
				return true;
			}
		}
		return false;
	}

	double loadScBuilderRenderer::cellNumericValue(int x, int y) const
	{
		if (!(!study) && !(!pRules) && (uint)x < study->parameters.nbYears)
		{
			if ((uint)y < study->areas.size())
			{
				assert((uint)y < pRules->load.overlay().width);
				assert((uint)x < pRules->load.overlay().height);
				return (pRules->load.overlay().entry[y][x]);
			}
		}
		return 0.;
	}

} // namespace Renderer
} // namespace Datagrid
} // namespace Component
} // namespace Antares

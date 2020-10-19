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
#ifndef __SOLVER_VARIABLE_STORAGE_AVERAGE_H__
# define __SOLVER_VARIABLE_STORAGE_AVERAGE_H__

# include "averagedata.h"


namespace Antares
{
namespace Solver
{
namespace Variable
{
namespace R
{
namespace AllYears
{



	template<class NextT = Empty, int FileFilter = Variable::Category::allFile>
	struct Average : public NextT
	{
	public:
		//! Type of the net item in the list
		typedef NextT NextType;

		enum
		{
			//! The count if item in the list
			count = 1 + NextT::count,

			categoryFile = NextT::categoryFile | Variable::Category::allFile,
		};

		struct Data
		{
			double value;
			uint32_t indice;
		};

		//! Name of the filter
		static const char* Name() {return "average";}

	public:
		Average()
		{}

	protected:
		void initializeFromStudy(Antares::Data::Study& study)
		{
			avgdata.initializeFromStudy(study);
			// Next
			NextType::initializeFromStudy(study);
		}

		void reset()
		{
			// Reset
			avgdata.reset();
			// Next
			NextType::reset();
		}

		void merge(uint year, const IntermediateValues& rhs)
		{
			avgdata.merge(year, rhs);
			// Next
			NextType::merge(year, rhs);
		}


		template<class S, class VCardT>
		void buildSurveyReport(SurveyResults& report, const S& results, int dataLevel, int fileLevel, int precision) const
		{
			if (!(fileLevel & Category::id))
			{
				if (0 != (fileLevel & Category::mc))
				{
					// Do nothing
					// InternalExportValuesMC<1, VCardT, Precision>(report, avgdata.year);
				}
				else
				{
					switch (precision)
					{
						case Category::hourly:
							InternalExportValues<maxHoursInAYear, VCardT, Category::hourly>(report, Memory::RawPointer(avgdata.hourly));
							break;
						case Category::daily:
							InternalExportValues<maxDaysInAYear, VCardT, Category::daily>(report, avgdata.daily);
							break;
						case Category::weekly:
							InternalExportValues<maxWeeksInAYear, VCardT, Category::weekly>(report, avgdata.weekly);
							break;
						case Category::monthly:
							InternalExportValues<maxMonths, VCardT, Category::monthly>(report, avgdata.monthly);
							break;
						case Category::annual:
							InternalExportValues<1, VCardT, Category::annual>(report, avgdata.year);
							break;
					}
				}
			}
			// Next
			NextType::template buildSurveyReport<S,VCardT>(report, results, dataLevel, fileLevel, precision);
		}

		template<class VCardT>
		void buildDigest(SurveyResults& report, int digestLevel, int dataLevel) const
		{
			if ((dataLevel & Category::area || dataLevel & Category::setOfAreas)
				&& digestLevel & Category::digestAllYears)
			{
				assert(report.data.columnIndex < report.maxVariables && "Column index out of bounds");

				report.captions[0][report.data.columnIndex] = report.variableCaption;
				report.captions[1][report.data.columnIndex] = VCardT::Unit();
				report.captions[2][report.data.columnIndex] = "EXP";

				// Precision
				report.precision[report.data.columnIndex] = PrecisionToPrintfFormat<VCardT::decimal>::Value();
				// Value
				report.values[report.data.columnIndex][report.data.rowIndex] = avgdata.allYears;
				// Non applicability
				report.digestNonApplicableStatus[report.data.rowIndex][report.data.columnIndex] = *report.isCurrentVarNA;

				++(report.data.columnIndex);
			}
			// Next
			NextType::template buildDigest<VCardT>(report, digestLevel, dataLevel);
		}

		Yuni::uint64 memoryUsage() const
		{
			return avgdata.dynamicMemoryUsage() + NextType::memoryUsage();
		}


		static void EstimateMemoryUsage(Antares::Data::StudyMemoryUsage& u)
		{
			Antares::Memory::EstimateMemoryUsage(sizeof(double), maxHoursInAYear, u, false);
			u.requiredMemoryForOutput += u.years * sizeof(double);
			u.takeIntoConsiderationANewTimeserieForDiskOutput();
			NextType::EstimateMemoryUsage(u);
		}


		template<template<class,int> class DecoratorT>
		Antares::Memory::Stored<double>::ConstReturnType hourlyValuesForSpatialAggregate() const
		{
			if (Yuni::Static::Type::StrictlyEqual<DecoratorT<Empty,0>,Average<Empty,0> >::Yes)
				return avgdata.hourly;
			return NextType::template hourlyValuesForSpatialAggregate<DecoratorT>();
		}

	public:
		AverageData avgdata;

	private:
		template<uint Size, class VCardT, int PrecisionT>
		void InternalExportValues(SurveyResults& report, const double* array) const
		{
			assert(array);
			assert(report.data.columnIndex < report.maxVariables && "Column index out of bounds");

			// Caption
			report.captions[0][report.data.columnIndex] = report.variableCaption;
			report.captions[1][report.data.columnIndex] = VCardT::Unit();
			report.captions[2][report.data.columnIndex] = "EXP";
			// Precision
			report.precision[report.data.columnIndex] = PrecisionToPrintfFormat<VCardT::decimal>::Value();
			// Non applicability
			report.nonApplicableStatus[report.data.columnIndex] = *report.isCurrentVarNA;

			// Values
			switch (PrecisionT)
			{
				case Category::annual:
					{
						double& target = *(report.values[report.data.columnIndex]);
						target = 0;
						for (uint i = 0; i != avgdata.nbYearsCapacity; ++i)
							target += array[i];
						avgdata.allYears = target;
						break;
					}
				default:
					(void)::memcpy(report.values[report.data.columnIndex], array, sizeof(double) * Size);
					break;
			}

			// Next column index
			++report.data.columnIndex;
		}

		/*
		template<uint Size, class VCardT, int PrecisionT>
		void InternalExportValuesMC(SurveyResults& report, const double* array) const
		{
			if (!(PrecisionT & Category::annual))
				return;
			assert(report.data.columnIndex < report.maxVariables && "Column index out of bounds");

			// Caption
			report.captions[0][report.data.columnIndex] = report.variableCaption;
			report.captions[1][report.data.columnIndex] = VCardT::Unit();
			report.captions[2][report.data.columnIndex] = "EXP";
			// Precision
			report.precision[report.data.columnIndex] = Solver::Variable::PrecisionToPrintfFormat<VCardT::decimal>::Value();

			(void)::memcpy(report.matrix.values[report.data.columnIndex], array, report.data.nbYears * sizeof(double));

			// Next column index
			++report.data.columnIndex;
		}
		*/


	}; // class Average







} // namespace AllYears
} // namespace R
} // namespace Variable
} // namespace Solver
} // namespace Antares

#endif // __SOLVER_VARIABLE_STORAGE_AVERAGE_H__

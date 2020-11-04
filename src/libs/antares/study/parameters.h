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
#ifndef __ANTARES_LIBS_STUDY_PARAMETERS_H__
# define __ANTARES_LIBS_STUDY_PARAMETERS_H__

#include <vector>

# include <yuni/yuni.h>
# include <yuni/core/string.h>
# include "../constants.h"
# include <stdlib.h>
# include <assert.h>
# include "../date.h"
# include "../inifile.h"
# include "fwd.h"
# include "variable-print-info.h"

#include <antares/study/UnfeasibleProblemBehavior.hpp>

using namespace std;

namespace Antares
{
namespace Data
{   
	/*!
	** \brief General data for a study
	**
	** Those data are located into the file `generalData.ini`
	*/
	class Parameters final
	{
	public:
		//! \name Constructor
		//@{
		/*!
		** \brief Default Constructor
		**
		** \warning None of the variables are initialized. You must explicitly use
		**   the method `reset()` or the method `loadFromFile()`
		** \see reset()
		** \see loadFromFile()
		*/
		Parameters();
		//! Destructor
		~Parameters();
		//@}


		//! \name Simulation mode
		//@{
		//! Get if the simulation is in economy mode
		bool economy() const;
		//! Get if the simulation is in adequacy mode
		bool adequacy() const;
		//! Get if the simulation is in adequacy-draft mode
		bool adequacyDraft() const;
		//@}


		/*!
		** \brief Assign a new number of MC years
		*/
		void years(uint y);

		/*!
		** \brief Load data from a file
		**
		** This routine ensures that the structure is properly initialized with
		** default values, whatever is the result.
		** If the filename is empty, or it does not exists, or the file can not
		** be opened, the routine will return 0.
		**
		** \param filename The file to load
		** \return True if the settings have been loaded, false if at least one error has occured
		*/
		bool loadFromFile(const AnyString& filename, uint version, const StudyLoadOptions& options);

		/*!
		** \brief Prepare all settings for a simulation
		**
		** The solver must be able to rely on all variables for performance reasons.
		** The first case scenario can be the user who might not have disabled all settings,
		** like the `refresh`, that can have a non-zero value even if the ts-generator
		** is disabled.
		** Another case would be the directives given by the command line.
		**
		** \note This method is automatically called from `loadFromFile()` if the
		**  flag options.usedByTheSolver is set.
		** \see loadFromFile()
		*/
		void prepareForSimulation(const StudyLoadOptions& options);


		/*!
		** \brief Save data to an ini file
		**
		** \param filename The target filename
		** \return True if the file has been successfully saved, false otherwise
		*/
		bool saveToFile(const AnyString& filename) const;


		/*!
		** \brief Get if a time-series must be generated by the preprocessor
		**
		** \param mask The time-serie to test
		** \return True if the time-series must be generated by the preprocessor, false otherwise
		*/
		bool isTSGeneratedByPrepro(const TimeSeries ts) const;


		/*!
		** \brief Reset to default all values in a structure for general data
		*/
		void reset();
		/*!
		** \brief Reset to default all seeds
		*/
		void resetSeeds();

		/*!
		** \brief Try to detect then fix any bad value
		*/
		void fixBadValues();

		/*!
		** \brief Check if some general data seem valid
		**
		** \return The error if any (stErrNone otherwise)
		*/
		StudyError checkIntegrity() const;


		void removeExtraSettings();

		/*!
		** \brief Get the amount of memory used by the general data
		*/
		Yuni::uint64 memoryUsage() const;

        /*!
        ** \brief Reset MC year weight to 1 for all years
        */
		void resetYearsWeigth();

        /*!
        ** \brief Get MC years weight dependending on playlist configuration
        **
        ** \return std::vector<int> with weight for each MC year
        */
		std::vector<int> getYearsWeight() const;

        /*!
        ** \brief Get MC years weight sum dependending on playlist configuration
        **
        ** \return weigth sum (nbYears if playlist disabled)
        */
		int              getYearsWeightSum() const;

        /*!
        ** \brief Define weight for a MC year
        **
		** \param year MC year index
		** \param weight MC year weight
        */
		void setYearWeight(int year, int weight);

	public:
		//! \name Mode
		//@{
		//! Mode of the study (adequacy, economy...)
		StudyMode mode;
		//@}

		//! \name Expansion
		//@{
		//! Expansion flag
		mutable bool expansion;

		//! \name Horizon
		//@{
		//! Horizon year
		Yuni::String horizon;
		//@}

		//! \name Calendar
		//@{
		//! Number of years to study
		uint nbYears;
		//! Simulation days interval
		Date::DayInterval simulationDays;
		//! Day of the 1st january
		DayOfTheWeek dayOfThe1stJanuary;
		//! First day in the week
		DayOfTheWeek firstWeekday;
		//! The first month of the simulation year
		MonthName  firstMonthInYear;
		//! Leap year
		bool leapYear;
		//@}


		//! \name Additional
		//@{
		//! Export results each year
		bool yearByYear;
		//! Derated
		bool derated;
		//! Custom scenario
		bool useCustomScenario;
		//! Custom playlist (each year will be manually selected by the user)
		bool userPlaylist;
		//! Flag to perform the calculations or not from the solver
		bool* yearsFilter;

		//! Custom variable selection (each variable will be manually selected for print by the user)
		bool thematicTrimming;
		//! List of all output variables print info
		mutable AllVariablesPrintInfo variablesPrintInfo;

		//! The number of years that will be really performed
		// Computed automatically from the number of MC years and the playlist
		uint effectiveNbYears;
		//! Enable/Disable filtering by files :
		//!		for an area or a link, print (or not) a file associated to :
		//!		- a time division (hourly results, daily results, weekly results, ...),
		//!		- a kind of result (year by year result or a synthesis result).
		bool geographicTrimming;
		//@}


		//! \name TimeSeries
		//@{
		//! Nb of timeSeries : Load
		uint nbTimeSeriesLoad;
		//! Nb of timeSeries : Hydro
		uint nbTimeSeriesHydro;
		//! Nb of timeSeries : Wind
		uint nbTimeSeriesWind;
		//! Nb of timeSeries : Thermal
		uint nbTimeSeriesThermal;
		//! Nb of timeSeries : Solar
		uint nbTimeSeriesSolar;
		//@}


		//! \name Time-series refresh
		//@{
		/*!
		** \brief Time series to refresh on-line
		**
		** This value is a mask bits for timeSeries
		** \see TimeSeries
		*/
		uint timeSeriesToRefresh;

		//! Refresh interval (in years) for timeSeries : Load
		uint refreshIntervalLoad;
		//! Refresh interval (in years) for timeSeries : Hydro
		uint refreshIntervalHydro;
		//! Refresh interval (in years) for timeSeries : Wind
		uint refreshIntervalWind;
		//! Refresh interval (in years) for timeSeries : Thermal
		uint refreshIntervalThermal;
		//! Refresh interval (in years) for timeSeries : Solar
		uint refreshIntervalSolar;
		//@}


		//! \name Archives
		//@{
		/*!
		** \brief TimeSeries to archive
		**
		** Only generated timeSeries will be archived.
		** This value is a mask bits for timeSeries.
		** \see TimeSeries
		*/
		uint timeSeriesToArchive;
		//@}


		//! \name Pre-Processor
		//@{
		/*!
		** \brief TimeSeries to generate
		**
		** This value is a mask bits for timeSeries.
		** \see TimeSeries
		*/
		uint timeSeriesToGenerate;
		//@}

		//! \name Import Time-Series to HardDrive
		//@{
		/*!
		** \brief TimeSeries to Import
		**
		** This value is a mask bits for timeSeries.
		** All generated timeseries will be re-written into the input
		** \see TimeSeries
		*/
		uint timeSeriesToImport;
		//@}

		//! \name Correlated draws
		//@{
		/*!
		** \brief TimeSeries where the draws are correlated
		**
		** This value is a mask bits for timeSeries.
		** \see TimeSeries
		** This is the historical correlation mode
		*/
		uint intraModal;

		/*!
		** \brief Inter-modal
		*/
		uint interModal;
		//@}

		//! \name Timeseries numbers
		//@{
		//! Store the sampled timeseries numbers
		bool storeTimeseriesNumbers;
		//@}

		/*!
		** \brief Read-only mode
		**
		** This value can only be set by the property `read-only` in the
		** generaldata.ini. The default value is `false`.
		*/
		bool readonly;

		//! Write the simulation synthesis into the output
		bool synthesis;

		//! \name Optimization
		//@{
		//! Spillage bound
		bool spillageBound;

		//! Improve units startup
		bool improveUnitsStartup;
		//! Block size used by the adequacy algorithm
		uint adequacyBlockSize;

		//! Accuracy on correlation
		uint timeSeriesAccuracyOnCorrelation;
	
		//@}


		//! \name Optimization preferences
		//@{
		struct IncludeOptions
		{
			//! Include binding constraints
			bool constraints;
			//! Hurdle costs
			bool hurdleCosts;

			struct Reserve
			{
				//! Day ahead reserve
				bool dayAhead;
				//! Strategic reserve
				bool strategic;
				//! Spinning reserve
				bool spinning;
				//! Primary reserve
				bool primary;

			} reserve;

			struct Thermal
			{
				// Thermal cluster min stable power
				bool minStablePower;
				
				//! Thermal cluster Min U/D Time
				bool minUPTime;
			} thermal;
			

			//! a flag to export all mps files
			bool exportMPS;

			//! a flag to export structure needed for Antares XPansion
			bool exportStructure;

			//!Enum to define unfeasible problem behavior \see UnfeasibleProblemBehavior
			UnfeasibleProblemBehavior unfeasibleProblemBehavior;

		} include;

		// Shedding
		struct
		{
			//! Shedding strategy
			SheddingStrategy strategy;
			//! Shedding policy
			SheddingPolicy   policy;
		} shedding;

		struct
		{
			//! Power fluctuations
			PowerFluctuations  fluctuations;
		} power;

		struct
		{
			//! Unit Commitment Mode
			UnitCommitmentMode  ucMode;
		} unitCommitment;

		
		struct
		{
			//! Number of Cores Mode
			NumberOfCoresMode  ncMode;
		} nbCores;

		struct
		{
			//! Initial reservoir levels
			InitialReservoirLevels  iniLevels;
		} initialReservoirLevels;

		struct
		{
			//! Hydro Pricing Mode
			HydroPricingMode  hpMode;
		} hydroPricing;
		
		// In case of hydro hot start and MC years simultaneous run
		// ... Answers the question : do all sets of simultaneous years have the same size ?
		//     (obvious if the parallel mode is not required : answer is yes).
		bool allSetsHaveSameSize;

		struct
		{
			//! Day ahead reserve allocation mode
			DayAheadReserveManagement  daMode;
		} reserveManagement;


		//! Transmission capacities
		TransmissionCapacities transmissionCapacities;
		//! Asset type
		LinkType linkType;
		//! Simplex optimization range (day/week)
		SimplexOptimization  simplexOptimizationRange;
		//@}

		//! \name Scenariio Builder - Rules
		//@{
		//! The current active rules for building scenarios (useful if building mode == custom)
		RulesScenarioName  activeRulesScenario;
		//@}

		//! \name Output
		//@{
		//! No output
		// This variable is not stored within the study but only used by the solver
		bool noOutput;
		//@}


		//! \name Seeds
		//@{
		//! Seeds
		uint seed[seedMax];
		//@}


	private:
		//! Load data from an INI file
		bool loadFromINI(const IniFile& ini, uint version, const StudyLoadOptions& options);
		//! Save the internal settings into an INI file
		void saveToINI(IniFile& ini) const;

        //! MC year weight for MC synthesis
        std::vector<int> yearsWeight;

	}; // class Parameters






	/*!
	** \brief Convert a study mode (enum) into a human readable C-String
	*/
	const char* StudyModeToCString(StudyMode mode);

	/*!
	** \brief Convert a C-String (lowercase) into a study mode if possible
	**
	** \param[out] mode The study mode. It will remain untouched if the conversion failed
	** \param Text An arbitrary Text (case insensitive)
	** \return True if the conversion succeeded, false otherwise
	*/
	bool StringToStudyMode(StudyMode& mode, Yuni::CString<20,false> text);







} // namespace Data
} // namespace Antares

# include "parameters.hxx"

#endif // __ANTARES_LIBS_STUDY_PARAMETERS_H__

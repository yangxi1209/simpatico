#ifndef MCMD_MD_STRESS_AUTOCORRELATION_CPP
#define MCMD_MD_STRESS_AUTOCORRELATION_CPP

/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2012, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/


#include "MdStressAutoCorrelation.h"        // class header

namespace McMd
{

   /* 
   * Constructor.
   */
   MdStressAutoCorrelation::MdStressAutoCorrelation(MdSystem& system)
    : StressAutoCorrelation<MdSystem>(system)
   {  setClassName("MdStressAutoCorrelation"); }

   /* 
   * Destructor.
   */
   MdStressAutoCorrelation::~MdStressAutoCorrelation()
   {}

}
#endif

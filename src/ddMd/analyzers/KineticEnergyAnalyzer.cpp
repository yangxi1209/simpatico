/*
* Simpatico - Simulation Package for Polymeric and Molecular Liquids
*
* Copyright 2010 - 2014, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "KineticEnergyAnalyzer.h"
#include <util/format/Int.h>
#include <util/format/Dbl.h>
#include <util/accumulators/Average.h>                    // member template 
#include <util/mpi/MpiLoader.h>
#include <util/misc/ioUtil.h>

#include <sstream>

namespace DdMd
{

   using namespace Util;

   /*
   * Constructor.
   */
   KineticEnergyAnalyzer::KineticEnergyAnalyzer(Simulation& simulation) 
    : Analyzer(simulation),
      outputFile_(),
      accumulator_(NULL),
      nSamplePerBlock_(1),
      isInitialized_(false)
   {  setClassName("KineticEnergyAnalyzer"); }

   /*
   * Destructor.
   */
   KineticEnergyAnalyzer::~KineticEnergyAnalyzer() 
   {  
      if(accumulator_ != NULL) {
         delete accumulator_;
      }
   }

   /*
   * Read interval and outputFileName. 
   */
   void KineticEnergyAnalyzer::readParameters(std::istream& in) 
   {
      readInterval(in);
      readOutputFileName(in);
      read<int>(in,"nSamplePerBlock", nSamplePerBlock_);

      if (simulation().domain().isMaster()) {
         accumulator_ = new Average;
         accumulator_->setNSamplePerBlock(nSamplePerBlock_);
      }

      isInitialized_ = true;
   }

   /*
   * Load internal state from an archive.
   */
   void KineticEnergyAnalyzer::loadParameters(Serializable::IArchive &ar)
   {
      loadInterval(ar);
      MpiLoader<Serializable::IArchive> loader(*this, ar);
      loader.load(nSamplePerBlock_);

      if (simulation().domain().isMaster()) {
         accumulator_ = new Average;
         accumulator_->loadParameters(ar);
      }

      if (nSamplePerBlock_ != accumulator_->nSamplePerBlock()) {
         UTIL_THROW("Inconsistent values of nSamplePerBlock");
      }

      isInitialized_ = true;
   }

   /*
   * Save internal state to an archive.
   */
   void KineticEnergyAnalyzer::save(Serializable::OArchive &ar)
   {
      saveInterval(ar);
      saveOutputFileName(ar);

      if (simulation().domain().isMaster()){
         ar << *accumulator_;
      }
   }

   /*
   * Reset nSample.
   */
   void KineticEnergyAnalyzer::clear() 
   {   
      if (simulation().domain().isMaster()){ 
         accumulator_->clear();
      }
   }

   /*
   * Compute value.
   */
   void KineticEnergyAnalyzer::sample(long iStep) 
   {
      if (isAtInterval(iStep))  {
         double energy = 0.0;
         simulation().computeKineticEnergy();
         if (simulation().domain().isMaster()) {
            energy =  simulation().kineticEnergy();
            accumulator_->sample(energy);
         }
      }
   }

   /*
   * Output results to file after simulation is completed.
   */
   void KineticEnergyAnalyzer::output()
   {
      if (simulation().domain().isMaster()) {
         simulation().fileMaster().openOutputFile(outputFileName(".prm"), outputFile_);
         ParamComposite::writeParam(outputFile_);
         outputFile_.close();

         simulation().fileMaster().openOutputFile(outputFileName(".ave"), outputFile_);
         accumulator_->output(outputFile_);
         outputFile_.close();
      }
   }

}

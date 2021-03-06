////////////////////////////////////////////////////////////////////////////////
//!                                                                             
//!                        \author Simon C. Davenport
//!                                                                             
//!	 \file
//!     This file defines a class to store a 2 Landau level FQHE 
//!     Haldane pseduopotential model for in the sphere geometry. 
//!                                                        
//!                    Copyright (C) Simon C Davenport
//!                                                                             
//!     This program is free software: you can redistribute it and/or modify
//!     it under the terms of the GNU General Public License as published by
//!     the Free Software Foundation, either version 3 of the License,
//!     or (at your option) any later version.
//!                                                                             
//!     This program is distributed in the hope that it will be useful, but
//!     WITHOUT ANY WARRANTY; without even the implied warranty of
//!     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//!     General Public License for more details.
//!                                                                             
//!     You should have received a copy of the GNU General Public License
//!     along with this program. If not, see <http://www.gnu.org/licenses/>.
//!                                                                             
////////////////////////////////////////////////////////////////////////////////

#ifndef _TWO_LEVEL_PSEUDOPOTENTIAL_MODEL_HPP_INCLUDED_
#define _TWO_LEVEL_PSEUDOPOTENTIAL_MODEL_HPP_INCLUDED_

///////     LIBRARY INCLUSIONS     /////////////////////////////////////////////
#include "pseudopotential_model_base.hpp"
#include "../../hamiltonians/two_level_spinless_fermion_hamiltonian.hpp"
#include "term_tables.hpp"
#include "two_level_angular_momentum_constraint.hpp"
#if _DEBUG_
#include "../../utilities/general/debug.hpp"
#include <bitset>
#endif

namespace diagonalization
{
    //!
    //! The SphereTwoLevelPseudopotentialModel class defines a 2 Landau level
    //! FQHE Haldane pseudopotential model the sphere geometry. 
    //!
    class SphereTwoLevelPseudopotentialModel : 
    public SpherePseudopotentialModelBase<TwoLevelSpinlessFermionHamiltonian<double> >
    {
        private:
        QuadraticTermTables m_quadraticTables;
                                            //!<  Class container for regular array term tables
        QuarticTermTables m_quarticTables;  //!<  Class container for regular array term tables
        QuadraticTermTables m_quadraticTables2LL;
                                            //!<  Class container for regular array term tables
                                            //!   for 2nd LL interactions
        QuarticTermTables m_quarticTables2LL;
                                            //!<  Class container for regular array term tables
                                            //!   for 2nd LL interactions
        public:
        SphereTwoLevelPseudopotentialModel(const iSize_t nbrParticles,
            const iSize_t nbrOrbitals, const std::vector<double>& pseudopotentials,
            const std::vector<double>& pseudopotentials2LL);
        SphereTwoLevelPseudopotentialModel(boost::program_options::variables_map* optionList, 
                                           utilities::MpiWrapper& mpi);
        void BuildTermTables(const utilities::MpiWrapper& mpi);
        void TermsToFile(const io::fileFormat_t format, utilities::MpiWrapper& mpi) const;
        void TermsFromFile(const io::fileFormat_t format, utilities::MpiWrapper& mpi);
        void SetOccupationEnergies(double* energyLevels, const iSize_t dim, const utilities::MpiWrapper& mpi);
        void BuildFockBasis(utilities::MpiWrapper& mpi);
        void SetFockBasis(fock_t* buffer1, fock_t* buffer2, const fock_t dim);
        void BuildHamiltonian(utilities::MpiWrapper& mpi);
        void Diagonalize(utilities::MpiWrapper& mpi);
    };
}   //  End diagonalization namespace
#endif

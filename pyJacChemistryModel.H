/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2016-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::pyJacChemistryModel

Description
    Extends StandardChemistryModel by adding the pyJac lib.


SourceFiles
    pyJacChemistryModelI.H
    pyJacChemistryModel.C

\*---------------------------------------------------------------------------*/

#ifndef pyJacChemistryModel_H
#define pyJacChemistryModel_H

#include "StandardChemistryModel.H"
#include "chemistryReductionMethod.H"
#include "chemistryTabulationMethod.H"
#include "OFstream.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                      Class pyJacChemistryModel Declaration
\*---------------------------------------------------------------------------*/

template<class ReactionThermo, class ThermoType>
class pyJacChemistryModel
:
    public StandardChemistryModel<ReactionThermo, ThermoType>
{
    // Private Member Functions

        //- Disallow copy constructor
        pyJacChemistryModel(const pyJacChemistryModel&);

        //- Disallow default bitwise assignment
        void operator=(const pyJacChemistryModel&);


public:

    //- Runtime type information
    TypeName("pyJac");


    // Constructors

        //- Construct from thermo
        pyJacChemistryModel(ReactionThermo& thermo);


    //- Destructor
    virtual ~pyJacChemistryModel();


    // Member Functions

        virtual void derivatives
        (
            const scalar t,
            const scalarField& c,
            scalarField& dcdt
        ) const;

        virtual void jacobian
        (
            const scalar t,
            const scalarField& c,
            scalarField& dcdt,
            scalarSquareMatrix& J
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //



// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "pyJacChemistryModel.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

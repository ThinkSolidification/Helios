/** \file "EnergyBalanceModel.h" Primary header file for energy balance model.
    \author Brian Bailey

    Copyright (C) 2018  Brian Bailey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

*/

#ifndef __ENERGYBALANCEMODEL__
#define __ENERGYBALANCEMODEL__

#include "Context.h"

//! Energy balance model class
/** This model computes surface temperatures based on a local energy balance */
class EnergyBalanceModel{
public:

  //! Constructor
  /** \param[in] "context" Pointer to the Helios context */
  EnergyBalanceModel( helios::Context* context );

  //! Self-test
  /** \return 0 if test was successful, 1 if test failed. */
  int selfTest( void );

  //! Function to run the energy balance model
  /** \param[in] "radiation_bands" Vector of strings that give the names of the radiation bands to include in net radiation flux calculation. */
  DEPRECATED( void run( std::vector<std::string> radiation_bands ) );

  //! Function to run the energy balance model for all primitives in the Context
  /** \param[in] "radiation_bands" Vector of strings that give the names of the radiation bands to include in net radiation flux calculation. */
  void run(void) ;

  //! Function to run the energy balance model for a select set of primitives
  /** \param[in] "UUIDs" Unique universal identifiers (UUIDs) for primitives that should be included in energy balance calculations. All other primitives will be skipped by the model.*/
  void run( std::vector<uint> UUIDs );

  //! Add the label of a radiation band in the RadiationModel plug-in that should be used in calculation of the absorbed all-wave radiation flux
  /** \param[in] "band" Name of radiation band (e.g., PAR, NIR, LW, etc.)
   */
  void addRadiationBand( const char* band );

private:

  //! Copy of a pointer to the context
  helios::Context* context;

  //! Default surface temperature if it was not specified in the context
  float temperature_default;

  //! Default wind speed if it was not specified in the context
  float wind_speed_default;

  //! Default air temperature if it was not specified in the context
  float air_temperature_default;

  //! Default air relative humidity if it was not specified in the context
  float air_humidity_default;

  //! Default air pressure if it was not specified in the context
  float pressure_default;

  //! Default stomatal conductance if it was not specified in the context
  float gS_default;

  //! Default "other" flux if it was not specified in the context
  float Qother_default;

  //! Solve the surface energy balance using Secant method
  /** 
     \param[in] "T" Initial guess for primitive surface temperature
     \param[in] "R" Total absorbed radiation over all bands
     \param[in] "Qother" Other energy flux, e.g., storage, conductance
     \param[in] "eps" Primitive emissivity
     \param[in] "U" Wind speed outside of the primitive boundary-layer
     \param[in] "L" Characteristic length of primitive for convection
     \param[in] "Ta" Air temperature outside of the primitive boundary-layer
     \param[in] "ea" Air vapor pressure outside of the primitive boundary-layer
     \param[in] "pressure" Air pressure
     \param[in] "gS" Stomatal conductance
     \param[in] "Nsides" Number of sides of primitive emitting radiation
     \return Primitive surface temperature
  */
  //float solveEnergyBalance( float T, float R, float Qother, float eps, float U, float L, float Ta, float ea, float pressure, float gS, uint Nsides );

  //! Evaluate the surface energy balance equation and calculate the residual
  /** 
     \param[in] "T" Primitive surface temperature
     \param[in] "R" Total absorbed radiation over all bands
     \param[in] "Qother" Other energy flux, e.g., storage, conductance
     \param[in] "eps" Primitive emissivity
     \param[in] "U" Wind speed outside of the primitive boundary-layer
     \param[in] "L" Characteristic length of primitive for convection
     \param[in] "Ta" Air temperature outside of the primitive boundary-layer
     \param[in] "ea" Air vapor pressure outside of the primitive boundary-layer
     \param[in] "pressure" Air pressure
     \param[in] "gS" Stomatal conductance
     \param[in] "Nsides" Number of sides of primitive emitting radiation
     \return Energy balance resiudal
  */
  //float evaluateEnergyBalance( float T, float R, float Qother, float eps, float U, float L, float Ta, float ea, float pressure, float gS, uint Nsides );

  //! Names of radiation bands to be included in absorbed all-wave radiation flux
  std::vector<std::string> radiation_bands;
    
};

#endif
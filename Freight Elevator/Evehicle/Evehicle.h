/*******************************************************************
*
*  DESCRIPTION: class Evehicle - Simulates the Freight Elevator
* 								 Vehicle
*
*  AUTHOR:  Marcelo Gutierrez Alcaraz
*
*  EMAIL: marcelo@sce.carleton.ca
*
*  DATE: October 19, 2005
*
*******************************************************************/

#ifndef __EVEHICLE_H
#define __EVEHICLE_H

/** include files **/
#include "atomic.h"     // class Atomic


/** declarations **/
class Evehicle : public Atomic
{
public:
	Evehicle( const string &name = "Evehicle" );	// Default constructor

	~Evehicle();

	virtual string className() const
		{return "Evehicle";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	int     partType;
	int		floor;
	int		calldiff;
	Port    &in;
	Port    &out ;

// not needed for this example
	int 	  NUM_PARTS;
	int     DEBUG;

			
};	// class evehicle


#endif   //__EVEHICLE_H 

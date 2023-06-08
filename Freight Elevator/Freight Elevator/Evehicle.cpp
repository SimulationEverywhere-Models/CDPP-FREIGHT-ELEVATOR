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

/** include files **/
#include "Evehicle.h"     // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator (MainSimulator::Instance().getParameter( ... ))

/*******************************************************************
* Function Name: Evehicle
* Description: constructor
********************************************************************/
Evehicle::Evehicle( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )

{
/*	
	string debugTemp( MainSimulator::Instance().getParameter( description(), "DEBUG_FLAG" ) ) ;
	if (debugTemp == "1") DEBUG = 1;
	else DEBUG = 0;
*/

}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Evehicle::initFunction()
{
	passivate();	// for the final mod. this should be a condition for any other state
	partType = 1;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: stay in travel time for the difference between floors
* 			   times a fixed travel time (1 min)
********************************************************************/
Model &Evehicle::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == in) {

		calldiff = msg.value() * 1 ;
		holdIn( active, Time(0,calldiff,0,0) ) ;
		
	}

	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:   Always in loading/delivering state until an 
*                external events occur
********************************************************************/
Model &Evehicle::internalFunction( const InternalMessage & )	
{
	passivate();		
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Evehicle::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), out, calldiff) ;
	return *this ;
}

Evehicle::~Evehicle()
{
	// N/A
}

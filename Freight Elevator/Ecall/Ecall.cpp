/*******************************************************************
*
*  DESCRIPTION: class Ecall - Call Generation for a Freight Elevator
*
*  AUTHOR:  Marcelo Gutierrez Alcaraz
*
*  EMAIL: marcelo@sce.carleton.ca
*
*  DATE: October 19, 2005
*
*******************************************************************/

/** include files **/
#include "Ecall.h"     // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator (MainSimulator::Instance().getParameter( ... ))

/*******************************************************************
* Function Name: Ecall
* Description: constructor
********************************************************************/
Ecall::Ecall( const string &name )
: Atomic( name )
, outside_call( addInputPort( "outside_call" ) )
, inside_call( addInputPort( "inside_call" ) )
, call_gen( addOutputPort( "call_gen" ) )

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
Model &Ecall::initFunction()
{
//	passivate();	// for the final mod. this should be a condition for any other state
	des_maker = 1;
	return *this ;
}

/********************************************************************
* Function Name: externalFunction
* Description: On any input, it immediately calls the output function
*********************************************************************/
Model &Ecall::externalFunction( const ExternalMessage &msg )
{
	if (msg.port() == inside_call) {

		acall_gen = msg.value();
		des_maker = 0;
		holdIn( active, Time::Zero ) ;
	}
	if ((msg.port() == outside_call) && (des_maker != 0)) {

		acall_gen = msg.value();
		holdIn( active, Time::Zero ) ;
		
	}
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description:   Always passive since the block only waits and 
*                reroutes the calling
********************************************************************/
Model &Ecall::internalFunction( const InternalMessage & )	
{
	des_maker = 1;
	passivate();		
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Ecall::outputFunction( const InternalMessage &msg )
{
	sendOutput( msg.time(), call_gen, acall_gen) ;
	return *this ;
}

Ecall::~Ecall()
{
	// N/A
}

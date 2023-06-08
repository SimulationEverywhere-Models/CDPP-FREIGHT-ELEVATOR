/*******************************************************************
*
*  DESCRIPTION: class Econtrol
*
*  AUTHOR:  Marcelo Gutierrez Alcaraz
*
*  EMAIL: marcelo@sce.carleton.ca
*
*  DATE: October 19, 2005
*
*******************************************************************/

/** include files **/
#include "Econtrol.h"     // base header
#include "message.h"       // class InternalMessage 
#include "mainsimu.h"      // class Simulator (MainSimulator::Instance().getParameter( ... ))

/*******************************************************************
* Function Name: Econtrol
* Description: constructor
********************************************************************/
Econtrol::Econtrol( const string &name )
: Atomic( name )
, acall( addInputPort( "acall" ) )
, fback( addInputPort( "fback" ) )
, timem( addOutputPort( "timem" ) )
, floor( addOutputPort( "floor" ) )

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
Model &Econtrol::initFunction()
{
	sendElement = 0;
	BUFFER_MAX_SIZE = 100;
	elements.erase( elements.begin(), elements.end() ) ;
	AVelements.erase( AVelements.begin(), AVelements.end() ) ;
	temp_index = 1;
	actualfloor = temp_index;
	temp_index = 0;	//test
	temp_index2 = 0;	//test
	CyclicVar = 0;	//not used
	StateChecker = 1;
	AVelements.push_back(actualfloor);
	AVelements.pop_front();
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: On input ACALL perfom the calculation and store
* 			   until response from Evehicle
********************************************************************/
Model &Econtrol::externalFunction( const ExternalMessage &msg )
{
	
	if( msg.port() == acall )
	{
		out_call = 1;
		floorvalue = msg.value();
		diff_value = abs(floorvalue - actualfloor) * 1;
		if( elements.size() < BUFFER_MAX_SIZE ) {	
			elements.push_back( diff_value ) ;
			AVelements.push_back( floorvalue ) ;
		}
		
		 else {
				// Should not happen
				}
		}

	if( msg.port() == fback )
	{
		bufferCall = 1;
		StateChecker = 1;
		if( elements.size() > 0 ) {
			sendElement = 1;
		}
		else {
			// Should not happen
		}
	}
	holdIn( active, Time::Zero);

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description:   Update actual floor and wait for more calls
********************************************************************/
Model &Econtrol::internalFunction( const InternalMessage & )	
{
	actualfloor = floorvalue;
	passivate();		
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Econtrol::outputFunction( const InternalMessage &msg )
{

	if (bufferCall == 1)
	{
		bufferCall = 0;
//		if (sendElement == 0)
//		{
			sendElement = 0;
			sendOutput( msg.time(), floor, AVelements.front() ) ;	// Keeps the floor index	
			AVelements.pop_front();									// accordingly to call #
			//
//			if(temp_index == 0) { 
//			sendOutput( msg.time(), timem, elements.front() ) ;	// Send element in front
//			elements.pop_front();
//			temp_index = 8;
//			}
			//
//		}
	}

	if (out_call == 1)
	{
		out_call = 0;

		if(StateChecker == 1) { 
			sendOutput( msg.time(), timem, elements.front() ) ;	// Send element in front
			elements.pop_front();
			StateChecker = 0;			
		} 
	} 	

	return *this ;
}

Econtrol::~Econtrol()
{
	// N/A
}

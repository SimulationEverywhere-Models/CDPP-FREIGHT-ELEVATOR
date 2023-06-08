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

#ifndef __ECONTROL_H
#define __ECONTROL_H

/** include files **/
#include "atomic.h"     // class Atomic


/** declarations **/
class Econtrol : public Atomic
{
public:
	Econtrol( const string &name = "Econtrol" );	// Default constructor

	~Econtrol();

	virtual string className() const
		{return "Econtrol";}

protected:
	Model &initFunction() ;

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	int     sendElement;
	int		floorvalue;
	int		actualfloor;
	int		diff_value;
	int		temp_index;		// test
	int		temp_index2;	// test
	int		StateChecker;	// test
	int		CyclicVar;
	int		out_call;
	int		bufferCall;
	const 	Port	&acall;		// inputs to the control
	const 	Port	&fback;		// block
	Port    &timem;				//outputs the time difference
	Port	&floor;				//outputs the actual floor
	unsigned int        BUFFER_MAX_SIZE;
	
	typedef list<Value> ElementList ;
	ElementList         elements ;
	
	typedef list<Value> FloorAVlist;
	FloorAVlist         AVelements ;
			
};	// class econtrol


#endif   //__ECONTROL_H 
